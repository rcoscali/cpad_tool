/*
 * Copyright ©2017 NagraFrance
 */

#include "Graph.h"

using namespace std;

cpad::Graph::Graph(uuid_t grid, int start_checkpoint)
  : m_entry(nullptr),
    _has_entry(false),
    m_cunits_ptr(),
    m_checkpoint(start_checkpoint)
{
  uuid_copy(m_grid, grid);
}

cpad::Graph::Graph(int start_checkpoint)
  : cpad::Graph((unsigned char *)NULL_GRID, start_checkpoint)
{
  uuid_generate(m_grid);
}

cpad::Graph::~Graph()
{
}

cpad::Graph::Graph(Graph const& a_graph_to_copy)
  : Graph((unsigned char *)a_graph_to_copy.m_grid, a_graph_to_copy.m_checkpoint)
{
  m_entry = a_graph_to_copy.m_entry;
  _has_entry = a_graph_to_copy._has_entry;
  m_cunits_ptr = a_graph_to_copy.m_cunits_ptr;
}

cpad::Graph&
cpad::Graph::operator = (cpad::Graph const& a_graph_to_affect)
{
  uuid_copy(m_grid, a_graph_to_affect.m_grid);
  m_checkpoint = a_graph_to_affect.m_checkpoint;
  m_entry = a_graph_to_affect.m_entry;
  _has_entry = a_graph_to_affect._has_entry;
  m_cunits_ptr = a_graph_to_affect.m_cunits_ptr;

  return (*this);
}

const char *
cpad::Graph::get_name(const char **out)
{
  if (out == (const char **)NULL)
    throw std::invalid_argument("Invalid NULL pointer argument for returning name");
  if (uuid_is_null(m_grid))
    throw std::logic_error("Graph has a null graph identifier");
  uuid_unparse_upper(m_grid, (char *)*out);
  return (*out);
}

void
cpad::Graph::add_cunit(shared_ptr<cpad::CUnit> a_cunit)
{
  m_cunits_ptr.push_back(a_cunit);
}

void
cpad::Graph::add_cunit(cpad::CUnit *&a_cunit)
{
  add_cunit(shared_ptr<cpad::CUnit>(a_cunit));
}

vector<shared_ptr<cpad::CUnit>>
cpad::Graph::get_cunits(void)
{
  return m_cunits_ptr;
}

void
cpad::Graph::set_entry(shared_ptr<cpad::CUnit> an_entry)
{
  if (_has_entry)
    throw std::logic_error("Graph already has an entry point");
  m_entry = an_entry;
  _has_entry = true;
}

void
cpad::Graph::set_entry(cpad::CUnit *&an_entry)
{
  set_entry(shared_ptr<cpad::CUnit>(an_entry));
}

bool
cpad::Graph::has_entry(void)
{
  return _has_entry;
}

shared_ptr<cpad::CUnit>
cpad::Graph::get_entry(void)
{
  return m_entry;
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
  os << "    label=\"Compilation Graph ID: " << uuid << "\";\n";
  os << "    labeljust=r;\n";
  if (_has_entry)
    {
      os << "    comment=\"Entry point is in compilation unit '" << get_entry()->get_filename() << "'\";\n";
      if (get_entry()->has_entry())
        {
          os << "    comment=\"and in function '" << get_entry()->get_entry()->get_name() << "'\";\n";
          if (get_entry()->get_entry()->has_entry())
            {
              os << "    comment=\"and in basic_block '" << get_entry()->get_entry()->get_entry()->get_name() << "'\";\n";
            }
        }
      os << "    \n";
      os << "    ENTRY [shape=circle,style=filled,fontcolor=white,color=black,fixedsize=true,fontsize=8,width=0.4,label=\"Entry\"];\n";
      os << "    \n";
    }
  for (vector<shared_ptr<CUnit>>::iterator it = m_cunits_ptr.begin();
       it != m_cunits_ptr.end();
       it++)
    {
      shared_ptr<CUnit> cunit = *it;
      (*cunit).dump(os);
    }

  cerr << "has entry?: " << _has_entry << "\n";
  cerr << "entry: " << get_entry() << "\n";
  cerr << "entry has entry?: " << get_entry()->has_entry() << "\n";
  cerr << "entry(entry): " << get_entry()->get_entry() << "\n";
  cerr << "entry(entry) has entry?: " << get_entry()->get_entry()->has_entry() << "\n";
  if (_has_entry && get_entry()->has_entry() && get_entry()->get_entry()->has_entry())
    {
      Func entry_func = *(get_entry()->get_entry());
      Node entry_node = *(get_entry()->get_entry()->get_entry());
      os << "    \n";
      os << "    ENTRY -> " << entry_node.get_cluster_name() << "[style=\"dotted,bold\",color=red,weight=3,constraint=false,decorate=false];\n";
      os << "    \n";
    }
  os << "}\n";
}

int
cpad::Graph::get_current_checkpoint()
{
  return m_checkpoint;
}

void
cpad::Graph::add_node(const shared_ptr<cpad::Node> &a_shared_node_ptr)
{
  add_node(weak_ptr<cpad::Node>(a_shared_node_ptr));
}

void
cpad::Graph::add_node(const weak_ptr<cpad::Node> &a_weak_node_ptr)
{
  m_all_nodes.push_back(a_weak_node_ptr);
}

void
cpad::Graph::add_node(cpad::Node * const &a_node_ptr)
{
  add_node(shared_ptr<cpad::Node>(a_node_ptr));
}

vector<weak_ptr<cpad::Node>>
cpad::Graph::get_all_nodes(void)
{
  return m_all_nodes;
}

void
cpad::Graph::allocate_cfi_apex(void)
{
  cerr << "Starting APEX allocation: current checkpoint: " << get_current_checkpoint() << "\n";

  cerr << "Computing ancestors ...\n";
  for (auto it = m_all_nodes.begin();
       it != m_all_nodes.end();
       it++)
    {
      if (auto node_ptr = (*it).lock())
        {
          node_ptr->compute_ancestors();
          node_ptr->dump_ancestors();
        }
    }
}
