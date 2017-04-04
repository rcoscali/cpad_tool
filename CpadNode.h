/*
 * Copyright ©2017 NagraFrance
 */

#ifndef CPAD__NODE_H_
#define CPAD__NODE_H_

#include <iostream>

using namespace std;

namespace cpad
{
  class Edge;
  
  class Node
  {
  public:
    Node(string cunit_name, string func_name, string name, int add_value, Edge *egde1, Edge *Edge2);
    Node(string cunit_name, string func_name, string name);
    Node(const Node &);
    virtual ~Node();
    Node& operator = (const Node &);

    const char *get_cunit_name();
    const char *get_func_name();
    int get_add_value();
    pair<Edge> *get_edges();
    
  private:
    string m_cunit_name;
    string m_func_name;
    int m_add_value;
    pair<Edge> *m_edges;
  };
}

#endif
