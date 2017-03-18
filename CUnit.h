/*
 * Copyright ©2017 NagraFrance
 */

#ifndef CPAD__CUNIT_H_
#define CPAD__CUNIT_H_

#include <iostream>
#include <fstream>

using namespace std;

namespace cpad
{
  class CUnit : public ifstream
  {
  public:
    CUnit();
    CUnit(string name);
    CUnit(const CUnit &);
    virtual ~CUnit();
    CUnit& operator = (const CUnit &);

    const char *get_filename();
    unsigned long get_length();
    
  private:
    bool m_opened;
    string m_filename;
    unsigned long m_length;
  };
}

#endif
