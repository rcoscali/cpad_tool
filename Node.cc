/*
 * Copyright ©2017 NagraFrance
 */

#include <stdexcept>

#include "Node.h"

cpad::Node::Node(string name,
		 int add_value,
		 Edge const* edge_d_ptr,
		 Edge const* edge_fb_ptr)
  : m_name(name),
    m_add_value(add_value),
    _has_add_value(true),
    _has_edge_d(edge_d_ptr != (Edge const*)NULL),
    _has_edge_fb(edge_fb_ptr != (Edge const*)NULL)
{
  m_edges_ptr.first = (cpad::Edge *)edge_d_ptr;
  m_edges_ptr.second = (cpad::Edge *)edge_fb_ptr;
}

cpad::Node::Node(string name)
  : Node(name, 0, (cpad::Edge const*)NULL, (cpad::Edge const*)NULL)
{
  _has_add_value = false;
  _has_edge_d = false;
  _has_edge_fb = false;
}

cpad::Node::Node(cpad::Node const&a_node_to_copy)
  : Node(m_name,
	 m_add_value,
	 m_edges_ptr.first,
	 m_edges_ptr.second)
{
  _has_add_value = a_node_to_copy._has_add_value;
  _has_edge_d = a_node_to_copy._has_edge_d;
  _has_edge_fb = a_node_to_copy._has_edge_fb;
}

cpad::Node::~Node()
{
}

cpad::Node&
cpad::Node::operator = (cpad::Node const&a_node_to_affect)
{
  m_name = a_node_to_affect.m_name;
  m_add_value = a_node_to_affect.m_add_value;
  _has_add_value = a_node_to_affect._has_add_value;
  m_edges_ptr = a_node_to_affect.m_edges_ptr;
  _has_edge_d = a_node_to_affect._has_edge_d;
  _has_edge_fb = a_node_to_affect._has_edge_fb;
  return (*this);
}

const char*
cpad::Node::get_name(void)
{
  return m_name.c_str();
}

bool
cpad::Node::has_add_value(void)
{
  return _has_add_value;
}

int
cpad::Node::get_add_value(void)
{
  if (!_has_add_value)
    throw std::logic_error("Node don't have an add_value");
  return m_add_value;
}

void
cpad::Node::set_add_value(int add_value)
{
  if (_has_add_value)
    throw std::logic_error("Node already have add value");
  m_add_value = add_value;
  _has_add_value = true;
}

bool
cpad::Node::has_an_edge(void)
{
  return _has_edge_d || _has_edge_fb;
}

std::pair<cpad::Edge *, cpad::Edge *> 
cpad::Node::get_edges(void)
{
  if (! (has_an_edge()))
    throw std::logic_error("This node has no Edge");
  return m_edges_ptr;
}

void
cpad::Node::add_default_edge(cpad::Edge const* an_edge_ptr)
{
  m_edges_ptr.first = (cpad::Edge *)an_edge_ptr;
}

void
cpad::Node::add_fallback_edge(cpad::Edge const* an_edge_ptr)
{
  m_edges_ptr.second = (cpad::Edge *)an_edge_ptr;
}
