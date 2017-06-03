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
cpad::cfg::BasicBlockRequestHelper::BasicBlockRequestHelper(std::string cunit_name,
                                                            std::string cfun_name,
                                                            std::string bb_name)
  : ::cpad::cfg::BasicBlockRequest()
{
  set_cunit_name(cunit_name);
  set_cfun_name(cfun_name);
  set_bb_name(bb_name);
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
  : cpad::cfg::BasicBlockRequestHelper(a_copy.cunit_name(),
                                       a_copy.cfun_name(),
                                       a_copy.bb_name())
{
}

/**
 * Affectation Operator
 */
cpad::cfg::BasicBlockRequestHelper&
cpad::cfg::BasicBlockRequestHelper::operator =(cpad::cfg::BasicBlockRequestHelper const&a_copy)
{
  set_cunit_name(a_copy.cunit_name());
  set_cfun_name(a_copy.cfun_name());
  set_bb_name(a_copy.bb_name());
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
  osb << "[BasicBlockRequest]" << std::endl;
  osb << "  CUnit name: " << cunit_name() << std::endl;
  osb << "  CFun name: " << cfun_name() << std::endl;
  osb << "  BB name: " << bb_name() << std::endl;
}

cpad::cfg::BasicBlockResponseHelper::BasicBlockResponseHelper()
  : ::cpad::cfg::BasicBlockResponse()
{
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
  : cpad::cfg::BasicBlockResponseHelper()
{
}

cpad::cfg::BasicBlockResponseHelper&
cpad::cfg::BasicBlockResponseHelper::operator =(cpad::cfg::BasicBlockResponseHelper const&a_copy)
{
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
  osb << "[BasicBlockResponse]" << std::endl;
}

