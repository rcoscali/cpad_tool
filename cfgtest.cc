/*
 * Copyright ©2017 NagraFrance
 */

#include <iostream>
#include <cstdlib>

#include "Node.h"
#include "Edge.h"

using namespace std;
using namespace cpad;

int
main(int argc, char *argv[])
{
  try
    {
      if (argc != 2)
        throw std::invalid_argument("Usage: cfgtest <initial_checkpoint>");

      //
      // Graph
      //
      
      int initial_checkpoint = atoi(argv[1]);
      cerr << "initial checkpoint: " << initial_checkpoint << "\n";
      Graph *gr = new Graph(initial_checkpoint);

      //
      // Compilation Units
      //

      // Create first CUnit: CUnit1
      CUnit *cunit1 = new CUnit(shared_ptr<Graph>(gr), "CUnit1");
      // Add it to the graph
      gr->add_cunit(cunit1);
      // Add it as entry cunit
      gr->set_entry(cunit1);
      // Create second CUnit: CUnit2
      CUnit *cunit2 = new CUnit(shared_ptr<Graph>(gr), "CUnit2");
      // Add it to the graph
      gr->add_cunit(cunit2);
      
      //
      // Funcs
      //
      
      // Create first function: foo
      Func *func1 = new Func(shared_ptr<CUnit>(cunit1), "foo");
      // Add it to cunit1
      cunit1->add_func(func1);
      // Add it as entry func
      cunit1->set_entry(func1);
      // Create second function: bar
      Func *func2 = new Func(shared_ptr<CUnit>(cunit2), "bar");
      // Add it to cunit2
      cunit2->add_func(func2);      
      Func *func3 = new Func(shared_ptr<CUnit>(cunit2), "bar");
      // Add it to cunit2
      cunit2->add_func(func3);
      
      //
      // Nodes
      //
      
      // Create Node A
      Node *a = new Node(shared_ptr<Func>(func1), "A");
      // Add it to func1
      func1->add_node(a);
      // Add it as entry node
      func1->set_entry(a);
      // Create Node B
      Node *b = new Node(shared_ptr<Func>(func1), "B");
      // Add it to func1
      func1->add_node(b);
      // Create Node C
      Node *c = new Node(shared_ptr<Func>(func1), "C");
      // Add it to func1
      func1->add_node(c);
      
      Node *d = new Node(shared_ptr<Func>(func2), "D");
      func2->add_node(d);
      Node *e = new Node(shared_ptr<Func>(func2), "E");
      func2->add_node(e);
      Node *f = new Node(shared_ptr<Func>(func3), "F");
      func3->add_node(f);

      //
      // Edges
      //
      
      Edge *ab = new Edge(shared_ptr<Node>(a), shared_ptr<Node>(b));
      a->add_default_edge(ab);
      Edge *ac = new Edge(shared_ptr<Node>(a), shared_ptr<Node>(c));
      a->add_fallback_edge(ac);
      
      Edge *cd = new Edge(shared_ptr<Node>(c), shared_ptr<Node>(d));
      c->add_default_edge(cd);
      Edge *cf = new Edge(shared_ptr<Node>(c), shared_ptr<Node>(f));
      c->add_fallback_edge(cf);
      
      Edge *de = new Edge(shared_ptr<Node>(d), shared_ptr<Node>(e));
      d->add_default_edge(de);
      Edge *df = new Edge(shared_ptr<Node>(d), shared_ptr<Node>(f));
      d->add_fallback_edge(df);
      
      Edge *ea = new Edge(shared_ptr<Node>(e), shared_ptr<Node>(a));
      e->add_default_edge(ea);
      
      Edge *fb = new Edge(shared_ptr<Node>(f), shared_ptr<Node>(b));
      f->add_default_edge(fb);

      // Added the same edge a second time as default edge
      try
        {
          f->add_default_edge(fb);
        }
      catch (exception &e)
        {
          cerr << "Exception: " << e.what() << "\n";
        }
      
      // Added the same edge as fallback edge
      try
        {
          f->add_fallback_edge(fb);
        }
      catch (exception &e)
        {
          cerr << "Exception: " << e.what() << "\n";
        }
      
      // Added an edge as default edge but already have one
      Edge *fa = new Edge(shared_ptr<Node>(f), shared_ptr<Node>(a));
      try
        {
          f->add_default_edge(fa);
        }
      catch (exception &e)
        {
          cerr << "Exception: " << e.what() << "\n";
        }
      
      // Added an edge as fallback edge but already have one
      try
        {
          f->add_fallback_edge(fa);
        }
      catch (exception &e)
        {
          cerr << "Exception: " << e.what() << "\n";
        }
      
      // Dump as dot
      gr->dump(cout);

      // Start apex allocation
      gr->allocate_cfi_apex();
    }
  catch (invalid_argument &ia)
    {
      cerr << "cfgtest: error: missing initial_checkpoint value\n";
      cerr << ia.what() << endl;
      return 1;
    }
  return 0;
}
