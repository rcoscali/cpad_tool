/*
 * Copyright ©2017 NagraFrance
 */

#include "Graph.h"

using namespace std;

cpad::Graph::Graph(uuid_t grid)
{
  uuid_copy(m_grid, grid);
}

cpad::Graph::Graph()
  : cpad::Graph((unsigned char *)INVALID_GRID)
{
  uuid_generate(m_grid);
}

cpad::Graph::~Graph()
{
}

cpad::Graph::Graph(Graph const& a_graph_to_copy)
  : Graph((unsigned char *)a_graph_to_copy.m_grid)
{
}

cpad::Graph&
cpad::Graph::operator = (cpad::Graph const& a_graph_to_affect)
{
  uuid_copy(m_grid, a_graph_to_affect.m_grid);
  return (*this);
}

void
cpad::Graph::add_cunit(shared_ptr<cpad::CUnit> a_cunit)
{
  m_cunits_ptr.push_back(a_cunit);
}

void
cpad::Graph::add_cunit(cpad::CUnit *&a_cunit)
{
  m_cunits_ptr.push_back(shared_ptr<cpad::CUnit>(a_cunit));
}

vector<shared_ptr<cpad::CUnit>>
cpad::Graph::get_cunits(void)
{
  return m_cunits_ptr;
}

void
cpad::Graph::dump(std::ostream &os)
{
  char uuid[50];
  uuid_unparse_upper(m_grid, uuid);

  cerr << "Graph::dump\n";
  os << "digraph {\n";
  os << "    mode=\"ipsep\";\n";
  os << "    sep=\"+20,10\";\n";
  os << "    smoothing=\"spring\";\n";
  os << "    clusterrank=\"local\";\n";
  os << "    labelfontcolor=\"#FF0000\";\n";
  os << "    labelfontname=\"mono:italic\";\n";
  os << "    labelfontsize=20.0;\n";
  os << "    gradientangle=45;\n";
  os << "    labeldistance=30;\n";
  os << "    labelangle=45;\n";
  os << "    pencolor=\"#40FF40\";\n";
  os << "    label=\"Compilation Graph ID: ";
  os << uuid << "\";\n";
  os << "    labeljust=r;\n";
  for (vector<shared_ptr<CUnit>>::iterator it = m_cunits_ptr.begin();
       it != m_cunits_ptr.end();
       it++)
    {
      shared_ptr<CUnit> cunit = *it;
      (*cunit).dump(os);
    }
  os << "}\n";
}
