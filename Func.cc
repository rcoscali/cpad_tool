/*
 * Copyright ©2017 NagraFrance
 */

#include <string>

#include "Func.h"

using namespace std;

namespace cpad
{
  Func::Func(void)
    : m_back_cunit(nullptr),
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
  {
    m_back_cunit = a_copy.m_back_cunit;
    m_name = a_copy.m_name;
  }

  Func::~Func(void)
  {

  }
  Func& Func::operator =(Func const &a_copy)
  {
    m_back_cunit = a_copy.m_back_cunit;
    m_name = a_copy.m_name;
  }

  const char *
  Func::get_name(void)
  {
    return m_name.c_str();
  }

  void
  cpad::Func::add_node(shared_ptr<cpad::Node> a_node)
  {
    m_nodes_ptr.push_back(a_node);
  }
  
  void
  cpad::Func::add_node(cpad::Node *&a_node)
  {
    m_nodes_ptr.push_back(shared_ptr<cpad::Node>(a_node));
  }
  
  vector<shared_ptr<cpad::Node>>
  cpad::Func::get_nodes(void)
  {
    return m_nodes_ptr;
  }
      
  void
  cpad::Func::dump(std::ostream &os)
  {
    cerr << "Func::dump\n";
    os << "        subgraph cluster_func_" << m_name << " {\n";
    os << "            style=\"filled\";\n";
    os << "            color=\"darkred\";\n";
    os << "            fillcolor=\"grey90\";\n";
    os << "            label=\"C Unit: " << m_name << "\";\n";
    os << "            labeljust=l;\n";
    os << "            penwidth=3;\n";
    for (vector<shared_ptr<Node>>::iterator it = m_nodes_ptr.begin();
         it != m_nodes_ptr.end();
         it++)
      {
        shared_ptr<Node> node = *it;
        (*node).dump(os);
      }
    os << "        }\n";
    for (vector<shared_ptr<Node>>::iterator it = m_nodes_ptr.begin();
         it != m_nodes_ptr.end();
         it++)
      {
        shared_ptr<Node> node = *it;
        (*node).dump_edges(os);
      }
  }
}
