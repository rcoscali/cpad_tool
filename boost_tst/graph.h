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

    void
      set_id(const uuid_t &id)
    {
      uuid_copy(m_id, id);
    }
    
    template <class Graph>
      class graph_writer
      {
      public:
      graph_writer(Graph _g) : m_g(_g) {}
	template <class VertexOrEdge>
	  void operator()(std::ostream& out, const VertexOrEdge& v) const
	  {
	    char uuidstr[50];

	    uuid_unparse_upper(m_g[v].uuid(), uuidstr);
	    out << "[label=\"" << uuidstr << "\"]";
	  }
	
      private:
	Graph m_g;
      };

  private:
    uuid_t m_id;    
  };
  
  typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS,
				cpad::vertex_properties,
				cpad::edge_properties,
				cpad::graph_properties
				> graph;
  typedef typename boost::graph_traits<cpad::graph>::vertex_descriptor vertex;
  typedef typename boost::graph_traits<cpad::graph>::edge_descriptor edge;
  typedef typename std::pair<edge, bool> edge_pair;
}

#endif /* !_GRAPH_H_ */
