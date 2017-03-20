/*
 * Copyright ©2017 NagraFrance
 */

#ifndef CPAD__DIR_H_
#define CPAD__DIR_H_

#include <string>

using namespace std;

namespace cpad
{
  class Dir
  {
  public:

    enum DirReadFlags
    {
      READ_DIR_INCLUDE_DOTS = 0x0001,
      READ_DIR_SORT         = 0x0002,
      READ_DIR_FLAG_MASK    = 0x0003
    };
    
    Dir(void);
    Dir(string pathname);
    Dir(Dir const&);
    virtual ~Dir(void);
    Dir& operator =(Dir const&);
    const char *get_pathname(void);
    vector<string> read(void);
    
  private:
    string m_pathname;
    bool m_recursive;
  };
}

#endif
