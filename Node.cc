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

bool
cpad::Node::operator == (cpad::Node const& right)
{
  return (get_cunit() == ((cpad::Node &)right).get_cunit() &&
          get_func() == ((cpad::Node &)right).get_func() &&
          m_name == right.m_name);
}

bool
cpad::Node::operator != (cpad::Node const& right)
{
  return (get_cunit() != ((cpad::Node &)right).get_cunit() ||
          get_func() != ((cpad::Node &)right).get_func() ||
          m_name != right.m_name);
}

bool
cpad::Node::operator == (shared_ptr<cpad::Node> right)
{
  return (get_cunit() == right->get_cunit() &&
          get_func() == right->get_func() &&
          m_name == right->m_name);
}

bool
cpad::Node::operator != (shared_ptr<cpad::Node> right)
{
  return (get_cunit() != right->get_cunit() ||
          get_func() != right->get_func() ||
          m_name != right->m_name);
}

const char *
cpad::Node::get_func_name(void)
{
  return m_back_func->get_name();
}


shared_ptr<cpad::Func>
cpad::Node::get_func(void)
{
  if (m_back_func == nullptr)
    throw std::logic_error("Node doesn't have owning function");
  return m_back_func;
}

const char *
cpad::Node::get_cunit_name(void)
{
  if (get_func()->get_cunit() == nullptr)
    throw std::logic_error("Node doesn't have owning compilation unit");
  return get_func()->get_cunit()->get_name();
}

shared_ptr<cpad::CUnit>
cpad::Node::get_cunit(void)
{
  return get_func()->get_cunit();
}

const char *
cpad::Node::get_graph_name(const char **out)
{
  if (get_cunit()->get_graph() == nullptr)
    throw std::logic_error("Node doesn't have owning graph");
  return get_cunit()->get_graph()->get_name(out);
}

shared_ptr<cpad::Graph>
cpad::Node::get_graph(void)
{
  return get_cunit()->get_graph();
}

const char*
cpad::Node::get_name(void)
{
  return m_name.c_str();
}

const char*
cpad::Node::get_cluster_name(void)
{
  if (m_cluster_name.empty())
    m_cluster_name = string("func_") + get_func_name() + string("_") + m_name;
  return m_cluster_name.c_str();
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
  else if (_has_edge_d)
    throw std::logic_error("Node already has a default edge");
  else
    {
      m_edges_ptr.first = an_edge_ptr;
      _has_edge_d = true;
    }
}

void
cpad::Node::add_default_edge(cpad::Edge *&an_edge_ptr)
{
  if (_has_edge_fb)
    throw std::logic_error("Node already has fallback edge");
  else if (_has_edge_d)
    throw std::logic_error("Node already has a default edge");
  else
    add_default_edge(shared_ptr<cpad::Edge>(an_edge_ptr));
}

void
cpad::Node::add_fallback_edge(shared_ptr<cpad::Edge> an_edge_ptr)
{
  if (!_has_edge_d)
    throw std::logic_error("Node has no default edge");
  else if (_has_edge_fb)
    throw std::logic_error("Node already has a fallback edge");
  else
    {
      if (*an_edge_ptr == *(m_edges_ptr.first))
        throw std::invalid_argument("Node already has this edge as default edge");
      else
        {
          m_edges_ptr.second = an_edge_ptr;
          _has_edge_fb = true;
        }
    }
}

void
cpad::Node::add_fallback_edge(cpad::Edge *&an_edge_ptr)
{
  if (!_has_edge_d)
    throw std::logic_error("Node has no default edge");
  else if (_has_edge_fb)
    throw std::logic_error("Node already has a fallback edge");
  else
    {
      if (*an_edge_ptr == *(m_edges_ptr.first))
        throw std::invalid_argument("Node already has this edge as default edge");
      else
        add_fallback_edge(shared_ptr<cpad::Edge>(an_edge_ptr));
    }
}

void
cpad::Node::add_edge(shared_ptr<cpad::Edge> an_edge_ptr)
{
  if (!_has_edge_d && !_has_edge_fb)
    add_default_edge(an_edge_ptr);
  
  else if (_has_edge_d && !_has_edge_fb)
    add_fallback_edge(an_edge_ptr);
  
  else if (_has_edge_d && _has_edge_fb)
    throw std::logic_error("Node already has both (default/fallback) edge");
  else
    throw std::logic_error("Node edge inconsistency (has fallback without default)");
}

void
cpad::Node::add_edge(cpad::Edge *&an_edge_ptr)
{
  if (!_has_edge_d && !_has_edge_fb)
    add_default_edge(shared_ptr<cpad::Edge>(an_edge_ptr));

  else if (_has_edge_d && !_has_edge_fb)
    add_fallback_edge(shared_ptr<cpad::Edge>(an_edge_ptr));

  else if (_has_edge_d && _has_edge_fb)
    throw std::logic_error("Node already has both (default/fallback) edge");
  else
    throw std::logic_error("Node edge inconsistency (has fallback without default)");
}

