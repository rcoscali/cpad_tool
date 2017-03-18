/*
 * Copyright ©2017 NagraFrance
 */

#include <iostream>
#include <fstream>

#include "CUnit.h"

using namespace std;

namespace cpad
{
  CUnit::CUnit()
    : CUnit(string(""))
  {
  }
  
  CUnit::CUnit(string filename)
    : ifstream(),
	  m_filename(filename),
	  m_length(0),
	  m_opened(false)
  {
    m_filename = filename;
    if (!m_filename.empty())
      {
        filebuf *fb = rdbuf();
        fb->open(m_filename.c_str(), ios::in);
        if (fb->is_open())
          {
            m_opened = true;
            seekg(0, end);
            if (tellg() > 0)
              m_length = tellg();
            seekg(0, beg);
          }
      }
  }

  CUnit::CUnit(const CUnit &a_copy)
    : CUnit()
  {
    m_filename = a_copy.m_filename;
    m_length = a_copy.m_length;
    m_opened = a_copy.m_opened;
  }

  CUnit::~CUnit()
  {
    if (m_opened && rdbuf() && rdbuf()->is_open())
      rdbuf()->close();
  }

  CUnit &
  CUnit::operator =(const CUnit &a_copy)
  {
    m_filename = a_copy.m_filename;
    m_length = a_copy.m_length;
    m_opened = a_copy.m_opened;
    return *this;
  }

  const char *
  CUnit::get_filename()
  {
    return m_filename.c_str();
  }

  unsigned long
  CUnit::get_length()
  {
    return m_length;
  }
}

