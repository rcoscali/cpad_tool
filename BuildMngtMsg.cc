//
// Copyright ©2017 NagraFrance
//

#include "BuildMngtMsg.h"

cpad::StartCfgCollectionRequestHelper::StartCfgCollectionRequestHelper(std::string build_name,
								       uint32_t number_cunits,
								       std::string cpad_config)
  : ::cpad_protobuf::StartCfgCollectionRequest()
{
  set_build_name(minor);
  set_number_cunits(major);
  set_cpad_config(provider_name);
}

cpad::StartCfgCollectionRequestHelper::StartCfgCollectionRequestHelper(const char *buffer)
  : ::cpad_protobuf::StartCfgCollectionRequest()
{
  ParseFromString(std::string(buffer));
}

cpad::StartCfgCollectionRequestHelper::~StartCfgCollectionRequestHelper()
{
}

cpad::StartCfgCollectionRequestHelper::StartCfgCollectionRequestHelper(StartCfgCollectionRequestHelper const&a_copy)
  : ::cpad::StartCfgCollectionRequestHelper(a_copy.build_name(),
					    a_copy.number_cunits(),
					    a_copy.cpad_config())
{
}

cpad::StartCfgCollectionRequestHelper&
cpad::StartCfgCollectionRequestHelper::operator =(StartCfgCollectionRequestHelper const&a_copy)
{
  set_client_version_minor(a_copy.build_name());
  set_client_version_major(a_copy.number_cunits());
  set_client_provider_name(a_copy.cpad_config());
  return *this;
}

size_t
cpad::StartCfgCollectionRequestHelper::serialize(char *buffer)
{
  std::string local_buf;
  SerializeToString(&local_buf);
  local_buf.copy(buffer, local_buf.length());
  return local_buf.length();
}

void
cpad::StartCfgCollectionRequestHelper::dump(void)
{
  std::cout << "build name: " << build_name() << std::endl;
  std::cout << "number cunits: " << number_cunits() << std::endl;
  std::cout << "cpad_config: " << cpad_config() << std::endl;
}

cpad::StartCfgCollectionResponseHelper::StartCfgCollectionResponseHelper(bool cpad_config_ok,
									 std::string uuid)
  : ::cpad_protobuf::StartCfgCollectionResponse()
{
  set_cpad_config_ok(cpad_config_ok);
  set_uuid(uuid);
}

cpad::StartCfgCollectionResponseHelper::StartCfgCollectionResponseHelper(const char *buffer)
  : ::cpad_protobuf::StartCfgCollectionResponse()
{
  ParseFromString(std::string(buffer));
}

cpad::StartCfgCollectionResponseHelper::~StartCfgCollectionResponseHelper()
{
}

cpad::StartCfgCollectionResponseHelper::StartCfgCollectionResponseHelper(StartCfgCollectionResponseHelper const&a_copy)
  : ::cpad::StartCfgCollectionResponseHelper(a_copy.cpad_config_ok(),
					     a_copy.uuid())
{
}

cpad::StartCfgCollectionResponseHelper&
cpad::StartCfgCollectionResponseHelper::operator =(StartCfgCollectionResponseHelper const&a_copy)
{
  set_server_version_minor(a_copy.cpad_config_ok());
  set_server_version_major(a_copy.uuid());
  return *this;
}

size_t
cpad::StartCfgCollectionResponseHelper::serialize(char *buffer)
{
  std::string local_buf;
  SerializeToString(&local_buf);
  local_buf.copy(buffer, local_buf.length());
  return local_buf.length();
}

void
cpad::StartCfgCollectionResponseHelper::dump(void)
{
  std::cout << "cpad config ok: " << cpad_config_ok() << std::endl;
  std::cout << "uuid: " << uuid() << std::endl;
}

cpad::EndCfgCollectionRequestHelper::EndCfgCollectionRequestHelper()
  : ::cpad_protobuf::EndCfgCollectionRequest()
{
}

