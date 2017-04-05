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
  class Node;
  
  class Func
  {
  public:
    Func(void);
    Func(shared_ptr<CUnit>, string);
    Func(Func const&);
    virtual ~Func(void);
    Func& operator =(Func const&);
    const char *get_name(void);

    void add_node(shared_ptr<Node>);
    void add_node(Node *&);
    vector<shared_ptr<Node>> get_nodes(void);
    
    void dump(ostream &);
    
  private:
    shared_ptr<CUnit> m_back_cunit;
    vector<shared_ptr<Node>> m_nodes_ptr;
    string m_name;
  };
}

#endif
