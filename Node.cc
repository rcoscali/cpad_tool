/*
 * Copyright ©2017 NagraFrance
 */

#include <stdexcept>

#include "Node.h"

cpad::Node::Node(shared_ptr<Func> the_func,
                 string name,
		 int add_value,
		 shared_ptr<Edge> edge_d_ptr,
		 shared_ptr<Edge> edge_fb_ptr)
  : m_back_func(the_func),
    m_name(name),
    m_checkpoint((int)0),
    m_add_value(add_value),
    _has_add_value(true),
    _has_edge_d(edge_d_ptr != nullptr),
    _has_edge_fb(edge_fb_ptr != nullptr)
{
  m_edges_ptr.first = edge_d_ptr;
  m_edges_ptr.second = edge_fb_ptr;
}

cpad::Node::Node(shared_ptr<Func> the_func, string name)
  : Node(the_func, name, 0, nullptr, nullptr)
{
  _has_add_value = false;
  _has_edge_d = false;
  _has_edge_fb = false;
}

cpad::Node::Node(void)
  : Node(nullptr, "", 0, nullptr, nullptr)
{
  _has_add_value = false;
  _has_edge_d = false;
  _has_edge_fb = false;
}

cpad::Node::Node(cpad::Node const&a_node_to_copy)
  : Node(a_node_to_copy.m_back_func,
         a_node_to_copy.m_name,
	 a_node_to_copy.m_add_value,
	 a_node_to_copy.m_edges_ptr.first,
	 a_node_to_copy.m_edges_ptr.second)
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
  m_back_func = a_node_to_affect.m_back_func;
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

const int
cpad::Node::get_checkpoint(void)
{
  return (const int)m_checkpoint;
}

void
cpad::Node::set_checkpoint(const int checkpoint)
{
  m_checkpoint = (int)checkpoint;
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

std::pair<shared_ptr<cpad::Edge>, shared_ptr<cpad::Edge>> 
cpad::Node::get_edges(void)
{
  if (! (has_an_edge()))
    throw std::logic_error("This node has no Edge");
  return m_edges_ptr;
}

void
cpad::Node::add_default_edge(shared_ptr<cpad::Edge> an_edge_ptr)
{
  if (_has_edge_fb)
    throw std::logic_error("Node already has fallback edge");
  if (_has_edge_d)
    throw std::logic_error("Node already has a default edge");
  m_edges_ptr.first = an_edge_ptr;
  _has_edge_d = true;
}

void
cpad::Node::add_default_edge(cpad::Edge *&an_edge_ptr)
{
  if (_has_edge_fb)
    throw std::logic_error("Node already has fallback edge");
  if (_has_edge_d)
    throw std::logic_error("Node already has a default edge");
  m_edges_ptr.first = shared_ptr<cpad::Edge>(an_edge_ptr);
  _has_edge_d = true;
}

void
cpad::Node::add_fallback_edge(shared_ptr<cpad::Edge> an_edge_ptr)
{
  if (!_has_edge_d)
    throw std::logic_error("Node has no default edge");
  if (_has_edge_fb)
    throw std::logic_error("Node already has a fallback edge");
  m_edges_ptr.second = an_edge_ptr;
  _has_edge_fb = true;
}

void
cpad::Node::add_fallback_edge(cpad::Edge *&an_edge_ptr)
{
  if (!_has_edge_d)
    throw std::logic_error("Node has no default edge");
  if (_has_edge_fb)
    throw std::logic_error("Node already has a fallback edge");
  m_edges_ptr.second = shared_ptr<cpad::Edge>(an_edge_ptr);
  _has_edge_fb = true;
}

void
cpad::Node::add_edge(shared_ptr<cpad::Edge> an_edge_ptr)
{
  if (!_has_edge_d && !_has_edge_fb)
    {
      m_edges_ptr.first = an_edge_ptr;
      _has_edge_d = true;      
    }
  else if (_has_edge_d && !_has_edge_fb)
    {
      m_edges_ptr.second = an_edge_ptr;
      _has_edge_fb = true;      
    }
  else if (_has_edge_d && _has_edge_fb)
    throw std::logic_error("Node already has both (default/fallback) edge");
  else if (!_has_edge_d && _has_edge_fb)
    throw std::logic_error("Node edge inconsistency (has fallback without default)");
}

void
cpad::Node::add_edge(cpad::Edge *&an_edge_ptr)
{
  if (!_has_edge_d && !_has_edge_fb)
    {
      m_edges_ptr.first = shared_ptr<cpad::Edge>(an_edge_ptr);
      _has_edge_d = true;      
    }
  else if (_has_edge_d && !_has_edge_fb)
    {
      m_edges_ptr.second = shared_ptr<cpad::Edge>(an_edge_ptr);
      _has_edge_fb = true;      
    }
  else if (_has_edge_d && _has_edge_fb)
    throw std::logic_error("Node already has both (default/fallback) edge");
  else if (!_has_edge_d && _has_edge_fb)
    throw std::logic_error("Node edge inconsistency (has fallback without default)");
}

void
cpad::Node::dump(std::ostream &os)
{
  cerr << "Node::dump\n";
  os << "            " << m_name << " [shape=record,style=filled,fillcolor=lightgrey,";
  os << "label=\"{ ADD " << m_add_value << " | " << m_name << " | " << " INC " << m_checkpoint << " }\";];\n";

}

void
cpad::Node::dump_edges(std::ostream &os)
{
  if (m_edges_ptr.first != nullptr)
    m_edges_ptr.first->dump(os);
  if (m_edges_ptr.second != nullptr)
    m_edges_ptr.second->dump(os);
}
