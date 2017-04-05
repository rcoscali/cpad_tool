/*
 * Copyright ©2017 NagraFrance
 */

#ifndef CPAD__EDGE_H_
#define CPAD__EDGE_H_

#include <iostream>
#include <memory>

#include "Node.h"

using namespace std;

namespace cpad
{
  class Node;
  
  class Edge
  {
  public:
    Edge(int, shared_ptr<Node>, shared_ptr<Node>);
    Edge(shared_ptr<Node>, shared_ptr<Node>);
    Edge(Node const *, Node const *);
    Edge(void);
    Edge(Edge const&);
    virtual ~Edge(void);
    Edge& operator = (Edge const&);

    int get_delta_value(void);
    std::pair<shared_ptr<Node>, shared_ptr<Node>> get_nodes(void);

    void dump_in(ostream &);
    void dump_out(ostream &);
    void dump_outer(ostream &);
    
  private:
    int m_delta_value;
    bool _has_delta_value;
    std::pair<shared_ptr<Node>, shared_ptr<Node>> m_nodes_ptr;
    bool _has_start_node;
    bool _has_end_node;
  };
}

#endif
