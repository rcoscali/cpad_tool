/*
 * Copyright ©2017 NagraFrance
 */

#include "Edge.h"

cpad::Edge::Edge(int delta_value,
		 shared_ptr<cpad::Node> start,
		 shared_ptr<cpad::Node> end)
  : m_delta_value(delta_value),
    _has_delta_value(true),
    _has_start_node(start != nullptr),
    _has_end_node(end != nullptr)
{
  m_nodes_ptr.first = start;
  m_nodes_ptr.second = end;
}

cpad::Edge::Edge(shared_ptr<cpad::Node> start,
		 shared_ptr<cpad::Node> end)
  : Edge(0, start, end)
{
  _has_delta_value = false;
  m_nodes_ptr.first = start;
  m_nodes_ptr.second = end;
}

cpad::Edge::Edge(cpad::Node const *start,
		 cpad::Node const *end)
  : Edge(0, shared_ptr<cpad::Node>((cpad::Node *)start), shared_ptr<cpad::Node>((cpad::Node *)end))
{
  _has_delta_value = false;
  m_nodes_ptr.first = shared_ptr<cpad::Node>((cpad::Node *)start);
  m_nodes_ptr.second = shared_ptr<cpad::Node>((cpad::Node *)end);
}

cpad::Edge::Edge()
  : Edge(0, nullptr, nullptr)
{
  _has_delta_value = false;
  _has_start_node = true;
  _has_end_node = true;
}

cpad::Edge::Edge(Edge const&an_edge_to_copy)
  : Edge(an_edge_to_copy.m_delta_value,
	 an_edge_to_copy.m_nodes_ptr.first,
	 an_edge_to_copy.m_nodes_ptr.second)
{
  _has_delta_value = an_edge_to_copy._has_delta_value;
  _has_start_node = an_edge_to_copy._has_start_node;
  _has_end_node = an_edge_to_copy._has_end_node;
}

cpad::Edge::~Edge(void)
{
}

cpad::Edge &
cpad::Edge::operator =(::cpad::Edge const &an_edge_to_affect)
{
  m_delta_value = an_edge_to_affect.m_delta_value;
  _has_delta_value = an_edge_to_affect._has_delta_value;
  m_nodes_ptr = an_edge_to_affect.m_nodes_ptr;
  _has_start_node = an_edge_to_affect._has_start_node;
  _has_end_node = an_edge_to_affect._has_end_node;
  return (*this);
}

int
cpad::Edge::get_delta_value(void)
{
  return m_delta_value;
}

std::pair<shared_ptr<cpad::Node>, shared_ptr<cpad::Node>>
cpad::Edge::get_nodes(void)
{
  return m_nodes_ptr;
}

void
cpad::Edge::dump_in(std::ostream &os)
{
  cerr << "Edge::dump_in\n";
  shared_ptr<Node> start = m_nodes_ptr.first;
  shared_ptr<Node> end = m_nodes_ptr.second;
  if (start != nullptr &&
      end != nullptr &&
      start->get_func() == end->get_func())
    {
      os << "            func_" << start->get_func_name() << "_" << start->get_name();
      os << ":s -> ";
      os << "func_" << end->get_func_name() << "_" << end->get_name() << "";
      os << " [style=\"solid,bold\",color=black,weight=5,label=\"[" << m_delta_value << "]\"];\n";
    }
}

void
cpad::Edge::dump_out(std::ostream &os)
{
  cerr << "Edge::dump_out\n";
  shared_ptr<Node> start = m_nodes_ptr.first;
  shared_ptr<Node> end = m_nodes_ptr.second;
  if (start != nullptr &&
      end != nullptr &&
      start->get_func() != end->get_func())
    {
      os << "        func_" << start->get_func_name() << "_" << start->get_name();
      os << ":s -> ";
      os << "func_" << end->get_func_name() << "_" << end->get_name() << "";
      os << " [style=\"solid,bold\",color=black,weight=5,label=\"[" << m_delta_value << "]\"];\n";
    }
}

