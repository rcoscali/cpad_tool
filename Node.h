/*
 * Copyright ©2017 NagraFrance
 */

#ifndef CPAD__NODE_H_
#define CPAD__NODE_H_

#include <iostream>

#include "Edge.h"

using namespace std;

namespace cpad
{
  class Edge;
  
  class Node
  {
  public:
    Node(string, int, Edge const*, Edge const*);
    Node(string);
    Node(Node const&);
    virtual ~Node();
    Node& operator = (Node const&);

    //const char *get_cunit_name(void);
    //const char *get_func_name(void);
    const char *get_name(void);
    bool has_add_value(void);
    int get_add_value(void);
    void set_add_value(int add_value);
    bool has_an_edge(void);
    pair<Edge *, Edge *> get_edges(void);

    void add_default_edge(Edge const*); // default branch is first of pair
    void add_fallback_edge(Edge const*); // fallback branch is second of pair
    
    void dump();

  private:
    string m_name;
    bool _has_add_value;
    int m_add_value;
    pair<Edge *, Edge *> m_edges_ptr;
    bool _has_edge_d;
    bool _has_edge_fb;
  };
}

#endif
