#include <iostream>
#include <boost/graph/adjacency_list.hpp>

namespace cpad
{  
  struct vertex_properties {
  public:
    int m_cp;
    std::string m_name;
    vertex_properties()
      : m_cp(0),
	m_name("")
    {
    }
    vertex_properties(int cp, std::string name)
    {
      m_cp = cp;
      m_name = name;
    }
  };

  struct edge_properties {
    int m_delta;
    bool m_is_fb;

    edge_properties()
      : m_delta (0),
	m_is_fb (false)
    {
    }
    
    edge_properties(int delta, bool is_fb)
      : m_delta (delta),
	m_is_fb (is_fb)
    {
    }
    
  };

  struct graph_properties {
    std::string m_name;

    graph_properties()
      : m_name ("")
    {
    }
    
    graph_properties(std::string name)
      : m_name (name)
    {
    }    
  };

  typedef boost::adjacency_list<boost::vecS, boost::setS, boost::directedS,
				cpad::vertex_properties,
				cpad::edge_properties,
				cpad::graph_properties
				> graph;
  
  typedef typename boost::graph_traits<cpad::graph>::vertex_descriptor vertex;
  typedef typename std::pair<boost::graph_traits<cpad::graph>::edge_descriptor, bool> edge;
  
}

int main(int,char*[])
{
  // Create a graph object
  cpad::graph g(cpad::graph_properties("test_graph"));
  cpad::vertex v0 = boost::add_vertex(cpad::vertex_properties(1, "v0"), g);
  cpad::vertex v1 = boost::add_vertex(cpad::vertex_properties(2, "v1"), g);

  // Check if an edge between v0 and v1 exists. It should not at this point.
  //std::cout << "Graph name = " << get(p, g).m_name << std::endl; 
  std::cout << "Vertex v0: cp = " << g[v0].m_cp << std::endl; 
  std::cout << "Vertex v0: name = " << g[v0].m_name << std::endl; 
  std::cout << "Edge exists? " << (boost::edge(v0, v1, g).second ? "TRUE" : "FALSE") << std::endl; // false
 
  // Add an edge between v0 and v1.
  cpad::edge e0 = boost::add_edge(v0, v1, g);
 
  // Check again if an edge between v0 and v1 exists. It should now.
  std::cout << "Edge exists? " << (boost::edge(v0, v1, g).second ? "TRUE" : "FALSE") << std::endl; // true
 
  // A demonstration of the full return type of edge(). At this point, retrievedEdge.first
  // should be exactly equal to e0
  cpad::edge retrievedEdge = boost::edge(v0, v1, g);
 
  return 0;
}
