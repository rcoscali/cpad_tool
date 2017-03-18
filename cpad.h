/*
 * Copyright ©2017 NagraFrance
 */

#ifndef  CPAD__CPAD_H_
#define CPAD__CPAD_H_

#define CPAD_SEMANTICS_FILEPATH		"cpad-semantics.xml"

#include <vector>
#include <iostream>
#include <fstream>

#include "Filter.h"
#include "CUnit.h"
#include "Func.h"

using namespace std;

namespace cpad
{
  class Cpad
  {
  public:
    Cpad(int argc, char **argv);
    virtual ~Cpad();

    int do_tool_processing(void);
    
  protected:
    Cpad();
    Cpad(Cpad &);
    Cpad &operator =(Cpad&);
    
  private:
    bool m_active;
    string m_semantics_path;
    ifstream *m_semantics_file_p;
    char *m_semantics_buffer;
    
    vector<Filter<CUnit>> m_cunit_filters;
    vector<Filter<Func>> mfunc_filters;
    vector<CUnit> m_cunits;
    vector<Func> m_funcs;
  };
}

#endif
