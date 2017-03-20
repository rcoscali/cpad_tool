/*
 * Copyright ©2017 NagraFrance
 */

#include "Cpad.h"

#include <memory>
#include <cstdlib>
#include <boost/program_options.hpp>

#include "xml3all.h"
#include "Filter.h"
#include "CUnit.h"

#define READ_FROM_STREAM(IS)                                               \
  if (IS)                                                                  \
    {                                                                      \
      IS.seekg(0, is.end);                                                 \
      filelen = IS.tellg();                                                \
      IS.seekg(0, IS.beg);                                                 \
                                                                           \
      m_semantics_buffer = new char [filelen];                             \
                                                                           \
      IS.read(m_semantics_buffer, filelen);                                \
                                                                           \
      if (!IS)                                                             \
        cerr << "error: only " << IS.gcount() << " could be read" << endl; \
      IS.close();                                                          \
    }

using namespace std;
using namespace cpad;
using namespace XML3;
namespace po = boost::program_options;

template <class T>
Cpad::CUnits<T>::CUnits() {}

template <class T>
Cpad::CUnits<T>::~CUnits() {}

template <class T>
Cpad::CUnits<T>::CUnits(Cpad::CUnits<T> const &a_copy) {}

template <class T>
Cpad::CUnits<T>&
Cpad::CUnits<T>::operator =(Cpad::CUnits<T> const &a_copy)
{
  return *this;
}

template <class T>
Cpad::Funcs<T>::Funcs() {}

template <class T>
Cpad::Funcs<T>::~Funcs() {}

template <class T>
Cpad::Funcs<T>::Funcs(Cpad::Funcs<T> const &a_copy) {}

template <class T>
Cpad::Funcs<T>&
Cpad::Funcs<T>::operator =(Cpad::Funcs<T> const &a_copy)
{
  return *this;
}

template <class T>
Cpad::Dirs<T>::Dirs() {}

template <class T>
Cpad::Dirs<T>::~Dirs() {}

template <class T>
Cpad::Dirs<T>::Dirs(Cpad::Dirs<T> const &a_copy) {}

template <class T>
Cpad::Dirs<T>&
Cpad::Dirs<T>::operator =(Cpad::Dirs<T> const &a_copy)
{
  return *this;
}

