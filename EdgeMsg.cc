//
// Copyright ©2017 NagraFrance
//

#include "EdgeMsg.h"

//
// Edge helpers implem
//

/**
 * Constructor
 */
cpad::cfg::EdgeRequestHelper::EdgeRequestHelper(std::string filename)
  : ::cpad::cfg::EdgeRequest()
{
  set_filename(filename);
}

/**
 * Deserialize constructor
 */
cpad::cfg::EdgeRequestHelper::EdgeRequestHelper(const char *buffer)
  : ::cpad::cfg::EdgeRequest()
{
  ParseFromString(std::string(buffer));
}

cpad::cfg::EdgeRequestHelper::EdgeRequestHelper(const ::cpad::cfg::EdgeRequest* request)
  : ::cpad::cfg::EdgeRequest(*request)
{
}

/**
 * Default constructor
 */
cpad::cfg::EdgeRequestHelper::~EdgeRequestHelper()
{
}

/**
 * Copy constructor
 */
cpad::cfg::EdgeRequestHelper::EdgeRequestHelper(cpad::cfg::EdgeRequestHelper const&a_copy)
  : cpad::cfg::EdgeRequestHelper(a_copy.filename())
{
}

/**
 * Affectation Operator
 */
cpad::cfg::EdgeRequestHelper&
cpad::cfg::EdgeRequestHelper::operator =(cpad::cfg::EdgeRequestHelper const&a_copy)
{
  set_filename(a_copy.filename());
  return *this;
}

/**
 * Serialize helper method
 */
size_t
cpad::cfg::EdgeRequestHelper::serialize(char *buffer)
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
cpad::cfg::EdgeRequestHelper::dump(std::ostream& osb)
{
  std::cout << "[EdgeRequest]" << std::endl;
  std::cout << "CUnit filename : " << filename() << std::endl;
}

cpad::cfg::EdgeResponseHelper::EdgeResponseHelper(std::string filename)
  : ::cpad::cfg::EdgeResponse()
{
  set_filename(filename);
}

cpad::cfg::EdgeResponseHelper::EdgeResponseHelper(const char *buffer)
  : ::cpad::cfg::EdgeResponse()
{
  ParseFromString(std::string(buffer));
}

cpad::cfg::EdgeResponseHelper::EdgeResponseHelper(const ::cpad::cfg::EdgeResponse* response)
  : ::cpad::cfg::EdgeResponse(*response)
{
}

cpad::cfg::EdgeResponseHelper::~EdgeResponseHelper()
{
}

cpad::cfg::EdgeResponseHelper::EdgeResponseHelper(cpad::cfg::EdgeResponseHelper const&a_copy)
  : cpad::cfg::EdgeResponseHelper(a_copy.cunit_name())
{
}

cpad::cfg::EdgeResponseHelper&
cpad::cfg::EdgeResponseHelper::operator =(cpad::cfg::EdgeResponseHelper const&a_copy)
{
  set_cunit_name(a_copy.cunit_name());
  return *this;
}

size_t
cpad::cfg::EdgeResponseHelper::serialize(char *buffer)
{
  std::string local_buf;
  SerializeToString(&local_buf);
  local_buf.copy(buffer, local_buf.length());
  return local_buf.length();
}

void
cpad::cfg::EdgeResponseHelper::dump(std::ostream& osb)
{
  std::cout << "[EdgeResponse]" << std::endl;
}

