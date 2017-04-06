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
#include "Node.h"

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
  class Node;
  
  class Graph
  {
  public:
    Graph(uuid_t, int);
    Graph(int);
    virtual ~Graph();
    Graph(Graph const&);
    Graph& operator = (Graph const&);

    const char *get_name(const char **);

    void add_cunit(shared_ptr<CUnit>);
    void add_cunit(CUnit *&);
    vector<shared_ptr<CUnit>> get_cunits(void);

    void set_entry(shared_ptr<CUnit>);
    void set_entry(CUnit *&);
    bool has_entry(void);
    shared_ptr<CUnit> get_entry(void);

    void dump(ostream &);

    int get_current_checkpoint(void);
    void add_node(const shared_ptr<Node> &);
    void add_node(const weak_ptr<Node> &);
    void add_node(Node * const&);
    vector<weak_ptr<Node>> get_all_nodes(void);

    void allocate_cfi_apex(void);

    vector<weak_ptr<Node>> m_all_nodes;

  private:

    int m_checkpoint;
    shared_ptr<CUnit> m_entry;
    bool _has_entry;
    vector<shared_ptr<CUnit>> m_cunits_ptr;
    uuid_t m_grid;
    
  }; // class Graph

} // namespace

#endif /* CPAD__GRAPH_H_ */
