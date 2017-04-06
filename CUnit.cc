/*
 * Copyright ©2017 NagraFrance
 */

#include <iostream>
#include <fstream>

#include "CUnit.h"

using namespace std;

cpad::CUnit::CUnit()
  : cpad::CUnit(nullptr, "")
  {
    m_back_graph = nullptr;
    m_entry = nullptr;
    _has_entry = false;
  }
  
cpad::CUnit::CUnit(shared_ptr<Graph> the_graph, string filename)
  : ifstream(),
    m_entry(nullptr),
    _has_entry(false),
    m_back_graph(the_graph),
    m_filename(filename),
    m_length(0),
    _opened(false)
{
  m_filename = filename;
  if (!m_filename.empty())
    {
      filebuf *fb = rdbuf();
      fb->open(m_filename.c_str(), ios::in);
      if (fb->is_open())
        {
          _opened = true;
          seekg(0, end);
          if (tellg() > 0)
            m_length = tellg();
          seekg(0, beg);
        }
    }
}

cpad::CUnit::CUnit(const CUnit &a_copy)
  : CUnit()
{
  m_entry = a_copy.m_entry;
  _has_entry = a_copy._has_entry;
  m_back_graph = a_copy.m_back_graph;
  m_filename = a_copy.m_filename;
  m_length = a_copy.m_length;
  _opened = a_copy._opened;
}

cpad::CUnit::~CUnit()
{
  if (_opened && rdbuf() && rdbuf()->is_open())
    rdbuf()->close();
}

cpad::CUnit &
cpad::CUnit::operator =(const CUnit &a_copy)
{
  m_entry = a_copy.m_entry;
  _has_entry = a_copy._has_entry;
  m_back_graph = a_copy.m_back_graph;
  m_filename = a_copy.m_filename;
  m_length = a_copy.m_length;
  _opened = a_copy._opened;

  return (*this);
}

shared_ptr<cpad::Graph>
cpad::CUnit::get_graph(void)
{
  if (m_back_graph == nullptr)
    throw std::logic_error("Compilation Unit doesn't have an owning Graph");
  return m_back_graph;
}

const char *
cpad::CUnit::get_graph_name(const char **out)
{
  return get_graph()->get_name(out);
}

bool
cpad::CUnit::operator == (cpad::CUnit const&a_cunit)
{
  return (m_filename == a_cunit.m_filename);
}

bool
cpad::CUnit::operator == (shared_ptr<cpad::CUnit> const a_cunit)
{
  return (m_filename == a_cunit->m_filename);
}

bool
cpad::CUnit::operator != (cpad::CUnit const& a_cunit)
{
  return (m_filename != a_cunit.m_filename);
}

bool
cpad::CUnit::operator != (shared_ptr<cpad::CUnit> const a_cunit)
{
  return (m_filename != a_cunit->m_filename);
}

const char *
cpad::CUnit::get_name()
{
  return get_filename();
}

const char *
cpad::CUnit::get_cluster_name()
{
  if (m_cluster_name.empty())
    m_cluster_name = string("cluster_cunit_") + get_name();
  return m_cluster_name.c_str();
}

const char *
cpad::CUnit::get_filename()
{
  return m_filename.c_str();
}

unsigned long
cpad::CUnit::get_length()
{
  return m_length;
}

void
cpad::CUnit::add_func(shared_ptr<Func> a_func)
{
  m_funcs_ptr.push_back(a_func);
}

void
cpad::CUnit::add_func(cpad::Func *&a_func)
{
  m_funcs_ptr.push_back(shared_ptr<cpad::Func>(a_func));
}

vector<shared_ptr<cpad::Func>>
cpad::CUnit::get_funcs(void)
{
  return m_funcs_ptr;
}

void
cpad::CUnit::set_entry(shared_ptr<cpad::Func> an_entry)
{
  if (_has_entry)
    throw std::logic_error("Compilation Unit already has an entry point set");
  m_entry = an_entry;
  _has_entry = true;
}

void
cpad::CUnit::set_entry(Func *&an_entry_ptr)
{
  set_entry(shared_ptr<cpad::Func>(an_entry_ptr));
}

bool
cpad::CUnit::has_entry(void)
{
  return _has_entry;
}

shared_ptr<cpad::Func>
cpad::CUnit::get_entry(void)
{
  return m_entry;
}

void
cpad::CUnit::dump(std::ostream &os)
{
  cerr << "CUnit::dump\n";
  os << "    subgraph \"" << get_cluster_name() << "\" {\n";
  os << "        label=\"C Unit: " << m_filename << "\";\n";
  os << "        style=\"dashed\";\n";
  os << "        color=\"black\";\n";
  os << "        fillcolor=\"grey90\";\n";
  os << "        labeljust=l;\n";
  os << "        pencolor=\"#C0AF40\";\n";
  os << "        labelfontsize=16.0;\n";
  os << "        style=\"rounded\";\n";
  os << "        penwidth=3;\n";
  
  for (vector<shared_ptr<cpad::Func>>::iterator it = m_funcs_ptr.begin();
       it != m_funcs_ptr.end();
       it++)
    {
      shared_ptr<cpad::Func> func = *it;
      (*func).dump(os);
    }
  os << "    }\n";
  for (vector<shared_ptr<cpad::Func>>::iterator it = m_funcs_ptr.begin();
       it != m_funcs_ptr.end();
       it++)
    {
      shared_ptr<cpad::Func> func = *it;
      (*func).dump_outer_edges(os);
    }
}
