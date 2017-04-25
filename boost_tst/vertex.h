/**
 * @file vertex.h
 *
 */

#ifndef _VERTEX_H_
#define _VERTEX_H_

#include <boost/config.hpp>
#include <boost/utility.hpp>                // for boost::tie
#include <boost/graph/properties.hpp>
#include <boost/graph/graph_concepts.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>

using namespace std;
using namespace boost;

namespace cpad
{
  enum vertex_ids
  {
    INVALID_VERTEX_ID = 0xffffffff
  };
  
  enum vertex_labels
  {
    INVALID_LABEL = 0xffffffff,
    UNALLOCATED_LABEL = 0xffffffff,
  };
  
  class vertex_properties
  {
    
  public:

    // Default constructor
  vertex_properties()
    : vertex_properties(INVALID_VERTEX_ID, INVALID_LABEL)
      {};

    // Explicit constructor
  vertex_properties(unsigned int id, unsigned int label)
    : m_id(id),
      m_label(label)
      {};

    // Destructor
    virtual ~vertex_properties()
      {};

    // Copy constructor
    vertex_properties(vertex_properties const &);

    // Affectation operator
    vertex_properties &operator = (vertex_properties const &);

    // Affectation operator with pair<uint, uint>
    vertex_properties &operator = (std::pair<unsigned int, unsigned int> const &);

    // Equality operator
    bool operator == (vertex_properties const &);

    // Not Equality operator
    bool operator != (vertex_properties const &);

    unsigned int id(void)
    {
      return get_id();
    };
    
    unsigned int get_id(void)
    {
      return m_id;
    };
    
    void set_id(unsigned int id)
    {
      m_id = id;
    };
    
    bool has_id(void)
    {
      return (m_id != INVALID_VERTEX_ID);
    }

    unsigned int label(void)
    {
      return get_label();
    };
    
    unsigned int get_label(void)
    {
      return m_label;
    };
    
    void set_label(unsigned int label)
    {
      m_label = label;
    };

    bool has_label(void)
    {
      return (m_label != UNALLOCATED_LABEL);
    }
    
  private:
    
    unsigned int m_id;
    unsigned int m_label;
  };

  /**
   * Copy constructor
   */
  vertex_properties::vertex_properties(vertex_properties const &a_vertex_to_copy)
    {
      m_id = a_vertex_to_copy.m_id;
      m_label = a_vertex_to_copy.m_label;
    }

  /**
   * Affectation operator
   */
  vertex_properties &
    vertex_properties::operator = (vertex_properties const &a_vertex_to_affect)
    {
      m_id = a_vertex_to_affect.m_id;
      m_label = a_vertex_to_affect.m_label;
      return (*this);
    }

  /**
   * Affectation operator
   */
  vertex_properties &
    vertex_properties::operator = (std::pair<unsigned int, unsigned int> const &a_pair_to_affect)
    {
      m_id = a_pair_to_affect.first;
      m_label = a_pair_to_affect.second;
      return (*this);
    }

  /**
   * Equality operator
   */
  bool
    vertex_properties::operator == (vertex_properties const &a_vertex_to_cmp)
    {
      bool ret = false;

      ret = (m_id == a_vertex_to_cmp.m_id && m_label == a_vertex_to_cmp.m_label);
      return ret;
    }

  /**
   * None Equality operator
   */
  bool
    vertex_properties::operator != (vertex_properties const &a_vertex_to_cmp)
    {
      bool ret = false;

      ret = !(*this == a_vertex_to_cmp);
      return ret;
    }
}

#endif /* !_VERTEX_H_ */