cpad::EndCfgCollectionRequestHelper::EndCfgCollectionRequestHelper(const char *buffer)
  : ::cpad_protobuf::EndCfgCollectionRequest()
{
  ParseFromString(std::string(buffer));
}

cpad::EndCfgCollectionRequestHelper::~EndCfgCollectionRequestHelper()
{
}

cpad::EndCfgCollectionRequestHelper::EndCfgCollectionRequestHelper(EndCfgCollectionRequestHelper const&a_copy)
  : ::cpad::EndCfgCollectionRequestHelper()
{
}

cpad::EndCfgCollectionRequestHelper&
cpad::EndCfgCollectionRequestHelper::operator =(EndCfgCollectionRequestHelper const&a_copy)
{
  return *this;
}

size_t
cpad::EndCfgCollectionRequestHelper::serialize(char *buffer)
{
  std::string local_buf;
  SerializeToString(&local_buf);
  local_buf.copy(buffer, local_buf.length());
  return local_buf.length();
}

void
cpad::EndCfgCollectionRequestHelper::dump(void)
{
  std::cout << "no properties" << std::endl;
}

cpad::EndCfgCollectionResponseHelper::EndCfgCollectionResponseHelper(bool apex_allocation_status)
  : ::cpad_protobuf::EndCfgCollectionResponse()
{
  set_apex_allocation_status(apex_allocation_status);
}

cpad::EndCfgCollectionResponseHelper::EndCfgCollectionResponseHelper(const char *buffer)
  : ::cpad_protobuf::EndCfgCollectionResponse()
{
  ParseFromString(std::string(buffer));
}

cpad::EndCfgCollectionResponseHelper::~EndCfgCollectionResponseHelper()
{
}

cpad::EndCfgCollectionResponseHelper::EndCfgCollectionResponseHelper(EndCfgCollectionResponseHelper const&a_copy)
  : ::cpad::EndCfgCollectionResponseHelper(a_copy.apex_allocation_status())
{
}

cpad::EndCfgCollectionResponseHelper&
cpad::EndCfgCollectionResponseHelper::operator =(EndCfgCollectionResponseHelper const&a_copy)
{
  set_apex_allocation_status(a_copy.apex_allocation_status());
  return *this;
}

size_t
cpad::EndCfgCollectionResponseHelper::serialize(char *buffer)
{
  std::string local_buf;
  SerializeToString(&local_buf);
  local_buf.copy(buffer, local_buf.length());
  return local_buf.length();
}

void
cpad::EndCfgCollectionResponseHelper::dump(void)
{
  std::cout << "apex allocation status: " << apex_allocation_status() << std::endl;
}

cpad::StartCfgToolingRequestHelper::StartCfgToolingRequestHelper()
  : ::cpad_protobuf::StartCfgToolingRequest()
{
}

cpad::StartCfgToolingRequestHelper::StartCfgToolingRequestHelper(const char *buffer)
  : ::cpad_protobuf::StartCfgToolingRequest()
{
  ParseFromString(std::string(buffer));
}

cpad::StartCfgToolingRequestHelper::~StartCfgToolingRequestHelper()
{
}

cpad::StartCfgToolingRequestHelper::StartCfgToolingRequestHelper(StartCfgToolingRequestHelper const&a_copy)
  : ::cpad::StartCfgToolingRequestHelper()
{
}

cpad::StartCfgToolingRequestHelper&
cpad::StartCfgToolingRequestHelper::operator =(StartCfgToolingRequestHelper const&a_copy)
{
  return *this;
}

size_t
cpad::StartCfgToolingRequestHelper::serialize(char *buffer)
{
  std::string local_buf;
  SerializeToString(&local_buf);
  local_buf.copy(buffer, local_buf.length());
  return local_buf.length();
}

void
cpad::StartCfgToolingRequestHelper::dump(void)
{
  std::cout << "no properties" << std::endl;
}

cpad::StartCfgToolingResponseHelper::StartCfgToolingResponseHelper()
  : ::cpad_protobuf::StartCfgToolingResponse()
{
}

