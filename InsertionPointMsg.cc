//
// Copyright ©2017 NagraFrance
//

#include "InsertionPointMsg.h"

cpad::InsertionPointRequestHelper::InsertionPointRequestHelper(std::string cunit_name,
                                                               std::string cfun_name,
                                                               cpad_protobuf::InsertionLocation location)
  : ::cpad_protobuf::InsertionPointRequest()
{
  set_cunit_name(cunit_name);
  set_cfun_name(cfun_name);
  set_location(location);
}

cpad::InsertionPointRequestHelper::InsertionPointRequestHelper(const char *buffer)
  : ::cpad_protobuf::InsertionPointRequest()
{
  ParseFromString(std::string(buffer));
}

cpad::InsertionPointRequestHelper::~InsertionPointRequestHelper()
{
}

cpad::InsertionPointRequestHelper::InsertionPointRequestHelper(cpad::InsertionPointRequestHelper const&a_copy)
  : ::cpad::InsertionPointRequestHelper(a_copy.cunit_name(),
                                        a_copy.cfun_name(),
                                        a_copy.location())
{
}

cpad::InsertionPointRequestHelper&
cpad::InsertionPointRequestHelper::operator =(cpad::InsertionPointRequestHelper const&a_copy)
{
  set_cunit_name(a_copy.cunit_name());
  set_cfun_name(a_copy.cfun_name());
  set_location(a_copy.location());
  return *this;
}

size_t
cpad::InsertionPointRequestHelper::serialize(char *buffer)
{
  std::string local_buf;
  SerializeToString(&local_buf);
  local_buf.copy(buffer, local_buf.length());
  return local_buf.length();
}

void
cpad::InsertionPointRequestHelper::dump(void)
{
  std::cout << "cunit name : " << cunit_name() << std::endl;
  std::cout << "cfun name: " << cfun_name() << std::endl;
  std::cout << "location: " << location() << std::endl;
}

cpad::InsertionPointResponseHelper::InsertionPointResponseHelper(bool insert_asm_statement,
                                                                 std::string asm_statement)
  : ::cpad_protobuf::InsertionPointResponse()
{
  set_insert_asm_statement(insert_asm_statement);
  set_asm_statement(asm_statement);
}

cpad::InsertionPointResponseHelper::InsertionPointResponseHelper(const char *buffer)
  : ::cpad_protobuf::InsertionPointResponse()
{
  ParseFromString(std::string(buffer));
}

cpad::InsertionPointResponseHelper::~InsertionPointResponseHelper()
{
}

cpad::InsertionPointResponseHelper::InsertionPointResponseHelper(cpad::InsertionPointResponseHelper const&a_copy)
  : ::cpad::InsertionPointResponseHelper(a_copy.insert_asm_statement(),
                                         a_copy.asm_statement())
{
}

cpad::InsertionPointResponseHelper&
cpad::InsertionPointResponseHelper::operator =(cpad::InsertionPointResponseHelper const&a_copy)
{
  set_insert_asm_statement(a_copy.insert_asm_statement());
  set_asm_statement(a_copy.asm_statement());
}

size_t
cpad::InsertionPointResponseHelper::serialize(char *buffer)
{
  std::string local_buf;
  SerializeToString(&local_buf);
  local_buf.copy(buffer, local_buf.length());
  return local_buf.length();
}

void
cpad::InsertionPointResponseHelper::dump(void)
{
  std::cout << "insert asm statement : " << insert_asm_statement() << std::endl;
  std::cout << "asm statement: " << asm_statement() << std::endl;
}

