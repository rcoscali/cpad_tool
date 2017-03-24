//
// Copyright ©2017 NagraFrance
//

#include "CUnitTerminateMsg.h"

cpad::CUnitTerminateRequestHelper::CUnitTerminateRequestHelper(std::string cunit_name)
  : ::cpad_protobuf::CUnitTerminateRequest()
{
  set_cunit_name(cunit_name);
}

cpad::CUnitTerminateRequestHelper::CUnitTerminateRequestHelper(const char *buffer)
  : ::cpad_protobuf::CUnitTerminateRequest()
{
  ParseFromString(std::string(buffer));
}

cpad::CUnitTerminateRequestHelper::~CUnitTerminateRequestHelper()
{
}

cpad::CUnitTerminateRequestHelper::CUnitTerminateRequestHelper(cpad::CUnitTerminateRequestHelper const&a_copy)
  : cpad::CUnitTerminateRequestHelper(a_copy.cunit_name())
{
}

cpad::CUnitTerminateRequestHelper&
cpad::CUnitTerminateRequestHelper::operator =(cpad::CUnitTerminateRequestHelper const&a_copy)
{
  set_cunit_name(a_copy.cunit_name());
  return *this;
}

size_t
cpad::CUnitTerminateRequestHelper::serialize(char *buffer)
{
  std::string local_buf;
  SerializeToString(&local_buf);
  local_buf.copy(buffer, local_buf.length());
  return local_buf.length();
}

void
cpad::CUnitTerminateRequestHelper::dump(void)
{
  std::cout << "CUnit name : " << cunit_name() << std::endl;
}

cpad::CUnitTerminateResponseHelper::CUnitTerminateResponseHelper(std::string cunit_name)
  : ::cpad_protobuf::CUnitTerminateResponse()
{
  set_cunit_name(cunit_name);
}

cpad::CUnitTerminateResponseHelper::CUnitTerminateResponseHelper(const char *buffer)
  : ::cpad_protobuf::CUnitTerminateResponse()
{
  ParseFromString(std::string(buffer));
}

cpad::CUnitTerminateResponseHelper::~CUnitTerminateResponseHelper()
{
}

cpad::CUnitTerminateResponseHelper::CUnitTerminateResponseHelper(cpad::CUnitTerminateResponseHelper const&a_copy)
  : cpad::CUnitTerminateResponseHelper(a_copy.cunit_name())
{
}

cpad::CUnitTerminateResponseHelper&
cpad::CUnitTerminateResponseHelper::operator =(cpad::CUnitTerminateResponseHelper const&a_copy)
{
  set_cunit_name(a_copy.cunit_name());
  return *this;
}

size_t
cpad::CUnitTerminateResponseHelper::serialize(char *buffer)
{
  std::string local_buf;
  SerializeToString(&local_buf);
  local_buf.copy(buffer, local_buf.length());
  return local_buf.length();
}

void
cpad::CUnitTerminateResponseHelper::dump(void)
{
  std::cout << "CUnit name : " << cunit_name() << std::endl;
}