cpad::StartCfgToolingResponseHelper::StartCfgToolingResponseHelper(const char *buffer)
  : ::cpad_protobuf::StartCfgToolingResponse()
{
  ParseFromString(std::string(buffer));
}

cpad::StartCfgToolingResponseHelper::~StartCfgToolingResponseHelper()
{
}

cpad::StartCfgToolingResponseHelper::StartCfgToolingResponseHelper(StartCfgToolingResponseHelper const&a_copy)
  : ::cpad::StartCfgToolingResponseHelper()
{
}

cpad::StartCfgToolingResponseHelper&
cpad::StartCfgToolingResponseHelper::operator =(StartCfgToolingResponseHelper const&a_copy)
{
  return *this;
}

size_t
cpad::StartCfgToolingResponseHelper::serialize(char *buffer)
{
  std::string local_buf;
  SerializeToString(&local_buf);
  local_buf.copy(buffer, local_buf.length());
  return local_buf.length();
}

void
cpad::StartCfgToolingResponseHelper::dump(void)
{
  std::cout << "no properties" << std::endl;
}

cpad::EndCfgToolingRequestHelper::EndCfgToolingRequestHelper()
  : ::cpad_protobuf::EndCfgToolingRequest()
{
}

cpad::EndCfgToolingRequestHelper::EndCfgToolingRequestHelper(const char *buffer)
  : ::cpad_protobuf::EndCfgToolingRequest()
{
  ParseFromString(std::string(buffer));
}

cpad::EndCfgToolingRequestHelper::~EndCfgToolingRequestHelper()
{
}

cpad::EndCfgToolingRequestHelper::EndCfgToolingRequestHelper(EndCfgToolingRequestHelper const&a_copy)
  : ::cpad::EndCfgToolingRequestHelper()
{
}

cpad::EndCfgToolingRequestHelper&
cpad::EndCfgToolingRequestHelper::operator =(EndCfgToolingRequestHelper const&a_copy)
{
  return *this;
}

size_t
cpad::EndCfgToolingRequestHelper::serialize(char *buffer)
{
  std::string local_buf;
  SerializeToString(&local_buf);
  local_buf.copy(buffer, local_buf.length());
  return local_buf.length();
}

void
cpad::EndCfgToolingRequestHelper::dump(void)
{
  std::cout << "no properties" << std::endl;
}

cpad::EndCfgToolingResponseHelper::EndCfgToolingResponseHelper(uint32_t number_bb,
							       uint32_t number_modified_bb)
  : ::cpad_protobuf::EndCfgToolingResponse()
{
  set_number_bb(number_bb);
  set_number_modified_bb(number_modified_bb);
}

cpad::EndCfgToolingResponseHelper::EndCfgToolingResponseHelper(const char *buffer)
  : ::cpad_protobuf::EndCfgToolingResponse()
{
  ParseFromString(std::string(buffer));
}

cpad::EndCfgToolingResponseHelper::~EndCfgToolingResponseHelper()
{
}

cpad::EndCfgToolingResponseHelper::EndCfgToolingResponseHelper(EndCfgToolingResponseHelper const&a_copy)
  : ::cpad::EndCfgToolingResponseHelper(a_copy.number_bb(),
					a_copy.number_modified_bb())
{
}

cpad::EndCfgToolingResponseHelper&
cpad::EndCfgToolingResponseHelper::operator =(EndCfgToolingResponseHelper const&a_copy)
{
  set_server_version_minor(a_copy.number_bb());
  set_server_version_major(a_copy.number_modified_bb());
  return *this;
}

size_t
cpad::EndCfgToolingResponseHelper::serialize(char *buffer)
{
  std::string local_buf;
  SerializeToString(&local_buf);
  local_buf.copy(buffer, local_buf.length());
  return local_buf.length();
}

void
cpad::EndCfgToolingResponseHelper::dump(void)
{
  std::cout << "number bb: " << server_number_bb() << std::endl;
  std::cout << "server major: " << server_number_modified_bb() << std::endl;
}

