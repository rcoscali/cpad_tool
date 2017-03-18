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
      Filter<T>(enum FilterType type, char const* expr);

      virtual ~Filter();

      Filter(Filter<T> const&);
      Filter<T>& operator = (Filter<T> const&);
      Filter<T>& operator != (Filter<T> const&);

      enum FilterType get_type();
      const char *get_expr();

    private:
      enum FilterType m_type;
      string m_filter_expr;
      regex m_filter_regexp;
    };
}

template <class T>
cpad::Filter<T>::Filter(enum FilterType type)
{
  m_type = type;
  m_filter_expr = "";
  m_filter_regexp = regex("");
}
  
template <class T>
cpad::Filter<T>::Filter(enum FilterType type, char const *expr)
  : cpad::Filter<T>(type)
{
  switch (m_type)
    {
    case cpad::EXPR:
      m_filter_expr = string(expr);
      break;
    case cpad::REGEXP:
      m_filter_expr = string(expr);
      m_filter_regexp = regex(expr, regex::extended);
      break;
    case cpad::WILDCARD:
      m_filter_expr = string(expr);
      m_filter_regexp = regex(expr, regex::basic);
      break;
    }
}
  
template <class T>
cpad::Filter<T>::~Filter()
{
}

template <class T>
cpad::Filter<T>::Filter(cpad::Filter<T> const& a_copy) 
{
  m_type = a_copy.m_type;
  m_filter_expr = a_copy.m_filter_expr;
}

template <class T>
cpad::Filter<T>&
cpad::Filter<T>::operator = (cpad::Filter<T> const &a_copy)
{
  m_type = a_copy.m_type;
  m_filter_expr = a_copy.m_filter_expr;
  return *this;
}

template <class T>
enum cpad::FilterType
cpad::Filter<T>::get_type()
{
  return m_type;
}

template <class T>
const char *
cpad::Filter<T>::get_expr()
{
  return m_filter_expr.c_str();
}
  
#endif
