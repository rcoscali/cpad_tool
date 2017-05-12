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
#include <boost/graph/subgraph.hpp>
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

int
main(int argc, char **argv)
{
  using namespace cpad;
  using namespace boost;
  
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

  subgraph<cpad::graph> g;

  boost::subgraph<cpad::graph> cunit1 = g.create_subgraph();
  get_property(cunit1, graph_name) = std::string("CUnit1");
  boost::subgraph<cpad::graph> func11 = cunit1.create_subgraph();
  get_property(func11, graph_name) = std::string("Func 1-1");
  boost::subgraph<cpad::graph> func12 = cunit1.create_subgraph();
  get_property(func12, graph_name) = std::string("Func 1-2");
  
  boost::subgraph<cpad::graph> cunit2 = g.create_subgraph();
  get_property(cunit2, graph_name) = std::string("CUnit2");
  boost::subgraph<cpad::graph> func21 = cunit2.create_subgraph();
  get_property(func21, graph_name) = std::string("Func 2-1");
  boost::subgraph<cpad::graph> func22 = cunit2.create_subgraph();
  get_property(func22, graph_name) = std::string("Func 2-2");

  typename boost::property_map<cpad::graph, boost::vertex_data_t>::type vertexmap = get(vertex_data, g.m_graph);
  typename boost::property_map<cpad::graph, boost::edge_data_t>::type edgemap = get(edge_data, g.m_graph);

  uuid_t gid;
  uuid_generate_time(gid);
  graph_properties gp(gid);
  get_property(g.m_graph, graph_data) = gp;
  get_property(g.m_graph, graph_name) = "TestGraph";

  cpad::vertex vA = add_vertex(func11);
  cpad::vertex_properties vB_props = vertex_properties("vB");
  cpad::vertex vB = add_vertex(func11);
  vertexmap[vB] = vB_props;
  cpad::vertex_properties vC_props = vertex_properties(2, 120);
  cpad::vertex vC = add_vertex(func12);
  vertexmap[vC] = vC_props;
  cpad::vertex_properties vD_props = vertex_properties(3, 130, "vD");
  cpad::vertex vD = add_vertex(func12);
  vertexmap[vD] = vD_props;
  cpad::vertex_properties vE_props = vertex_properties(4, 140, "vE");
  cpad::vertex vE = add_vertex(func21);
  vertexmap[vE] = vE_props;
  cpad::vertex_properties vF_props = vertex_properties(5, 150, "vF");
  cpad::vertex vF = add_vertex(func22);
  vertexmap[vF] = vF_props;

  std::cout << "Vertex vA has valid id = " << (vertexmap[vA].has_id() ? "YES" : "NO") << std::endl; 
  std::cout << "Vertex vA id = " << vertexmap[vA].id() << std::endl; 
  std::cout << "Vertex vA has valid label = " << (vertexmap[vA].has_label() ? "YES" : "NO") << std::endl; 
  std::cout << "Vertex vA label = " << vertexmap[vA].label() << std::endl; 
  std::cout << "Vertex vB has valid id = " << (vertexmap[vB].has_id() ? "YES" : "NO") << std::endl; 
  std::cout << "Vertex vB id = " << vertexmap[vB].id() << std::endl; 
  std::cout << "Vertex vB has valid label = " << (vertexmap[vB].has_label() ? "YES" : "NO") << std::endl; 
  std::cout << "Vertex vB label = " << vertexmap[vB].label() << std::endl; 

  std::cout << std::endl;
  std::cout << "Setting vA (name = '" << vertexmap[vA].get_name() << "') id to 0 ..." << std::endl;
  vertexmap[vA].set_name("vA");
  vertexmap[vA].set_id(0);
  
  std::cout << "Now vA (name = '" << vertexmap[vA].get_name() << "') has valid id = " << (vertexmap[vA].has_id() ? "YES" : "NO") << std::endl; 
  std::cout << "Now vA id = ..." << vertexmap[vA].id() << std::endl;
  std::cout << "Now vA has valid label = " << (vertexmap[vA].has_label() ? "YES" : "NO") << std::endl; 
  std::cout << "Now vA label = ..." << vertexmap[vA].label() << std::endl;

  std::cout << std::endl;
  std::cout << "Setting vA to std::make_pair(0, 10) ..." << std::endl;
  vertexmap[vA] = std::make_pair(0, 10);
  std::cout << "Now vA has valid id = " << (vertexmap[vA].has_id() ? "YES" : "NO") << std::endl; 
  std::cout << "Now vA id = ..." << vertexmap[vA].id() << std::endl;
  std::cout << "Now vA has valid label = " << (vertexmap[vA].has_label() ? "YES" : "NO") << std::endl; 
  std::cout << "Now vA label = ..." << vertexmap[vA].label() << std::endl;

  std::cout << std::endl;
  std::cout << "Working on edges ..." << std::endl;

  bool success;

  cpad::edge eAB;
  cpad::edge eAC;
  tie(eAB, success) = add_edge(vA, vB, g);
  tie(eAC, success) = add_edge(vA, vC, g);
  edge_properties eAC_props = edge_properties(1);
  
  cpad::edge eBD;
  cpad::edge eBE;
  tie(eBD, success) = add_edge(vB, vD, g);
  cpad::edge_properties eBD_props = edge_properties(4, true);
  edgemap[eBD] = eBD_props;

  tie(eBE, success) = add_edge(vB, vE, g);
  cpad::edge_properties eBE_props = edge_properties(5);
  edgemap[eBE] = eBE_props;
  
  cpad::edge_pair eCA_pair = add_edge(vC, vA, g);
  cpad::edge_properties eCA_props = edge_properties(6);
  edgemap[eCA_pair.first] = eCA_props;

  cpad::edge_pair eEF_pair = add_edge(vE, vF, g);
  cpad::edge_properties eEF_props = edge_properties(7);
  edgemap[eEF_pair.first] = eEF_props;
  
  cpad::edge_pair eEC_pair = add_edge(vE, vC, g);
  cpad::edge_properties eEC_props = edge_properties(8);
  edgemap[eEC_pair.first] = eEC_props;

  cpad::edge_pair eFB_pair = add_edge(vF, vB, g);
  cpad::edge_properties eFB_props = edge_properties(9);
  edgemap[eFB_pair.first] = eFB_props;
  
  std::cout << std::endl;
  std::cout << "Edge AB exists ? " << (boost::edge(vA, vB, g).second ? "YES" : "NO") << std::endl;
  std::cout << "Edge AF exists ? " << (boost::edge(vA, vF, g).second ? "YES" : "NO") << std::endl;

  std::cout << std::endl;
  std::cout << "Edge AB delta = " << edgemap[boost::edge(vA, vB, g).first].delta() << std::endl;
  std::cout << "Edge AB is fallback branch = " << edgemap[boost::edge(vA, vB, g).first].is_fallback_branch() << std::endl;

  std::cout << std::endl;
  std::cout << "Edge AB source vertex has valid id ? " << (vertexmap[boost::source(boost::edge(vA, vB, g).first, g)].has_id() ? "YES" : "NO") << std::endl;
  std::cout << "Edge AB source vertex id = " << vertexmap[boost::source(boost::edge(vA, vB, g).first, g)].id() << std::endl;
  std::cout << "Edge AB source vertex has valid label ? " << (vertexmap[boost::source(boost::edge(vA, vB, g).first, g)].has_label() ? "YES" : "NO") << std::endl;
  std::cout << "Edge AB source vertex label = " << vertexmap[boost::source(boost::edge(vA, vB, g).first, g)].label() << std::endl;

  std::cout << std::endl;
  std::cout << "Edge AB target vertex has valid id ? " << (vertexmap[boost::target(boost::edge(vA, vB, g).first, g)].has_id() ? "YES" : "NO") << std::endl;
  std::cout << "Edge AB target vertex id = " << vertexmap[boost::target(boost::edge(vA, vB, g).first, g)].id() << std::endl;
  std::cout << "Edge AB target vertex has valid label ? " << (vertexmap[boost::target(boost::edge(vA, vB, g).first, g)].has_label() ? "YES" : "NO") << std::endl;
  std::cout << "Edge AB target vertex label = " << vertexmap[boost::target(boost::edge(vA, vB, g).first, g)].label() << std::endl;

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

      if (vertexmap[v].get_name().length() == 0)
	{
	  cout << ">>> Setting name of vertex with id " << vertexmap[v].id() << " to v" << (char)('A' + vertexmap[v].id()) << std::endl;
	  std::string newname = "v";
	  newname += (char)('A' + vertexmap[v].id());
	  vertexmap[v].set_name(newname);
	  cout << ">>> Name of vertex with id " << vertexmap[v].id() << " set to " << vertexmap[v].name() << std::endl;
	}
      
      std::cout << "* Out degree of vertex " << vertexmap[v].get_name() << " id " << vertexmap[v].id() << " (" << vertexmap[v].label() << ") = " << boost::out_degree(v, g) << std::endl;
      // type for eit is: std::pair<boost::graph_traits<cpad::graph>::in_edge_iterator, boost::graph_traits<cpad::graph>::in_edge_iterator>
      auto edges = out_edges(v, g);
      for (auto eit = edges.first; eit != edges.second; eit++)
	{
	  // type for e is boost::graph_traits<cpad::graph>::edge_descriptor or cpad::edge
	  auto e = *eit;
	  boost::graph_traits<cpad::graph>::edge_descriptor e1 = *eit;
	  cpad::edge e2 = *eit;
	  cout << "    Edge with delta " << edgemap[e].delta() << " go from vertex " << vertexmap[v].id() << " to vertex " << vertexmap[boost::target(e, g)].id() << "\n";
	}
    }

  std::cout << std::endl;

  //cpad::vertex_properties::vertex_writer<cpad::graph> vw(g);
  //cpad::edge_properties::edge_writer<cpad::graph> ew(g);
  cpad::graph_properties::graph_writer<cpad::graph> gw(g);

  //ofstream outfgv("gv.dot");
  //ofstream outfgve("gve.dot");
  ofstream outfgveg("gveg.dot");
  
  //write_graphviz(outfgv, g, vw);
  //outfgv.close();
  //write_graphviz(outfgve, g, vw, ew);
  //outfgve.close();
  write_graphviz(outfgveg, g, vw, ew, gw);
  outfgveg.close();  

  std::ofstream oaf("archive.graph");
  boost::archive::binary_oarchive oar(oaf);
  
  oar << (const cpad::graph)g.m_graph;
  oaf.close();

  subgraph<cpad::graph> restored_g;
  std::ifstream iaf("archive.graph");
  boost::archive::binary_iarchive iar(iaf);

  iar >> restored_g.m_graph;
  iaf.close();

  ofstream restored_outfgveg("restored_gveg.dot");
  write_graphviz(restored_outfgveg, restored_g, vw, ew, gw);
  restored_outfgveg.close();

  return(0);
}
