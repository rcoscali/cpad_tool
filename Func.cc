/*
 * Copyright ©2017 NagraFrance
 */

#include <string>

#include "Func.h"

using namespace std;

namespace cpad
{
  Func::Func(void)
    : Func("")
  {
  }

  Func::Func(string name)
  {
    m_name = name;
  }
  
  Func::Func(Func const& a_copy)
  {
    m_name = a_copy.m_name;
  }

  Func::~Func(void)
  {

  }
  Func& Func::operator =(Func const &a_copy)
  {
	m_name = a_copy.m_name;
  }

  const char *
  Func::get_name(void)
  {
	return m_name.c_str();
  }
}
