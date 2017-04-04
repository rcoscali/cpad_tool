/*
 * Copyright ©2017 NagraFrance
 */

#include "Edge.h"

cpad::Edge::Edge(int delta_value,
		 cpad::Node const* start,
		 cpad::Node const* end)
  : m_delta_value(delta_value),
    _has_delta_value(true),
    _has_start_node(start != (cpad::Node const*)NULL),
    _has_end_node(end != (cpad::Node const*)NULL)
{
  m_nodes_ptr.first = (cpad::Node *)start;
  m_nodes_ptr.second = (cpad::Node *)end;
}

cpad::Edge::Edge()
  : Edge(0, (cpad::Node const*)NULL, (cpad::Node const*)NULL)
{
  _has_delta_value = false;
  _has_start_node = true;
  _has_end_node = true;
}

::cpad::Edge::Edge(Edge const&an_edge_to_copy)
  : Edge(an_edge_to_copy.m_delta_value,
	 an_edge_to_copy.m_nodes_ptr.first,
	 an_edge_to_copy.m_nodes_ptr.second)
{
  _has_delta_value = an_edge_to_copy._has_delta_value;
  _has_start_node = an_edge_to_copy._has_start_node;
  _has_end_node = an_edge_to_copy._has_end_node;
}

::cpad::Edge &
::cpad::Edge::operator =(::cpad::Edge const &an_edge_to_affect)
{
  m_delta_value = an_edge_to_affect.m_delta_value;
  _has_delta_value = an_edge_to_affect._has_delta_value;
  m_nodes_ptr = an_edge_to_affect.m_nodes_ptr;
  _has_start_node = an_edge_to_affect._has_start_node;
  _has_end_node = an_edge_to_affect._has_end_node;
  return (*this);
}

