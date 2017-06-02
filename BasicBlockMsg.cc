//
// Copyright ©2017 NagraFrance
//

#include "BasicBlockMsg.h"

//
// BasicBlock helpers implem
//

/**
 * Constructor
 */
cpad::cfg::BasicBlockRequestHelper::BasicBlockRequestHelper(std::string filename)
  : ::cpad::cfg::BasicBlockRequest()
{
  set_filename(filename);
}

/**
 * Deserialize constructor
 */
cpad::cfg::BasicBlockRequestHelper::BasicBlockRequestHelper(const char *buffer)
  : ::cpad::cfg::BasicBlockRequest()
{
  ParseFromString(std::string(buffer));
}

cpad::cfg::BasicBlockRequestHelper::BasicBlockRequestHelper(const ::cpad::cfg::BasicBlockRequest* request)
  : ::cpad::cfg::BasicBlockRequest(*request)
{
}

/**
 * Default constructor
 */
cpad::cfg::BasicBlockRequestHelper::~BasicBlockRequestHelper()
{
}

/**
 * Copy constructor
 */
cpad::cfg::BasicBlockRequestHelper::BasicBlockRequestHelper(cpad::cfg::BasicBlockRequestHelper const&a_copy)
  : cpad::cfg::BasicBlockRequestHelper(a_copy.filename())
{
}

/**
 * Affectation Operator
 */
cpad::cfg::BasicBlockRequestHelper&
cpad::cfg::BasicBlockRequestHelper::operator =(cpad::cfg::BasicBlockRequestHelper const&a_copy)
{
  set_filename(a_copy.filename());
  return *this;
}

/**
 * Serialize helper method
 */
size_t
cpad::cfg::BasicBlockRequestHelper::serialize(char *buffer)
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
cpad::cfg::BasicBlockRequestHelper::dump(std::ostream& osb)
{
  std::cout << "[BasicBlockRequest]" << std::endl;
  std::cout << "CUnit filename : " << filename() << std::endl;
}

cpad::cfg::BasicBlockResponseHelper::BasicBlockResponseHelper(std::string filename)
  : ::cpad::cfg::BasicBlockResponse()
{
  set_filename(filename);
}

cpad::cfg::BasicBlockResponseHelper::BasicBlockResponseHelper(const char *buffer)
  : ::cpad::cfg::BasicBlockResponse()
{
  ParseFromString(std::string(buffer));
}

cpad::cfg::BasicBlockResponseHelper::BasicBlockResponseHelper(const ::cpad::cfg::BasicBlockResponse* response)
  : ::cpad::cfg::BasicBlockResponse(*response)
{
}

cpad::cfg::BasicBlockResponseHelper::~BasicBlockResponseHelper()
{
}

cpad::cfg::BasicBlockResponseHelper::BasicBlockResponseHelper(cpad::cfg::BasicBlockResponseHelper const&a_copy)
  : cpad::cfg::BasicBlockResponseHelper(a_copy.cunit_name())
{
}

cpad::cfg::BasicBlockResponseHelper&
cpad::cfg::BasicBlockResponseHelper::operator =(cpad::cfg::BasicBlockResponseHelper const&a_copy)
{
  set_cunit_name(a_copy.cunit_name());
  return *this;
}

size_t
cpad::cfg::BasicBlockResponseHelper::serialize(char *buffer)
{
  std::string local_buf;
  SerializeToString(&local_buf);
  local_buf.copy(buffer, local_buf.length());
  return local_buf.length();
}

void
cpad::cfg::BasicBlockResponseHelper::dump(std::ostream& osb)
{
  std::cout << "[BasicBlockResponse]" << std::endl;
}

