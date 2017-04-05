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
  cerr << "Graph::dump\n";
  os << "digraph {\n";
  os << "    label=\"";
  sprintf(uuid, "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
          m_grid[15], m_grid[14], m_grid[13], m_grid[12],
          m_grid[11], m_grid[10],
          m_grid[9],  m_grid[8],
          m_grid[7],  m_grid[6],
          m_grid[5],  m_grid[4],  m_grid[3],  m_grid[2],  m_grid[1],  m_grid[0]);
  os << uuid;
  os << "\";\n";
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
