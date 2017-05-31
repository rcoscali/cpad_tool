//
// Copyright ©2017 NagraFrance
//

#include <iostream>

#include "VersionMsg.h"

cpad::insns::VersionRequestHelper::VersionRequestHelper(uint32_t minor,
                                                 uint32_t major,
                                                 std::string provider_name)
  : ::cpad::insns::VersionRequest()
{
  set_client_version_minor(minor);
  set_client_version_major(major);
  set_client_provider_name(provider_name);
}

cpad::insns::VersionRequestHelper::VersionRequestHelper(const char *buffer)
  : ::cpad::insns::VersionRequest()
{
  ParseFromString(std::string(buffer));
}

cpad::insns::VersionRequestHelper::~VersionRequestHelper()
{
}

cpad::insns::VersionRequestHelper::VersionRequestHelper(VersionRequestHelper const&a_copy)
  : ::cpad::insns::VersionRequestHelper(a_copy.client_version_minor(),
                                 a_copy.client_version_major(),
                                 a_copy.client_provider_name())
{
}

cpad::insns::VersionRequestHelper&
cpad::insns::VersionRequestHelper::operator =(VersionRequestHelper const&a_copy)
{
  set_client_version_minor(a_copy.client_version_minor());
  set_client_version_major(a_copy.client_version_major());
  set_client_provider_name(a_copy.client_provider_name());
  return *this;
}

size_t
cpad::insns::VersionRequestHelper::serialize(char *buffer)
{
  std::string local_buf;
  SerializeToString(&local_buf);
  local_buf.copy(buffer, local_buf.length());
  return local_buf.length();
}

void
cpad::insns::VersionRequestHelper::dump(std::ostream &osb)
{
  osb << "[VersionRequestHelper]" << std::endl;
  osb << "client minor: " << client_version_minor() << std::endl;
  osb << "client major: " << client_version_major() << std::endl;
  osb << "client provider: " << client_provider_name() << std::endl;
}

cpad::insns::VersionResponseHelper::VersionResponseHelper(uint32_t minor,
                                                   uint32_t major,
                                                   std::string provider_name)
  : ::cpad::insns::VersionResponse()
{
  set_server_version_minor(minor);
  set_server_version_major(major);
  set_server_provider_name(provider_name);
}

cpad::insns::VersionResponseHelper::VersionResponseHelper(const char *buffer)
  : ::cpad::insns::VersionResponse()
{
  ParseFromString(std::string(buffer));
}

cpad::insns::VersionResponseHelper::~VersionResponseHelper()
{
}

cpad::insns::VersionResponseHelper::VersionResponseHelper(VersionResponseHelper const&a_copy)
  : ::cpad::insns::VersionResponseHelper(a_copy.server_version_minor(),
                                  a_copy.server_version_major(),
                                  a_copy.server_provider_name())
{
}

cpad::insns::VersionResponseHelper&
cpad::insns::VersionResponseHelper::operator =(VersionResponseHelper const&a_copy)
{
  set_server_version_minor(a_copy.server_version_minor());
  set_server_version_major(a_copy.server_version_major());
  set_server_provider_name(a_copy.server_provider_name());
  return *this;
}

size_t
cpad::insns::VersionResponseHelper::serialize(char *buffer)
{
  std::string local_buf;
  SerializeToString(&local_buf);
  local_buf.copy(buffer, local_buf.length());
  return local_buf.length();
}

void
cpad::insns::VersionResponseHelper::dump(std::ostream &osb)
{
  osb << "[VersionResponseHelper]" << std::endl;
  osb << "server minor: " << server_version_minor() << std::endl;
  osb << "server major: " << server_version_major() << std::endl;
  osb << "server provider: " << server_provider_name() << std::endl;
}

