//
// Copyright ©2017 NagraFrance
//

#include "InsertionPointMsg.h"

cpad::insns::InsertionPointRequestHelper::InsertionPointRequestHelper(std::string cunit_name,
                                                               std::string cfun_name,
                                                               cpad::insns::InsertionLocation location)
  : ::cpad::insns::InsertionPointRequest()
{
  set_cunit_name(cunit_name);
  set_cfun_name(cfun_name);
  set_location(location);
}

cpad::insns::InsertionPointRequestHelper::InsertionPointRequestHelper(const char *buffer)
  : ::cpad::insns::InsertionPointRequest()
{
  ParseFromString(std::string(buffer));
}

cpad::insns::InsertionPointRequestHelper::~InsertionPointRequestHelper()
{
}

cpad::insns::InsertionPointRequestHelper::InsertionPointRequestHelper(cpad::insns::InsertionPointRequestHelper const&a_copy)
  : ::cpad::insns::InsertionPointRequestHelper(a_copy.cunit_name(),
                                        a_copy.cfun_name(),
                                        a_copy.location())
{
}

cpad::insns::InsertionPointRequestHelper&
cpad::insns::InsertionPointRequestHelper::operator =(cpad::insns::InsertionPointRequestHelper const&a_copy)
{
  set_cunit_name(a_copy.cunit_name());
  set_cfun_name(a_copy.cfun_name());
  set_location(a_copy.location());
  return *this;
}

size_t
cpad::insns::InsertionPointRequestHelper::serialize(char *buffer)
{
  std::string local_buf;
  SerializeToString(&local_buf);
  local_buf.copy(buffer, local_buf.length());
  return local_buf.length();
}

void
cpad::insns::InsertionPointRequestHelper::dump(std::ostream &osb)
{
  osb << "[InsertionPointRequestHelper]" << std::endl;
  osb << "cunit name: " << cunit_name() << std::endl;
  osb << "cfun name: " << cfun_name() << std::endl;
  osb << "location: " << location() << std::endl;
}

cpad::insns::InsertionPointResponseHelper::InsertionPointResponseHelper(bool insert_asm_statement,
                                                                 std::string asm_statement)
  : ::cpad::insns::InsertionPointResponse()
{
  set_insert_asm_statement(insert_asm_statement);
  set_asm_statement(asm_statement);
}

cpad::insns::InsertionPointResponseHelper::InsertionPointResponseHelper(const char *buffer)
  : ::cpad::insns::InsertionPointResponse()
{
  ParseFromString(std::string(buffer));
}

cpad::insns::InsertionPointResponseHelper::~InsertionPointResponseHelper()
{
}

cpad::insns::InsertionPointResponseHelper::InsertionPointResponseHelper(cpad::insns::InsertionPointResponseHelper const&a_copy)
  : ::cpad::insns::InsertionPointResponseHelper(a_copy.insert_asm_statement(),
                                         a_copy.asm_statement())
{
}

cpad::insns::InsertionPointResponseHelper&
cpad::insns::InsertionPointResponseHelper::operator =(cpad::insns::InsertionPointResponseHelper const&a_copy)
{
  set_insert_asm_statement(a_copy.insert_asm_statement());
  set_asm_statement(a_copy.asm_statement());
}

size_t
cpad::insns::InsertionPointResponseHelper::serialize(char *buffer)
{
  std::string local_buf;
  SerializeToString(&local_buf);
  local_buf.copy(buffer, local_buf.length());
  return local_buf.length();
}

void
cpad::insns::InsertionPointResponseHelper::dump(std::ostream &osb)
{
  osb << "[InsertionPointResponseHelper]" << std::endl;
  osb << "insert asm statement: " << insert_asm_statement() << std::endl;
  osb << "asm statement: " << asm_statement() << std::endl;
}

