/*
 * Copyright ©2017 NagraFrance
 */

#ifndef CPAD__FUNC_H_
#define CPAD__FUNC_H_

#include <string>

using namespace std;

namespace cpad
{
  class Func
  {
  public:
	Func(void);
    Func(string name);
    Func(Func const&);
    virtual ~Func(void);
    Func& operator =(Func const&);
    const char *get_name(void);
    
  private:
    string m_name;
  };
}

#endif