Cpad::Cpad()
  : m_active(false),
    m_semantics_buffer((char *)NULL),
    m_semantics_path("cpad-semantics.xml")
{
  int filelen;
  ifstream is(m_semantics_path, ios::in);

  // First try local directory
  READ_FROM_STREAM(is)
  else
    {
      // Then HOME directory
      const char *home = getenv("HOME");
      if (home)
        {
          m_semantics_path = string(home) + "/.cpad/" + m_semantics_path;
          ifstream ishome(m_semantics_path, ios::in);
          READ_FROM_STREAM(ishome);
        }
    }

  XML semantics(m_semantics_buffer, filelen);
  auto& root = semantics.GetRootElement();
  auto coverage = root.FindElementZ("cpad:coverage");
  auto compilunits = coverage->FindElementZ("cpad:compilunits");
  auto filterselt1 = compilunits->FindElementZ("cpad:filters");
  auto compilunits_filter_list = filterselt1->GetChildren();

  // Handle filters
  for (vector<shared_ptr<XMLElement>>::iterator vi = compilunits_filter_list.begin();
       vi != compilunits_filter_list.end(); vi++)
    {
      auto filter_elt = *vi;
      auto applyon_attr = filter_elt->FindVariableZ("cpad:applyon");
      string applyon_value = applyon_attr->GetValue();
      auto type_attr = filter_elt->FindVariableZ("cpad:type");
      string type_value = type_attr->GetValue();
      auto filter_cdata = filter_elt->GetCDatas();
      
      const string expr = (filter_cdata[0])->GetValue();
      if (type_value.compare("expr"))
        {
          Filter a_filter(cpad::EXPR, expr.c_str());
          a_filter.set_applyon(applyon_value);
          m_cunit_filters.push_back(a_filter);
        }
      else if (type_value.compare("regexp"))
        {
          Filter a_filter(cpad::REGEXP, expr.c_str());
          a_filter.set_applyon(applyon_value);
          m_cunit_filters.push_back(a_filter);
        }
      else if (type_value.compare("wildcard"))
        {
          Filter a_filter(cpad::WILDCARD, expr.c_str());
          a_filter.set_applyon(applyon_value);
          m_cunit_filters.push_back(a_filter);
        }
    }

#if 1
  for (vector<cpad::Filter>::iterator fi = m_filters.begin();
       fi != m_filters.end();
       fi++)
    {
      Filter filter = *fi;
      cout << "Filter: " << filter.get_expr() << endl;
    }
#endif

  // Handle cunits
  shared_ptr<XMLElement> listelt1 = compilunits->FindElementZ("cpad:list");
  vector<shared_ptr<XMLElement>> compilunits_list = listelt1->GetChildren();

  for (vector<shared_ptr<XMLElement>>::iterator culi = compilunits_list.begin();
       culi != compilunits_list.end();
       culi++)
    {
      CUnit cunit((*culi)->GetContent());
      cout << cunit.get_filename() << ": " << cunit.get_length() << " bytes" << endl;
      m_cunits.push_back(cunit);
    }

  
  shared_ptr<XMLElement> functions = coverage->FindElementZ("cpad:functions");
  shared_ptr<XMLElement> filterselt2 = functions->FindElementZ("cpad:filters");
  vector<shared_ptr<XMLElement>> functions_filter_list = filterselt2->GetChildren();
  
  // Handle filters
  for (vector<shared_ptr<XMLElement>>::iterator vi = functions_filter_list.begin();
       vi != functions_filter_list.end(); vi++)
    {
      auto filter_elt = *vi;
      auto applyon_attr = filter_elt->FindVariableZ("cpad:applyon");
      string applyon_value = applyon_attr->GetValue();
      auto type_attr = filter_elt->FindVariableZ("cpad:type");
      string type_value = type_attr->GetValue();
      auto filter_cdata = filter_elt->GetCDatas();
      
      const string expr = (filter_cdata[0])->GetValue();
      if (type_value.compare("expr"))
        {
          Filter a_filter(cpad::EXPR, expr.c_str());
          a_filter.set_applyon(applyon_value);
          m_func_filters.push_back(a_filter);
        }
      else if (type_value.compare("regexp"))
        {
          Filter a_filter(cpad::REGEXP, expr.c_str());
          a_filter.set_applyon(applyon_value);
          m_func_filters.push_back(a_filter);
        }
      else if (type_value.compare("wildcard"))
        {
          Filter a_filter(cpad::WILDCARD, expr.c_str());
          a_filter.set_applyon(applyon_value);
          m_func_filters.push_back(a_filter);
        }
    }

  shared_ptr<XMLElement> listelt2 = functions->FindElementZ("cpad:list");
  vector<shared_ptr<XMLElement>> functions_list = listelt2->GetChildren();

  shared_ptr<XMLElement> insnsdata = root.FindElementZ("cpad:insnsdata");
  vector<shared_ptr<XMLElement>> insns = insnsdata->GetChildren();

  shared_ptr<XMLVariable> processing = coverage->FindVariableZ("cpad:processing");

  cout << "CPAD Processing is " << processing->GetValue() << endl;
}

Cpad::Cpad(int argc, char **argv)
  : Cpad()
{
  // Declare the supported options.
  po::options_description desc("Allowed options");
  desc.add_options()
    ("help", "produce help message")
    ("compression", po::value<int>(), "set compression level")
    ;

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  if (vm.count("help"))
    {
      cout << desc << "\n";
    }
  else
    {
      if (vm.count("compression")) {
        cout << "Compression level was set to " 
             << vm["compression"].as<int>() << ".\n";
      } else {
        cout << "Compression level was not set.\n";
      }
    }
}

Cpad::~Cpad()
{
  if (m_semantics_buffer)
    delete[] m_semantics_buffer;
}

int
Cpad::do_tool_processing(void)
{
  int ret = 1;
  cout << "Processing ..." << endl;

  /*
   * Implement tool processing here
   */

  ret = 0;
  return ret;
}
