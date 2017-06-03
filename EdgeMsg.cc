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
cpad::cfg::EdgeRequestHelper::EdgeRequestHelper(std::string start_cunit_name, std::string start_cfun_name, std::string start_bb_name,
                                                std::string end_cunit_name, std::string end_cfun_name, std::string end_bb_name,
                                                cpad::cfg::EdgeKind edge_branch)
  : ::cpad::cfg::EdgeRequest()
{
  set_start_cunit_name(start_cunit_name);
  set_start_cfun_name(start_cfun_name);
  set_start_bb_name(start_bb_name);
  set_end_cunit_name(end_cunit_name);
  set_end_cfun_name(end_cfun_name);
  set_end_bb_name(end_bb_name);
  set_edge_branch(edge_branch);
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
 * Virtual destructor
 */
cpad::cfg::EdgeRequestHelper::~EdgeRequestHelper()
{
}

/**
 * Copy constructor
 */
cpad::cfg::EdgeRequestHelper::EdgeRequestHelper(cpad::cfg::EdgeRequestHelper const& a_copy)
  : cpad::cfg::EdgeRequestHelper(a_copy.start_cunit_name(), a_copy.start_cfun_name(), a_copy.start_bb_name(),
                                 a_copy.end_cunit_name(), a_copy.end_cfun_name(), a_copy.end_bb_name(),
                                 a_copy.edge_branch())
{
}

/**
 * Affectation Operator
 */
cpad::cfg::EdgeRequestHelper&
cpad::cfg::EdgeRequestHelper::operator =(cpad::cfg::EdgeRequestHelper const&a_copy)
{
  set_start_cunit_name(a_copy.start_cunit_name());
  set_start_cfun_name(a_copy.start_cfun_name());
  set_start_bb_name(a_copy.start_bb_name());
  set_end_cunit_name(a_copy.end_cunit_name());
  set_end_cfun_name(a_copy.end_cfun_name());
  set_end_bb_name(a_copy.end_bb_name());
  set_edge_branch(a_copy.edge_branch());
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
  osb << "[EdgeRequest]" << std::endl;
  osb << "  Start BB: " << std::endl;
  osb << "    | CUnit name: " << start_cunit_name() << std::endl;
  osb << "    | CFun name: " << start_cfun_name() << std::endl;
  osb << "    | BB name: " << start_bb_name() << std::endl;
  osb << "  End BB: " << std::endl;
  osb << "    | CUnit name: " << end_cunit_name() << std::endl;
  osb << "    | CFun name: " << end_cfun_name() << std::endl;
  osb << "    | BB name: " << end_bb_name() << std::endl;
  osb << "  Branch kind: " << ::cpad::cfg::EdgeKind_Name(edge_branch()) << std::endl;
}

cpad::cfg::EdgeResponseHelper::EdgeResponseHelper()
  : ::cpad::cfg::EdgeResponse()
{
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
  : cpad::cfg::EdgeResponseHelper()
{
}

cpad::cfg::EdgeResponseHelper&
cpad::cfg::EdgeResponseHelper::operator =(cpad::cfg::EdgeResponseHelper const&a_copy)
{
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
  osb << "[EdgeResponse]" << std::endl;
}
