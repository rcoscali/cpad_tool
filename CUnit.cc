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
  }
  
cpad::CUnit::CUnit(shared_ptr<Graph> the_graph, string filename)
  : ifstream(),
    m_back_graph(the_graph),
    m_filename(filename),
    m_length(0),
    m_opened(false)
{
  m_filename = filename;
  if (!m_filename.empty())
    {
      filebuf *fb = rdbuf();
      fb->open(m_filename.c_str(), ios::in);
      if (fb->is_open())
        {
          m_opened = true;
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
  m_filename = a_copy.m_filename;
  m_length = a_copy.m_length;
  m_opened = a_copy.m_opened;
}

cpad::CUnit::~CUnit()
{
  if (m_opened && rdbuf() && rdbuf()->is_open())
    rdbuf()->close();
}

cpad::CUnit &
cpad::CUnit::operator =(const CUnit &a_copy)
{
  m_filename = a_copy.m_filename;
  m_length = a_copy.m_length;
  m_opened = a_copy.m_opened;
  return *this;
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
cpad::CUnit::dump(std::ostream &os)
{
  cerr << "CUnit::dump\n";
  os << "    subgraph \"cluster_cunit_" << m_filename << "\" {\n";
  os << "        label=\"C Unit: " << m_filename << "\";\n";
  os << "        style=\"dashed\";\n";
  os << "        color=\"black\";\n";
  os << "        fillcolor=\"grey80\";\n";
  os << "        labeljust=l;\n";
  os << "        penwidth=2;\n";
  
  for (vector<shared_ptr<cpad::Func>>::iterator it = m_funcs_ptr.begin();
       it != m_funcs_ptr.end();
       it++)
    {
      shared_ptr<cpad::Func> func = *it;
      (*func).dump(os);
    }
  os << "    }\n";
}
