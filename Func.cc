/*
 * Copyright ©2017 NagraFrance
 */

#include <string>

#include "Func.h"

using namespace std;

namespace cpad
{
  Func::Func(void)
    : m_entry(nullptr),
      _has_entry(false),
      m_back_cunit(nullptr),
      m_name("")
  {
  }

  Func::Func(shared_ptr<CUnit> the_cunit, string name)
    : Func()
  {
    m_back_cunit = the_cunit;
    m_name = name;
  }
  
  Func::Func(Func const& a_copy)
    : Func()
  {
    m_entry = a_copy.m_entry;
    _has_entry = a_copy._has_entry;
    m_back_cunit = a_copy.m_back_cunit;
    m_name = a_copy.m_name;
  }

  Func::~Func(void)
  {
  }
  
  Func&
  Func::operator =(Func const &a_copy)
  {
    m_entry = a_copy.m_entry;
    _has_entry = a_copy._has_entry;
    m_back_cunit = a_copy.m_back_cunit;
    m_name = a_copy.m_name;
  }

  bool
  Func::operator ==(Func const& a_func)
  {
    return (m_back_cunit == a_func.m_back_cunit &&
            m_name == a_func.m_name);
  }
  
  bool
  Func::operator ==(shared_ptr<Func> const a_func)
  {
    return (m_back_cunit == a_func->m_back_cunit &&
            m_name == a_func->m_name);
  }
  
  bool
  Func::operator !=(Func const& a_func)
  {
    return (m_back_cunit != a_func.m_back_cunit ||
            m_name != a_func.m_name);
  }
  
  bool
  Func::operator !=(shared_ptr<Func> const a_func)
  {
    return (m_back_cunit != a_func->m_back_cunit ||
            m_name != a_func->m_name);
  }

  shared_ptr<cpad::CUnit>
  Func::get_cunit(void)
  {
    if (m_back_cunit == nullptr)
      throw std::logic_error("Function doesn't have an owning Compilation Unit");
    return m_back_cunit;
  }
  
  const char *
  Func::get_cunit_name(void)
  {
    return get_cunit()->get_name();
  }

  shared_ptr<Graph>
  Func::get_graph(void)
  {
    return get_cunit()->get_graph();
  }
  
  const char *
  Func::get_graph_name(const char **out)
  {
    return get_graph()->get_name(out);
  }
  
  const char *
  Func::get_name(void)
  {
    return m_name.c_str();
  }

  const char *
  Func::get_cluster_name(void)
  {
    if (m_cluster_name.empty())
      m_cluster_name = string("cluster_func_") + get_name();
    return m_cluster_name.c_str();
  }

  void
  cpad::Func::add_node(shared_ptr<cpad::Node> a_node)
  {
    m_nodes_ptr.push_back(a_node);
    get_graph()->add_node(a_node);
  }
  
  void
  cpad::Func::add_node(cpad::Node *&a_node)
  {
    add_node(shared_ptr<cpad::Node>(a_node));
  }
  
  vector<shared_ptr<cpad::Node>>
  cpad::Func::get_nodes(void)
  {
    return m_nodes_ptr;
  }

  void
  Func::set_entry(shared_ptr<Node> an_entry)
  {
    if (_has_entry)
      throw std::logic_error("Function already has an entry point set");
    m_entry = an_entry;
    _has_entry = true;
  }

  void
  Func::set_entry(Node *&an_entry_ptr)
  {
    set_entry(shared_ptr<Node>(an_entry_ptr));
  }
  
  bool
  Func::has_entry(void)
  {
    return _has_entry;
  }

  shared_ptr<Node>
  Func::get_entry(void)
  {
    return m_entry;
  }
  
  void
  cpad::Func::dump(std::ostream &os)
  {
    cerr << "Func::dump\n";
    os << "        subgraph \"" << get_cluster_name() << "\" {\n";
    os << "            style=\"filled\";\n";
    os << "            color=\"#CFB0E0\";\n";
    os << "            style=\"filled\";\n";
    os << "            fillcolor=\"#CFB0E0\";\n";
    os << "            label=\"C Unit: " << m_name << "\";\n";
    os << "            labeljust=l;\n";
    os << "            pencolor=\"#AF40C0\";\n";
    os << "            labelfontname=\"mono\";\n";
    os << "            labelfontsize=12.0;\n";
    os << "            penwidth=2;\n";
    for (vector<shared_ptr<Node>>::iterator it = m_nodes_ptr.begin();
         it != m_nodes_ptr.end();
         it++)
      {
        shared_ptr<Node> node = *it;
        (*node).dump(os);
      }
    for (vector<shared_ptr<Node>>::iterator it = m_nodes_ptr.begin();
         it != m_nodes_ptr.end();
         it++)
      {
        shared_ptr<Node> node = *it;
        (*node).dump_in_edges(os);
      }
    os << "        }\n";
    for (vector<shared_ptr<Node>>::iterator it = m_nodes_ptr.begin();
         it != m_nodes_ptr.end();
         it++)
      {
        shared_ptr<Node> node = *it;
        (*node).dump_out_edges(os);
      }
  }

  void
  cpad::Func::dump_outer_edges(std::ostream &os)
  {
    for (vector<shared_ptr<Node>>::iterator it = m_nodes_ptr.begin();
         it != m_nodes_ptr.end();
         it++)
      {
        shared_ptr<Node> node = *it;
        (*node).dump_outer_edges(os);
      }
  }
}
