/*
 * Copyright ©2017 NagraFrance
 */

#ifndef CPAD__FILTER_H_
#define CPAD__FILTER_H_

#include <string>
#include <regex>

using namespace std;

namespace cpad
{
  enum FilterType
  {
    REGEXP = 1,
    WILDCARD = 2,
    EXPR = 3
  };

  enum FilterApplyOn
  {
    APPLYON_FILENAME  = 1,
    APPLYON_BASENAME  = 2,
    APPLYON_DIRNAME   = 3,
    APPLYON_EXTENSION = 4,
    APPLYON_MIMETYPE  = 5,
    APPLYON_SIZE      = 6,
    APPLYON_MDATE     = 7,
    APPLYON_CDATE     = 8,
    APPLYON_NUMBERS   = 9    
  }

  const char *FilterApplyOn_str[cpad::APPLYON_NUMBERS+1] =
    {
      /*0*/ "",
      /*1*/ "filename",
      /*2*/ "basename",
      /*3*/ "dirname",
      /*4*/ "extension",
      /*5*/ "mimetype",
      /*6*/ "size",
      /*7*/ "mdate",
      /*8*/ "cdate",
      /*9*/ NULL
    };
  
  class Filter
  {
  public:
    Filter(enum FilterType type);
    Filter(enum FilterType type, char const* expr);

    virtual ~Filter();
    
    Filter(Filter const&);
    Filter& operator = (Filter const&);
    Filter& operator != (Filter const&);

    enum FilterType get_type();
    const char *get_expr();
    string get_applyon();
    set_applyon(string applyon);
    
    private:
      enum FilterType m_type;
      string m_filter_expr;
      regex m_filter_regexp;
      string m_applyon;
    };
}


#endif
