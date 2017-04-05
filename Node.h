/*
 * Copyright ©2017 NagraFrance
 */

#ifndef CPAD__NODE_H_
#define CPAD__NODE_H_

#include <iostream>

#include "Func.h"
#include "Edge.h"

using namespace std;

namespace cpad
{
  class Edge;
  class Func;
  
  class Node
  {
  public:
    Node();
    Node(shared_ptr<Func>, string);
    Node(shared_ptr<Func>, string, int, shared_ptr<Edge>, shared_ptr<Edge>);
    Node(Node const&);
    virtual ~Node();
    Node& operator = (Node const&);

    const char *get_func_name(void);
    shared_ptr<Func> get_func(void);

    const char *get_name(void);

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

  private:
    shared_ptr<Func> m_back_func;
    string m_name;
    int m_checkpoint;
    bool _has_add_value;
    int m_add_value;
    pair<shared_ptr<Edge>, shared_ptr<Edge>> m_edges_ptr;
    bool _has_edge_d;
    bool _has_edge_fb;
  };
}

#endif
