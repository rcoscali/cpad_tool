/*
 * Copyright ©2017 NagraFrance
 */

#include <iostream>

#include "Node.h"
#include "Edge.h"

using namespace cpad;

int
main(int argc, char *argv[])
{
  Node a("A");
  Node b("B");
  Node c("C");

  Edge ab(&a, &b);
  Edge ac(&a, &c);
}
