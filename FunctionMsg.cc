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
cpad::cfg::FunctionRequestHelper::FunctionRequestHelper(std::string filename)
  : ::cpad::cfg::FunctionRequest()
{
  set_filename(filename);
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
  : cpad::cfg::FunctionRequestHelper(a_copy.filename())
{
}

/**
 * Affectation Operator
 */
cpad::cfg::FunctionRequestHelper&
cpad::cfg::FunctionRequestHelper::operator =(cpad::cfg::FunctionRequestHelper const&a_copy)
{
  set_filename(a_copy.filename());
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
  std::cout << "[FunctionRequest]" << std::endl;
  std::cout << "CUnit filename : " << filename() << std::endl;
}

cpad::cfg::FunctionResponseHelper::FunctionResponseHelper(std::string filename)
  : ::cpad::cfg::FunctionResponse()
{
  set_filename(filename);
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
  : cpad::cfg::FunctionResponseHelper(a_copy.cunit_name())
{
}

cpad::cfg::FunctionResponseHelper&
cpad::cfg::FunctionResponseHelper::operator =(cpad::cfg::FunctionResponseHelper const&a_copy)
{
  set_cunit_name(a_copy.cunit_name());
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
  std::cout << "[FunctionResponse]" << std::endl;
}

