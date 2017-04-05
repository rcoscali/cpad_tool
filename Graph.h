/*
 * Copyright ©2017 NagraFrance
 */

#ifndef CPAD__GRAPH_H_
#define CPAD__GRAPH_H_

#include <uuid.h>

#include <iostream>
#include <memory>
#include <vector>

#include "CUnit.h"

using namespace std;

namespace cpad
{
  UUID_DEFINE(NULL_GRID,
              0x00, 0x00, 0x00, 0x00,
              0x00, 0x00, 0x00, 0x00,
              0x00, 0x00, 0x00, 0x00,
              0x00, 0x00, 0x00, 0x00 );
  UUID_DEFINE(INVALID_GRID,
              0xff, 0xff, 0xff, 0xff,
              0xff, 0xff, 0xff, 0xff,
              0xff, 0xff, 0xff, 0xff,
              0xff, 0xff, 0xff, 0xff );

  class CUnit;
  
  class Graph
  {
  public:
    Graph(uuid_t grid);
    Graph();
    virtual ~Graph();
    Graph(Graph const&);
    Graph& operator = (Graph const&);

    void add_cunit(shared_ptr<CUnit>);
    void add_cunit(CUnit *&);
    vector<shared_ptr<CUnit>> get_cunits(void);

    void dump(ostream &);

  private:

    vector<shared_ptr<CUnit>> m_cunits_ptr;
    uuid_t m_grid;
    
  }; // class Graph

} // namespace

#endif /* CPAD__GRAPH_H_ */
