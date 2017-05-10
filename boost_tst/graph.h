/**
 * @file graph.h
 *
 */

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <uuid/uuid.h>

#include <map>
#include <iostream>
#include <utility>
#include <algorithm>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

#include <boost/serialization/map.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/binary_object.hpp>
#include <boost/serialization/split_member.hpp>

#include <boost/graph/properties.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/adj_list_serialize.hpp>

#include "vertex.h"
#include "edge.h"

using namespace std;

namespace boost {
    enum graph_data_t { graph_data };
    BOOST_INSTALL_PROPERTY(graph, data);
}

namespace cpad
{
  const uuid_t INVALID_GRAPH_ID = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  
  class graph_properties
  {    
  public:
    
    graph_properties() : graph_properties(INVALID_GRAPH_ID) {};
    graph_properties(const uuid_t &id)
      {
	uuid_copy(m_id, id);
      };
    virtual ~graph_properties() {};
    graph_properties(const graph_properties &a_graph_to_copy)
      {
	uuid_copy(m_id, a_graph_to_copy.m_id);
      };

    const uuid_t &
      get_id(void)
    {
      return m_id;
    }

    const uuid_t &
      id(void)
    {
      return get_id();
    }

    const char *
      get_name(char *out)
    {
      uuid_unparse_upper(m_id, out);
      return out;
    }

    void
      set_id(const uuid_t &id)
    {
      uuid_copy(m_id, id);
    }

    template <class Graph>
      class graph_writer
      {
      public:
      graph_writer(Graph g) : m_g(g) {};
	void operator()(std::ostream& out) const
	{
	  char nstr[50];
	  
	  std::string gname = get_property(m_g, graph_name);
	  graph_properties gp = get_property(m_g, graph_data);
	  
	  out << "graph [bgcolor=lightgrey]" << std::endl;
	  out << "node [shape=record color=white]" << std::endl;
	  out << "edge [style=dashed]" << std::endl;
	  out << "label=\"" << gname << "/" << gp.get_name(nstr) << "\"" << std::endl;
	}

      private:
	Graph m_g;
      };
  
    BOOST_SERIALIZATION_SPLIT_MEMBER ();
    
  private:
    friend class boost::serialization::access;

    template <typename Archive>
      void save(Archive &ar, const unsigned int version) const
      {
	ar & version;
	ar
	  & m_id[ 5] & m_id[ 9] & m_id[ 4] & m_id[11] 
	  & m_id[ 6] & m_id[15] & m_id[13] & m_id[ 3]
	  & m_id[10] & m_id[ 8] & m_id[ 0] & m_id[ 7] 
	  & m_id[12] & m_id[ 2] & m_id[14] & m_id[ 1]; 
      }
    
    template <typename Archive>
      void load(Archive &ar, const unsigned int version)
      {
        unsigned int archive_version;
	ar & archive_version;
        if (version == archive_version)
          {
            ar
              & m_id[ 5] & m_id[ 9] & m_id[ 4] & m_id[11] 
              & m_id[ 6] & m_id[15] & m_id[13] & m_id[ 3]
              & m_id[10] & m_id[ 8] & m_id[ 0] & m_id[ 7] 
              & m_id[12] & m_id[ 2] & m_id[14] & m_id[ 1]; 
          }
      }
    
    uuid_t m_id;    
  };
  
  using GraphProperties = boost::property<boost::graph_data_t, graph_properties>;
  using GraphvizAttributes = std::map<std::string, std::string>;

  typedef typename boost::adjacency_list<
    boost::vecS, boost::vecS, boost::bidirectionalS,
    // Vertex Properties: graphviz attrs & our vertex properties
    boost::property<boost::vertex_attribute_t, GraphvizAttributes,
                    boost::property<boost::vertex_data_t, cpad::vertex_properties>
                   >,
    // Edge properties: edge index, graphviz attrs & our edge properties
    boost::property<boost::edge_index_t, int,
                    boost::property<boost::edge_attribute_t, cpad::GraphvizAttributes,
                                    boost::property<boost::edge_data_t, cpad::edge_properties>
                                   >
                   >,
    boost::property<boost::graph_name_t, std::string,
                    boost::property<boost::graph_graph_attribute_t, cpad::GraphvizAttributes,
                                    boost::property<boost::graph_vertex_attribute_t, cpad::GraphvizAttributes,
					            boost::property<boost::graph_edge_attribute_t, cpad::GraphvizAttributes,
                                                                    boost::property<boost::graph_data_t, cpad::graph_properties>
                                                                   >
                                                   >
                                   >
                   >
    > graph;
  //using vertex_t = boost::graph_traits<cpad::graph>::vertex_descriptor;
  typedef typename boost::graph_traits<cpad::graph>::vertex_descriptor vertex;
  typedef boost::property_map<cpad::graph, boost::vertex_data_t> vertex_properties_map_t;
  typedef typename boost::graph_traits<cpad::graph>::edge_descriptor edge;
  typedef boost::property_map<cpad::graph, boost::edge_data_t> edge_properties_map_t;
  typedef typename std::pair<edge, bool> edge_pair;

} // namespace cpad

BOOST_CLASS_VERSION(cpad::graph_properties, 1);

#endif /* !_GRAPH_H_ */