void
cpad::Node::dump(std::ostream &os)
{
  os << "            " << get_cluster_name() << " [";
  os << "label=<<TABLE BGCOLOR=\"white\" BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\"><TR><TD><FONT POINT-SIZE=\"12.0\" FACE=\"Courier New\">ChkAdd</FONT></TD><TD ";
  os << "BGCOLOR=\"#c0c0c0\" PORT=\"here\"><FONT COLOR=\"red\" POINT-SIZE=\"12.0\">" << m_checkpoint << "</FONT></TD><TD>" << m_add_value << "</TD></TR><TR><TD ";
  os << "COLSPAN=\"3\">" << m_name << "</TD></TR><TR><TD COLSPAN=\"2\"><FONT POINT-SIZE=\"12.0\" FACE=\"Courier New,italic\">ChkInc</FONT></TD><TD BGCOLOR=\"#c0c0c0\"><FONT COLOR=\"red\">";
  os << m_checkpoint << "</FONT></TD></TR></TABLE>>];\n";
}

void
cpad::Node::dump_in_edges(std::ostream &os)
{
  if (m_edges_ptr.first != nullptr)
    m_edges_ptr.first->dump_in(os);
  if (m_edges_ptr.second != nullptr)
    m_edges_ptr.second->dump_in(os);
}

void
cpad::Node::dump_out_edges(std::ostream &os)
{
  if (m_edges_ptr.first != nullptr)
    m_edges_ptr.first->dump_out(os);
  if (m_edges_ptr.second != nullptr)
    m_edges_ptr.second->dump_out(os);
}

void
cpad::Node::dump_outer_edges(std::ostream &os)
{
  if (m_edges_ptr.first != nullptr)
    m_edges_ptr.first->dump_outer(os);
  if (m_edges_ptr.second != nullptr)
    m_edges_ptr.second->dump_outer(os);
}

void
cpad::Node::add_ancestor(const weak_ptr<cpad::Node> &a_weak_node_ptr)
{
  m_ancestors.push_back(a_weak_node_ptr);
}

void
cpad::Node::add_ancestor(const shared_ptr<cpad::Node> &a_shared_node_ptr)
{
  add_ancestor(weak_ptr<cpad::Node>(a_shared_node_ptr));
}

cpad::Node::HasNodeAsAncestor::HasNodeAsAncestor(shared_ptr<cpad::Node> the_node_ptr_to_check)
  : has_node(false),
    the_node_ptr(the_node_ptr_to_check)
{
};
      
void
cpad::Node::HasNodeAsAncestor::operator ()(weak_ptr<cpad::Node> const &a_node_weak_ptr)
{
  if (!has_node)
    {
      auto a_node_ptr = a_node_weak_ptr.lock();
      if (a_node_ptr != nullptr && *a_node_ptr == *the_node_ptr)
        has_node = true;
    }
}

bool
cpad::Node::has_ancestor(const weak_ptr<cpad::Node> &a_node_ptr)
{
  auto a_shared_node_ptr = a_node_ptr.lock();
  if (a_shared_node_ptr != nullptr)
    return has_ancestor(a_shared_node_ptr);
  return false;
}

bool
cpad::Node::has_ancestor(const shared_ptr<cpad::Node> &a_node_ptr)
{
  cpad::Node::HasNodeAsAncestor functor
    = std::for_each(m_ancestors.begin(),
                    m_ancestors.end(),
                    cpad::Node::HasNodeAsAncestor(a_node_ptr));
  return functor.has_node_as_ancestor();
}

void
cpad::Node::compute_ancestors()
{
  for (auto it = get_graph()->m_all_nodes.begin();
       it != get_graph()->m_all_nodes.end();
       it++)
    {
      if (auto node_ptr = (*it).lock())
        {
          if (node_ptr->m_edges_ptr.first != nullptr &&
              *this == *(node_ptr->m_edges_ptr.first->get_nodes().second) &&
              !has_ancestor(node_ptr->m_edges_ptr.first->get_nodes().first))
            add_ancestor(node_ptr->m_edges_ptr.first->get_nodes().first);

          if (node_ptr->m_edges_ptr.second != nullptr &&
              *this == *(node_ptr->m_edges_ptr.second->get_nodes().second) &&
              !has_ancestor(node_ptr->m_edges_ptr.second->get_nodes().first))
            add_ancestor(node_ptr->m_edges_ptr.second->get_nodes().first);
        }
    }
}

void
cpad::Node::dump_ancestors(void)
{
  cerr << "Node " << get_name() << " has " << m_ancestors.size() << " ancestors:";
  for (auto it = m_ancestors.begin();
       it != m_ancestors.end();
       it++)
    {
      if (auto node = (*it).lock())
        cerr << "  " << node->get_name();
    }
  cerr << "\n";
}
