/*
 * Copyright ©2017 NagraFrance
 */

#ifndef CPAD__EDGE_H_
#define CPAD__EDGE_H_

#include <iostream>

#include "Node.h"

using namespace std;

namespace cpad
{
  class Node;
  
  class Edge
  {
  public:
    Edge(int, Node const*, Node const*);
    Edge(void);
    Edge(Edge const&);
    virtual ~Edge();
    Edge& operator = (Edge const&);

    int get_delta_value(void);
    std::pair<Node *, Node *> get_nodes(void);

    void dump();
    
  private:
    int m_delta_value;
    bool _has_delta_value;
    std::pair<Node *, Node *> m_nodes_ptr;
    bool _has_start_node;
    bool _has_end_node;
  };
}

#endif
