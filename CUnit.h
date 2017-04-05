/*
 * Copyright ©2017 NagraFrance
 */

#ifndef CPAD__CUNIT_H_
#define CPAD__CUNIT_H_

#include <iostream>
#include <fstream>
#include <memory>
#include <vector>

#include "Graph.h"
#include "Func.h"

using namespace std;

namespace cpad
{
  class Graph;
  class Func;
  
  class CUnit : public ifstream
  {
  public:
    CUnit();
    CUnit(shared_ptr<Graph>, string);
    CUnit(const CUnit &);
    virtual ~CUnit();
    CUnit& operator = (CUnit const&);

    bool operator == (CUnit const&);
    bool operator == (shared_ptr<CUnit> const);
    bool operator != (CUnit const&);
    bool operator != (shared_ptr<CUnit> const);

    const char *get_filename(void);
    unsigned long get_length(void);

    void add_func(shared_ptr<Func>);
    void add_func(Func *&);
    vector<shared_ptr<Func>> get_funcs(void);

    void dump(ostream &);
    
  private:
    shared_ptr<Graph> m_back_graph;
    bool m_opened;
    string m_filename;
    unsigned long m_length;
    vector<shared_ptr<Func>> m_funcs_ptr;
  };
}

#endif
