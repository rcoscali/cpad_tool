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

    shared_ptr<Graph> get_graph(void);
    const char *get_graph_name(const char **);

    bool operator == (CUnit const&);
    bool operator == (shared_ptr<CUnit> const);
    bool operator != (CUnit const&);
    bool operator != (shared_ptr<CUnit> const);

    const char *get_name(void);
    const char *get_cluster_name(void);
    const char *get_filename(void);
    unsigned long get_length(void);

    void add_func(shared_ptr<Func>);
    void add_func(Func *&);
    vector<shared_ptr<Func>> get_funcs(void);

    void set_entry(shared_ptr<Func>);
    void set_entry(Func *&);
    bool has_entry(void);
    shared_ptr<Func> get_entry(void);

    void dump(ostream &);
    
  private:
    shared_ptr<Func> m_entry;
    bool _has_entry;
    shared_ptr<Graph> m_back_graph;
    bool _opened;
    string m_cluster_name;
    string m_filename;
    unsigned long m_length;
    vector<shared_ptr<Func>> m_funcs_ptr;
  };
}

#endif
