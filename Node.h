/*
 * Copyright ©2017 NagraFrance
 */

#ifndef CPAD__NODE_H_
#define CPAD__NODE_H_

#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

#include "CUnit.h"
#include "Func.h"
#include "Edge.h"
#include "Graph.h"

using namespace std;

namespace cpad
{
  class Edge;
  class Func;
  class CUnit;
  class Graph;
  
  class Node
  {
  public:
    Node();
    Node(shared_ptr<Func>, string);
    Node(shared_ptr<Func>, string, int, shared_ptr<Edge>, shared_ptr<Edge>);
    Node(Node const&);
    virtual ~Node();
    Node& operator = (Node const&);
    
    bool operator == (Node const&);
    bool operator != (Node const&);
    bool operator == (shared_ptr<Node>);
    bool operator != (shared_ptr<Node>);

    class HasNodeAsAncestor
    {
    private:
      bool has_node;
      shared_ptr<Node> the_node_ptr;
      
    public:
      HasNodeAsAncestor(shared_ptr<Node>);
      void operator ()(weak_ptr<Node> const &);
      bool has_node_as_ancestor() { return has_node; }
    };
    
    const char *get_func_name(void);
    shared_ptr<Func> get_func(void);

    const char *get_cunit_name(void);
    shared_ptr<CUnit> get_cunit(void);

    const char *get_graph_name(const char **);
    shared_ptr<Graph> get_graph(void);

    const char *get_name(void);
    const char *get_cluster_name(void);

    const int get_checkpoint(void);
    void set_checkpoint(const int);

    bool has_add_value(void);
    int get_add_value(void);
    void set_add_value(int add_value);

    bool has_an_edge(void);
    pair<shared_ptr<Edge>, shared_ptr<Edge>> get_edges(void);

    void add_default_edge(shared_ptr<Edge>); // default branch is first of pair
    void add_default_edge(Edge *&); // default branch is first of pair
    void add_fallback_edge(shared_ptr<Edge>); // fallback branch is second of pair
    void add_fallback_edge(Edge *&); // fallback branch is second of pair
    void add_edge(shared_ptr<Edge>); // add default branch then fallback branch in pair
    void add_edge(Edge *&); // add default branch then fallback branch in pair
    
    void dump(ostream &);
    void dump_edges(ostream &);
    void dump_in_edges(ostream &);
    void dump_out_edges(ostream &);
    void dump_outer_edges(ostream &);

    void add_ancestor(const weak_ptr<Node> &);
    void add_ancestor(const shared_ptr<Node> &);
    bool has_ancestor(const weak_ptr<Node> &);
    bool has_ancestor(const shared_ptr<Node> &);
    void compute_ancestors(void);
    void dump_ancestors(void);

  private:
    shared_ptr<Func> m_back_func;
    string m_cluster_name;
    string m_name;
    int m_checkpoint;
    bool _has_add_value;
    int m_add_value;
    pair<shared_ptr<Edge>, shared_ptr<Edge>> m_edges_ptr;
    bool _has_edge_d;
    bool _has_edge_fb;
    vector<weak_ptr<Node>> m_ancestors;
    bool _has_been_traversed;
  };
}

#endif
