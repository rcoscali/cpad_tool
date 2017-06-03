//
// Copyright ©2017 NagraFrance
//

#include "FunctionMsg.h"

//
// Function helpers implem
//

/**
 * Constructor
 */
cpad::cfg::FunctionRequestHelper::FunctionRequestHelper(std::string cunit_name, std::string cfun_name)
  : ::cpad::cfg::FunctionRequest()
{
  set_cunit_name(cunit_name);
  set_cfun_name(cfun_name);
}

/**
 * Deserialize constructor
 */
cpad::cfg::FunctionRequestHelper::FunctionRequestHelper(const char *buffer)
  : ::cpad::cfg::FunctionRequest()
{
  ParseFromString(std::string(buffer));
}

cpad::cfg::FunctionRequestHelper::FunctionRequestHelper(const ::cpad::cfg::FunctionRequest* request)
  : ::cpad::cfg::FunctionRequest(*request)
{
}

/**
 * Default constructor
 */
cpad::cfg::FunctionRequestHelper::~FunctionRequestHelper()
{
}

/**
 * Copy constructor
 */
cpad::cfg::FunctionRequestHelper::FunctionRequestHelper(cpad::cfg::FunctionRequestHelper const&a_copy)
  : cpad::cfg::FunctionRequestHelper(a_copy.cunit_name(),
                                     a_copy.cfun_name())
{
}

/**
 * Affectation Operator
 */
cpad::cfg::FunctionRequestHelper&
cpad::cfg::FunctionRequestHelper::operator =(cpad::cfg::FunctionRequestHelper const&a_copy)
{
  set_cunit_name(a_copy.cunit_name());
  set_cfun_name(a_copy.cfun_name());
  return *this;
}

/**
 * Serialize helper method
 */
size_t
cpad::cfg::FunctionRequestHelper::serialize(char *buffer)
{
  std::string local_buf;
  SerializeToString(&local_buf);
  local_buf.copy(buffer, local_buf.length());
  return local_buf.length();
}

/**
 * Dump helper method
 */
void
cpad::cfg::FunctionRequestHelper::dump(std::ostream& osb)
{
  osb << "[FunctionRequest]" << std::endl;
  osb << "  CUnit name: " << cunit_name() << std::endl;
  osb << "  CFun name: " << cfun_name() << std::endl;
}

cpad::cfg::FunctionResponseHelper::FunctionResponseHelper()
  : ::cpad::cfg::FunctionResponse()
{
}

cpad::cfg::FunctionResponseHelper::FunctionResponseHelper(const char *buffer)
  : ::cpad::cfg::FunctionResponse()
{
  ParseFromString(std::string(buffer));
}

cpad::cfg::FunctionResponseHelper::FunctionResponseHelper(const ::cpad::cfg::FunctionResponse* response)
  : ::cpad::cfg::FunctionResponse(*response)
{
}

cpad::cfg::FunctionResponseHelper::~FunctionResponseHelper()
{
}

cpad::cfg::FunctionResponseHelper::FunctionResponseHelper(cpad::cfg::FunctionResponseHelper const&a_copy)
  : cpad::cfg::FunctionResponseHelper()
{
}

cpad::cfg::FunctionResponseHelper&
cpad::cfg::FunctionResponseHelper::operator =(cpad::cfg::FunctionResponseHelper const&a_copy)
{
  return *this;
}

size_t
cpad::cfg::FunctionResponseHelper::serialize(char *buffer)
{
  std::string local_buf;
  SerializeToString(&local_buf);
  local_buf.copy(buffer, local_buf.length());
  return local_buf.length();
}

void
cpad::cfg::FunctionResponseHelper::dump(std::ostream& osb)
{
  osb << "[FunctionResponse]" << std::endl;
}

