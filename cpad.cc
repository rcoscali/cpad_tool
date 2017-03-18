/*
 * Copyright ©2017 NagraFrance
 */

#include <cstdlib>
#include <boost/program_options.hpp>

#include "xml3all.h"
#include "cpad.h"
#include "Filter.h"
#include "CUnit.h"

#define read_from_ifstream(IS) \
  if (IS)                                                             \
    {                                                                 \
      IS.seekg(0, is.end);                                            \
      filelen = IS.tellg();                                           \
      IS.seekg(0, IS.beg);                                            \
                                                                      \
      m_semantics_buffer = new char [filelen];                        \
                                                                      \
      IS.read(m_semantics_buffer, filelen);                           \
                                                                      \
      if (!IS)                                                        \
        cerr << "error: only " << IS.gcount() << " could be read" << endl;\
      IS.close();                                                     \
    }

using namespace std;
using namespace cpad;
using namespace XML3;
namespace po = boost::program_options;

Cpad::Cpad()
  : m_active(false),
    m_semantics_buffer((char *)NULL),
    m_semantics_path("cpad-semantics.xml")
{
  int filelen;
  ifstream is(m_semantics_path, ios::in);

  // First try local directory
  read_from_ifstream(is)
  else
    {
      // Then HOME directory
      const char *home = getenv("HOME");
      if (home)
        {
          m_semantics_path = string(home) + "/.cpad/" + m_semantics_path;
          ifstream ishome(m_semantics_path, ios::in);
          read_from_ifstream(ishome);
        }
    }

  if (filelen)
    cout << "Read file " << m_semantics_path << " (" << filelen << " bytes)" << endl;

  XML semantics(m_semantics_buffer, filelen);
  auto&root = semantics.GetRootElement();
  shared_ptr<XMLElement> coverage = root.FindElementZ("cpad:coverage");
  shared_ptr<XMLElement> compilunits = coverage->FindElementZ("cpad:compilunits");
  shared_ptr<XMLElement> filterselt1 = compilunits->FindElementZ("cpad:filters");
  vector<shared_ptr<XMLElement>> compilunits_filter_list = filterselt1->GetChildren();

  for (vector<shared_ptr<XMLElement>>::iterator vi = compilunits_filter_list.begin();
       vi != compilunits_filter_list.end(); vi++)
    {
      shared_ptr<XMLElement> filter_elt = *vi;
      shared_ptr<XMLVariable> applyon_attr = filter_elt->FindVariableZ("cpad:applyon");
      string applyon_value = applyon_attr->GetValue();
      shared_ptr<XMLVariable> type_attr = filter_elt->FindVariableZ("cpad:type");
      string type_value = type_attr->GetValue();
      vector<shared_ptr<XMLCData>> filter_cdata = filter_elt->GetCDatas();
      
      cout << "Filter applies on " << applyon_value << " and is of type " << type_value << endl;
      cout << (filter_cdata[0])->GetValue() << endl;

      const string expr = (filter_cdata[0])->GetValue();
      if (type_value.compare("expr"))
        {
          //Filter<CUnit> filter(cpad::EXPR);
          //m_cunit_filters.insert(m_cunit_filters.begin(),
          //                     filter);
        }
      else if (type_value.compare("regexp"))
        {
          //Filter<CUnit> filter(cpad::REGEXP, expr.c_str());
          //m_cunit_filters.insert(m_cunit_filters.begin(),
          //filter);
        }
      else if (type_value.compare("wildcard"))
        {
          //Filter<CUnit> filter(cpad::WILDCARD, expr.c_str());
          //m_cunit_filters.insert(m_cunit_filters.begin(),
          //                     filter);
        }
    }
  
  
  shared_ptr<XMLElement> listelt1 = compilunits->FindElementZ("cpad:list");
  vector<shared_ptr<XMLElement>> compilunits_list = listelt1->GetChildren();
  shared_ptr<XMLElement> functions = coverage->FindElementZ("cpad:functions");
  shared_ptr<XMLElement> filterselt2 = functions->FindElementZ("cpad:filters");
  vector<shared_ptr<XMLElement>> functions_filter_list = filterselt2->GetChildren();
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
