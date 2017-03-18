/*
 * Copyright ©2017 NagraFrance
 */

#include <iostream>
#include <fstream>

#include "CUnit.h"

using namespace std;

namespace cpad
{
  CUnit::CUnit()
  {
  }
  
  CUnit::CUnit(string filename)
    : ifstream(filename, ios::in)
  {
    m_filename = filename;
    seekg(0, end);
    m_length = tellg();
    seekg(0, beg);
  }

  CUnit::CUnit(const CUnit &a_copy)
    : CUnit()
  {
  }

  CUnit::~CUnit()
  {
  }

  CUnit &
  CUnit::operator =(const CUnit &a_copy)
  {
  }
}

