/*
 * Copyright ©2017 NagraFrance
 */


#include "Filter.h"

use namespace std;
use namespace cpad;

cpad::Filter::Filter(enum FilterType type)
{
  m_type = type;
  m_filter_expr = "";
  m_filter_regexp = regex("");
  m_applyon = "";
}
  
cpad::Filter::Filter(enum FilterType type, char const *expr)
: cpad::Filter(type)
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
  
cpad::Filter::~Filter()
{
}

cpad::Filter::Filter(cpad::Filter const& a_copy) 
{
  m_type = a_copy.m_type;
  m_filter_expr = a_copy.m_filter_expr;
  m_applyon = a_copy.m_applyon;
}

cpad::Filter&
cpad::Filter::operator = (cpad::Filter const &a_copy)
{
  m_type = a_copy.m_type;
  m_filter_expr = a_copy.m_filter_expr;
  m_applyon = a_copy.m_applyon;
  return *this;
}

enum cpad::FilterType
cpad::Filter::get_type()
{
  return m_type;
}

const char *
cpad::Filter::get_expr()
{
  return m_filter_expr.c_str();
}

string
cpad::Filter::get_applyon()
{
  return (m_applyon);
}

void
cpad::Filter::set_applyon(string applyon)
{
  m_applyon = applyon;
}
