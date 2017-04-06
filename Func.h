/*
 * Copyright ©2017 NagraFrance
 */

#ifndef CPAD__FUNC_H_
#define CPAD__FUNC_H_

#include <string>
#include <memory>
#include <vector>

#include "CUnit.h"
#include "Node.h"

using namespace std;

namespace cpad
{
  class CUnit;
  class Graph;
  class Node;
  
  class Func
  {
  public:
    Func(void);
    Func(shared_ptr<CUnit>, string);
    Func(Func const&);
    virtual ~Func(void);
    Func& operator =(Func const&);
    
    bool operator ==(Func const&);
    bool operator !=(Func const&);
    bool operator ==(shared_ptr<Func>);
    bool operator !=(shared_ptr<Func>);

    shared_ptr<CUnit> get_cunit(void);
    const char *get_cunit_name(void);

    shared_ptr<Graph> get_graph(void);
    const char *get_graph_name(const char **);

    const char *get_name(void);
    const char *get_cluster_name(void);

    void add_node(shared_ptr<Node>);
    void add_node(Node *&);
    vector<shared_ptr<Node>> get_nodes(void);
    
    void set_entry(shared_ptr<Node>);
    void set_entry(Node *&);
    bool has_entry(void);
    shared_ptr<Node> get_entry(void);

    void dump(ostream &);
    void dump_outer_edges(ostream &);
    
  private:
    shared_ptr<Node> m_entry;
    bool _has_entry;
    shared_ptr<CUnit> m_back_cunit;
    vector<shared_ptr<Node>> m_nodes_ptr;
    string m_cluster_name;
    string m_name;
  };
}

#endif
