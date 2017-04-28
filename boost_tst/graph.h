/**
 * @file graph.h
 *
 */

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <uuid/uuid.h>

#include <iostream>
#include <utility>
#include <algorithm>
#include <boost/graph/properties.hpp>
#include <boost/graph/adjacency_list.hpp>

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

  private:
    uuid_t m_id;    
  };
  

  using GraphProperties = boost::property<boost::graph_data_t, graph_properties>;

  typedef typename boost::adjacency_list<
    boost::vecS, boost::vecS, boost::bidirectionalS,
    cpad::vertex_properties,
    cpad::edge_properties,
    boost::property<boost::graph_name_t, std::string, boost::property<boost::graph_data_t, graph_properties>>
    > graph;
  using vertex_t = boost::graph_traits<cpad::graph>::vertex_descriptor;
  typedef typename boost::graph_traits<cpad::graph>::vertex_descriptor vertex;
  typedef typename boost::graph_traits<cpad::graph>::edge_descriptor edge;
  typedef typename std::pair<edge, bool> edge_pair;

} // namespace cpad

#endif /* !_GRAPH_H_ */
