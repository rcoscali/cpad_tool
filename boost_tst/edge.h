/**
 * @file edge.h
 *
 */

#ifndef _EDGE_H_
#define _EDGE_H_

#include <utility>

#include <boost/serialization/access.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/binary_object.hpp>
#include <boost/serialization/split_member.hpp>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

#include <boost/graph/properties.hpp>
#include <boost/graph/graph_concepts.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/adj_list_serialize.hpp>
#include <boost/graph/graphviz.hpp>

#include "vertex.h"

using namespace std;

namespace cpad
{
  class edge_properties
  {
  public:
    edge_properties()
      : edge_properties(0)
    {};
    edge_properties(int delta, bool is_fb = false)
      : m_delta(delta),
        m_is_fb(is_fb)
    {};
    virtual ~edge_properties() {};
    edge_properties(edge_properties const &an_edge)
      : m_delta(an_edge.m_delta),
        m_is_fb(an_edge.m_is_fb) {};
    edge_properties &operator = (edge_properties const &an_edge)
      {
	m_delta = an_edge.m_delta;
	m_is_fb = an_edge.m_is_fb;
	return (*this);
      };

    const int
      delta(void) const
    {
      return get_delta();
    }

    const int
      get_delta(void) const
    {
      return m_delta;
    }

    void
      set_delta(const int delta)
    {
      m_delta = delta;
    }

    const bool
      is_fallback_branch(void) const
    {
      return m_is_fb;
    }

    void set_fallback_branch()
    {
      m_is_fb = true;
    }

    void set_default_branch()
    {
      m_is_fb = false;
    }

    template <class Graph>
      class edge_writer
      {
      public:
      edge_writer(Graph _g) : m_g(_g) {}
	template <class VertexOrEdge>
	  void operator()(std::ostream& out, const VertexOrEdge& v) const
	  {
	    out << "[label=\"" << m_g[v].delta() << "\"]";
	  }
	
      private:
	Graph m_g;
      };
    
    BOOST_SERIALIZATION_SPLIT_MEMBER ();
    
  private:
    friend class boost::serialization::access;

    template <typename Archive>
      void save(Archive &ar, const unsigned int version)
      {
	ar & version;
	ar & m_delta;
	ar & m_is_fb;
      }
    
    template <typename Archive>
      void load(Archive &ar, const unsigned int version)
      {
        unsigned int archive_version;
	ar & archive_version;
        if (version == archive_version)
          {
            ar & m_delta;
            ar & m_is_fb;
          }
      }
    
    int m_delta;
    bool m_is_fb;    
  };
}

BOOST_CLASS_VERSION(cpad::edge_properties, 1);

#endif /* !_EDGE_H_ */
