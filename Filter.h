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

  template<class T>
    class Filter : public vector<T>
    {
    public:
      Filter<T>(enum FilterType type);
      Filter<T>(enum FilterType type, const char *expr);

      virtual ~Filter();

      Filter(Filter<T> const&);
      Filter<T>& operator = (const Filter<T> &);

    private:
      enum FilterType m_type;
      string m_filter_expr;
      regex m_filter_regexp;
    };
}

#endif
