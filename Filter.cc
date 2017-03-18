/*
 * Copyright ©2017 NagraFrance
 */

#include "CUnit.h"
#include "Filter.h"

using namespace std;

namespace cpad
{
  template <class T>
  Filter<T>::Filter(enum FilterType type)
  {
    m_type = type;
    m_filter_expr = "";
    m_filter_regexp = regex("");
  }
  
  template <class T>
  Filter<T>::Filter(enum FilterType type, const char *expr)
    : Filter(type)
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
  Filter<T>::~Filter()
  {
  }

  template <class T>
  Filter<T>::Filter(Filter<T> const& a_copy) 
  {
    m_type = a_copy.m_type;
    m_filter_expr = a_copy.m_filter_expr;
  }

  template <class T>
  Filter<T>&
  Filter<T>::operator =(const Filter<T> &a_copy)
  {
    m_type = a_copy.m_type;
    m_filter_expr = a_copy.m_filter_expr;
    return *this;
  }
}

cpad::Filter<cpad::CUnit> a_filter(cpad::EXPR);

