//
// Copyright ©2017 NagraFrance
//

#include "VersionMsg.h"

cpad::VersionRequestHelper::VersionRequestHelper(uint32_t minor,
                                                 uint32_t major,
                                                 std::string provider_name)
  : ::cpad_protobuf::VersionRequest()
{
  set_client_version_minor(minor);
  set_client_version_major(major);
  set_client_provider_name(provider_name);
}

cpad::VersionRequestHelper::VersionRequestHelper(const char *buffer)
  : ::cpad_protobuf::VersionRequest()
{
  ParseFromString(std::string(buffer));
}

cpad::VersionRequestHelper::~VersionRequestHelper()
{
}

cpad::VersionRequestHelper::VersionRequestHelper(VersionRequestHelper const&a_copy)
  : ::cpad::VersionRequestHelper(a_copy.client_version_minor(),
                                 a_copy.client_version_major(),
                                 a_copy.client_provider_name())
{
}

cpad::VersionRequestHelper&
cpad::VersionRequestHelper::operator =(VersionRequestHelper const&a_copy)
{
  set_client_version_minor(a_copy.client_version_minor());
  set_client_version_major(a_copy.client_version_major());
  set_client_provider_name(a_copy.client_provider_name());
  return *this;
}

size_t
cpad::VersionRequestHelper::serialize(char *buffer)
{
  std::string local_buf;
  SerializeToString(&local_buf);
  local_buf.copy(buffer, local_buf.length());
  return local_buf.length();
}

void
cpad::VersionRequestHelper::dump(void)
{
  std::cout << "client minor: " << client_version_minor() << std::endl;
  std::cout << "client major: " << client_version_major() << std::endl;
  std::cout << "client provider: " << client_provider_name() << std::endl;
}

cpad::VersionResponseHelper::VersionResponseHelper(uint32_t minor,
                                                   uint32_t major,
                                                   std::string provider_name)
  : ::cpad_protobuf::VersionResponse()
{
  set_server_version_minor(minor);
  set_server_version_major(major);
  set_server_provider_name(provider_name);
}

cpad::VersionResponseHelper::VersionResponseHelper(const char *buffer)
  : ::cpad_protobuf::VersionResponse()
{
  ParseFromString(std::string(buffer));
}

cpad::VersionResponseHelper::~VersionResponseHelper()
{
}

cpad::VersionResponseHelper::VersionResponseHelper(VersionResponseHelper const&a_copy)
  : ::cpad::VersionResponseHelper(a_copy.server_version_minor(),
                                  a_copy.server_version_major(),
                                  a_copy.server_provider_name())
{
}

cpad::VersionResponseHelper&
cpad::VersionResponseHelper::operator =(VersionResponseHelper const&a_copy)
{
  set_server_version_minor(a_copy.server_version_minor());
  set_server_version_major(a_copy.server_version_major());
  set_server_provider_name(a_copy.server_provider_name());
  return *this;
}

size_t
cpad::VersionResponseHelper::serialize(char *buffer)
{
  std::string local_buf;
  SerializeToString(&local_buf);
  local_buf.copy(buffer, local_buf.length());
  return local_buf.length();
}

void
cpad::VersionResponseHelper::dump(void)
{
  std::cout << "server minor: " << server_version_minor() << std::endl;
  std::cout << "server major: " << server_version_major() << std::endl;
  std::cout << "server provider: " << server_provider_name() << std::endl;
}

