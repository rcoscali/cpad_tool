/**
 * @file main.cc
 *
 */

#include <stdio.h>
#include <iostream>                         // for std::cout
#include <fstream>
#include <utility>                          // for std::pair
#include <algorithm>                        // for std::for_each

#include <boost/config.hpp>
#include <boost/utility.hpp>                // for boost::tie

#include <boost/graph/properties.hpp>
#include <boost/graph/graph_concepts.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/adj_list_serialize.hpp>
#include <boost/graph/graphviz.hpp>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <boost/serialization/access.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/binary_object.hpp>
#include <boost/serialization/split_member.hpp>

#include "graph.h"

#include <boost/serialization/export.hpp>

using namespace cpad;

int
main(int argc, char **argv)
{
  enum
  {
    vertex_1 = 1,
    vertex_2,
    vertex_3,
    vertex_4,
    vertex_5,
    vertex_6,
    num_vertices
  };

  cpad::graph g;

  uuid_t gid;
  uuid_generate_time(gid);
  graph_properties gp(gid);
  get_property(g, graph_data) = gp;
  get_property(g, graph_name) = "TestGraph";

  cpad::vertex vA = add_vertex(g);
  cpad::vertex vB = add_vertex(vertex_properties("vB"), g);
  cpad::vertex vC = add_vertex(vertex_properties(2, 120), g);
  cpad::vertex vD = add_vertex(vertex_properties(3, 130, "vD"), g);
  cpad::vertex vE = add_vertex(vertex_properties(4, 140, "vE"), g);
  cpad::vertex vF = add_vertex(vertex_properties(5, 150, "vF"), g);

  std::cout << "Vertex vA has valid id = " << (g[vA].has_id() ? "YES" : "NO") << std::endl; 
  std::cout << "Vertex vA id = " << g[vA].id() << std::endl; 
  std::cout << "Vertex vA has valid label = " << (g[vA].has_label() ? "YES" : "NO") << std::endl; 
  std::cout << "Vertex vA label = " << g[vA].label() << std::endl; 
  std::cout << "Vertex vB has valid id = " << (g[vB].has_id() ? "YES" : "NO") << std::endl; 
  std::cout << "Vertex vB id = " << g[vB].id() << std::endl; 
  std::cout << "Vertex vB has valid label = " << (g[vB].has_label() ? "YES" : "NO") << std::endl; 
  std::cout << "Vertex vB label = " << g[vB].label() << std::endl; 

  std::cout << std::endl;
  std::cout << "Setting vA (name = '" << g[vA].get_name() << "') id to 0 ..." << std::endl;
  g[vA].set_name("vA");
  g[vA].set_id(0);
  
  std::cout << "Now vA (name = '" << g[vA].get_name() << "') has valid id = " << (g[vA].has_id() ? "YES" : "NO") << std::endl; 
  std::cout << "Now vA id = ..." << g[vA].id() << std::endl;
  std::cout << "Now vA has valid label = " << (g[vA].has_label() ? "YES" : "NO") << std::endl; 
  std::cout << "Now vA label = ..." << g[vA].label() << std::endl;

  std::cout << std::endl;
  std::cout << "Setting vA to std::make_pair(0, 10) ..." << std::endl;
  g[vA] = std::make_pair(0, 10);
  std::cout << "Now vA has valid id = " << (g[vA].has_id() ? "YES" : "NO") << std::endl; 
  std::cout << "Now vA id = ..." << g[vA].id() << std::endl;
  std::cout << "Now vA has valid label = " << (g[vA].has_label() ? "YES" : "NO") << std::endl; 
  std::cout << "Now vA label = ..." << g[vA].label() << std::endl;

  std::cout << std::endl;
  std::cout << "Working on edges ..." << std::endl;

  bool success;

  cpad::edge eAB;
  cpad::edge eAC;
  tie(eAB, success) = add_edge(vA, vB, g);
  tie(eAC, success) = add_edge(vA, vC, edge_properties(1), g);
  
  cpad::edge eBD;
  cpad::edge eBE;
  tie(eBD, success) = add_edge(vB, vD, edge_properties(4, true), g);
  tie(eBE, success) = add_edge(vB, vE, edge_properties(5), g);
  
  cpad::edge_pair eCA = add_edge(vC, vA, edge_properties(6), g);

  cpad::edge_pair eEF = add_edge(vE, vF, edge_properties(7), g);
  cpad::edge_pair eEC = add_edge(vE, vC, edge_properties(8), g);

  cpad::edge_pair eFB = add_edge(vF, vB, edge_properties(9), g);
  
  std::cout << std::endl;
  std::cout << "Edge AB exists ? " << (boost::edge(vA, vB, g).second ? "YES" : "NO") << std::endl;
  std::cout << "Edge AF exists ? " << (boost::edge(vA, vF, g).second ? "YES" : "NO") << std::endl;

  std::cout << std::endl;
  std::cout << "Edge AB delta = " << g[boost::edge(vA, vB, g).first].delta() << std::endl;
  std::cout << "Edge AB is fallback branch = " << g[boost::edge(vA, vB, g).first].is_fallback_branch() << std::endl;

  std::cout << std::endl;
  std::cout << "Edge AB source vertex has valid id ? " << (g[boost::source(boost::edge(vA, vB, g).first, g)].has_id() ? "YES" : "NO") << std::endl;
  std::cout << "Edge AB source vertex id = " << g[boost::source(boost::edge(vA, vB, g).first, g)].id() << std::endl;
  std::cout << "Edge AB source vertex has valid label ? " << (g[boost::source(boost::edge(vA, vB, g).first, g)].has_label() ? "YES" : "NO") << std::endl;
  std::cout << "Edge AB source vertex label = " << g[boost::source(boost::edge(vA, vB, g).first, g)].label() << std::endl;

  std::cout << std::endl;
  std::cout << "Edge AB target vertex has valid id ? " << (g[boost::target(boost::edge(vA, vB, g).first, g)].has_id() ? "YES" : "NO") << std::endl;
  std::cout << "Edge AB target vertex id = " << g[boost::target(boost::edge(vA, vB, g).first, g)].id() << std::endl;
  std::cout << "Edge AB target vertex has valid label ? " << (g[boost::target(boost::edge(vA, vB, g).first, g)].has_label() ? "YES" : "NO") << std::endl;
  std::cout << "Edge AB target vertex label = " << g[boost::target(boost::edge(vA, vB, g).first, g)].label() << std::endl;

  std::cout << std::endl;
  std::cout << "OutDegré des sommets:" << std::endl;
  // type for vertices is: std::pair<boost::graph_traits<cpad::graph>::vertex_iterator, boost::graph_traits<cpad::graph>::vertex_iterator>
  // type for vit is: boost::graph_traits<cpad::graph>::vertex_iterator
  auto vertices = boost::vertices(g);
  for (auto vit = vertices.first; vit != vertices.second; vit++)
    {
      // type for v is boost::graph_traits<cpad::graph>::vertex_descriptor or cpad::vertex
      auto v = *vit;
      boost::graph_traits<cpad::graph>::vertex_descriptor v2 = *vit;
      cpad::vertex v3 = *vit;

      if (g[v].get_name().length() == 0)
	{
	  cout << ">>> Setting name of vertex with id " << g[v].id() << " to v" << (char)('A' + g[v].id()) << std::endl;
	  std::string newname = "v";
	  newname += (char)('A' + g[v].id());
	  g[v].set_name(newname);
	  cout << ">>> Name of vertex with id " << g[v].id() << " set to " << g[v].name() << std::endl;
	}
      
      std::cout << "* Out degree of vertex " << g[v].get_name() << " id " << g[v].id() << " (" << g[v].label() << ") = " << boost::out_degree(v, g) << std::endl;
      // type for eit is: std::pair<boost::graph_traits<cpad::graph>::in_edge_iterator, boost::graph_traits<cpad::graph>::in_edge_iterator>
      auto edges = out_edges(v, g);
      for (auto eit = edges.first; eit != edges.second; eit++)
	{
	  // type for e is boost::graph_traits<cpad::graph>::edge_descriptor or cpad::edge
	  auto e = *eit;
	  boost::graph_traits<cpad::graph>::edge_descriptor e1 = *eit;
	  cpad::edge e2 = *eit;
	  cout << "    Edge with delta " << g[e].delta() << " go from vertex " << g[v].id() << " to vertex " << g[boost::target(e, g)].id() << "\n";
	}
    }

  std::cout << std::endl;

  cpad::vertex_properties::vertex_writer<cpad::graph> vw(g);
  cpad::edge_properties::edge_writer<cpad::graph> ew(g);
  cpad::graph_properties::graph_writer<cpad::graph> gw(g);

  ofstream outfgv("gv.dot");
  ofstream outfgve("gve.dot");
  ofstream outfgveg("gveg.dot");
  
  write_graphviz(outfgv, g, vw);
  outfgv.close();
  write_graphviz(outfgve, g, vw, ew);
  outfgve.close();
  write_graphviz(outfgveg, g, vw, ew, gw);
  outfgveg.close();  

  std::ofstream oaf("archive.graph");
  boost::archive::binary_oarchive oar(oaf);
  
  oar << g;
  oaf.close();

  cpad::graph restored_g;
  std::ifstream iaf("archive.graph");
  boost::archive::binary_iarchive iar(iaf);

  iar >> restored_g;
  iaf.close();

  ofstream restored_outfgveg("restored_gveg.dot");
  write_graphviz(restored_outfgveg, restored_g, vw, ew, gw);
  restored_outfgveg.close();

  return(0);
}
