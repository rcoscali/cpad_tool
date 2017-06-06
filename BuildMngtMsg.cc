//
// Copyright ©2017 NagraFrance
//

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
//#include <boost/uuid/string_generator.hpp>

#include "BuildMngtMsg.h"

cpad::build_mngt::StartCfgCollectionRequestHelper::StartCfgCollectionRequestHelper(std::string build_name,
                                                                                   uint32_t number_cunits,
                                                                                   std::string cpad_config)
  : ::cpad::build_mngt::StartCfgCollectionRequest()
{
  set_build_name(build_name);
  set_number_cunits(number_cunits);
  set_cpad_config(cpad_config);
}

cpad::build_mngt::StartCfgCollectionRequestHelper::StartCfgCollectionRequestHelper(const char *buffer)
  : ::cpad::build_mngt::StartCfgCollectionRequest()
{
  ParseFromString(std::string(buffer));
}

cpad::build_mngt::StartCfgCollectionRequestHelper::StartCfgCollectionRequestHelper(const ::cpad::build_mngt::StartCfgCollectionRequest *request)
  : ::cpad::build_mngt::StartCfgCollectionRequest(*request)
{
}

cpad::build_mngt::StartCfgCollectionRequestHelper::~StartCfgCollectionRequestHelper()
{
}

cpad::build_mngt::StartCfgCollectionRequestHelper::StartCfgCollectionRequestHelper(StartCfgCollectionRequestHelper const&a_copy)
  : ::cpad::build_mngt::StartCfgCollectionRequestHelper(a_copy.build_name(),
                                                        a_copy.number_cunits(),
                                                        a_copy.cpad_config())
{
}

cpad::build_mngt::StartCfgCollectionRequestHelper&
cpad::build_mngt::StartCfgCollectionRequestHelper::operator =(StartCfgCollectionRequestHelper const&a_copy)
{
  set_build_name(a_copy.build_name());
  set_number_cunits(a_copy.number_cunits());
  set_cpad_config(a_copy.cpad_config());
  return *this;
}

size_t
cpad::build_mngt::StartCfgCollectionRequestHelper::serialize(char *buffer)
{
  std::string local_buf;
  SerializeToString(&local_buf);
  local_buf.copy(buffer, local_buf.length());
  return local_buf.length();
}

void
cpad::build_mngt::StartCfgCollectionRequestHelper::dump(std::ostream &osb)
{
  osb << "[StartCfgCollectionRequest]" << std::endl;
  osb << "build name: " << build_name() << std::endl;
  osb << "number cunits: " << number_cunits() << std::endl;
  osb << "cpad_config: " << cpad_config() << std::endl;
}

cpad::build_mngt::StartCfgCollectionResponseHelper::StartCfgCollectionResponseHelper(::cpad::build_mngt::StartCfgCollectionResponse_CpadConfigStatus cpad_config_status,
                                                                                     std::string uuid)
  : ::cpad::build_mngt::StartCfgCollectionResponse()
{
  set_cpad_config_status(cpad_config_status);
  set_uuid(uuid);
}

cpad::build_mngt::StartCfgCollectionResponseHelper::StartCfgCollectionResponseHelper(const char *buffer)
  : ::cpad::build_mngt::StartCfgCollectionResponse()
{
  ParseFromString(std::string(buffer));
}

cpad::build_mngt::StartCfgCollectionResponseHelper::StartCfgCollectionResponseHelper(const ::cpad::build_mngt::StartCfgCollectionResponse *response)
  : ::cpad::build_mngt::StartCfgCollectionResponse(*response)
{
}

cpad::build_mngt::StartCfgCollectionResponseHelper::~StartCfgCollectionResponseHelper()
{
}

cpad::build_mngt::StartCfgCollectionResponseHelper::StartCfgCollectionResponseHelper(StartCfgCollectionResponseHelper const&a_copy)
  : ::cpad::build_mngt::StartCfgCollectionResponseHelper(a_copy.cpad_config_status(),
                                                         a_copy.uuid())
{
}

cpad::build_mngt::StartCfgCollectionResponseHelper&
cpad::build_mngt::StartCfgCollectionResponseHelper::operator =(StartCfgCollectionResponseHelper const&a_copy)
{
  set_cpad_config_status(a_copy.cpad_config_status());
  set_uuid(a_copy.uuid());
  return *this;
}

size_t
cpad::build_mngt::StartCfgCollectionResponseHelper::serialize(char *buffer)
{
  std::string local_buf;
  SerializeToString(&local_buf);
  local_buf.copy(buffer, local_buf.length());
  return local_buf.length();
}

void
cpad::build_mngt::StartCfgCollectionResponseHelper::dump(std::ostream &osb)
{
  boost::uuids::uuid u;
  std::copy(uuid().begin(), uuid().end(), u.begin());
  
  osb << "[StartCfgCollectionResponse]" << std::endl;
  osb << "cpad config status: " << cpad_config_status() << std::endl;
  osb << "uuid: " << u << std::endl;
}

cpad::build_mngt::EndCfgCollectionRequestHelper::EndCfgCollectionRequestHelper(std::string uuid)
  : ::cpad::build_mngt::EndCfgCollectionRequest()
{
  set_uuid(uuid);
}

cpad::build_mngt::EndCfgCollectionRequestHelper::EndCfgCollectionRequestHelper(const char *buffer)
  : ::cpad::build_mngt::EndCfgCollectionRequest()
{
  ParseFromString(std::string(buffer));
}

cpad::build_mngt::EndCfgCollectionRequestHelper::EndCfgCollectionRequestHelper(const ::cpad::build_mngt::EndCfgCollectionRequest *request)
  : ::cpad::build_mngt::EndCfgCollectionRequest(*request)
{
}

cpad::build_mngt::EndCfgCollectionRequestHelper::~EndCfgCollectionRequestHelper()
{
}

cpad::build_mngt::EndCfgCollectionRequestHelper::EndCfgCollectionRequestHelper(EndCfgCollectionRequestHelper const&a_copy)
  : ::cpad::build_mngt::EndCfgCollectionRequestHelper(a_copy.uuid())
{
}

cpad::build_mngt::EndCfgCollectionRequestHelper&
cpad::build_mngt::EndCfgCollectionRequestHelper::operator =(EndCfgCollectionRequestHelper const&a_copy)
{
  set_uuid(a_copy.uuid());
  return *this;
}

size_t
cpad::build_mngt::EndCfgCollectionRequestHelper::serialize(char *buffer)
{
  std::string local_buf;
  SerializeToString(&local_buf);
  local_buf.copy(buffer, local_buf.length());
  return local_buf.length();
}

void
cpad::build_mngt::EndCfgCollectionRequestHelper::dump(std::ostream &osb)
{
  boost::uuids::uuid u;
  std::copy(uuid().begin(), uuid().end(), u.begin());

  osb << "[EndCfgCollectionRequest]" << std::endl;
  osb << "uuid: " << u << std::endl;
}

cpad::build_mngt::EndCfgCollectionResponseHelper::EndCfgCollectionResponseHelper(::cpad::build_mngt::EndCfgCollectionResponse_ApexAllocationStatus apex_allocation_status,
                                                                                 std::string apex_allocation_message)
  : ::cpad::build_mngt::EndCfgCollectionResponse()
{
  set_apex_allocation_status(apex_allocation_status);
  set_apex_allocation_message(apex_allocation_message);
}

cpad::build_mngt::EndCfgCollectionResponseHelper::EndCfgCollectionResponseHelper(const char *buffer)
  : ::cpad::build_mngt::EndCfgCollectionResponse()
{
  ParseFromString(std::string(buffer));
}

cpad::build_mngt::EndCfgCollectionResponseHelper::EndCfgCollectionResponseHelper(const ::cpad::build_mngt::EndCfgCollectionResponse *response)
  : ::cpad::build_mngt::EndCfgCollectionResponse(*response)
{
}

cpad::build_mngt::EndCfgCollectionResponseHelper::~EndCfgCollectionResponseHelper()
{
}

cpad::build_mngt::EndCfgCollectionResponseHelper::EndCfgCollectionResponseHelper(EndCfgCollectionResponseHelper const&a_copy)
  : ::cpad::build_mngt::EndCfgCollectionResponseHelper(a_copy.apex_allocation_status(),
                                                       a_copy.apex_allocation_message())
{
}

cpad::build_mngt::EndCfgCollectionResponseHelper&
cpad::build_mngt::EndCfgCollectionResponseHelper::operator =(EndCfgCollectionResponseHelper const&a_copy)
{
  set_apex_allocation_status(a_copy.apex_allocation_status());
  set_apex_allocation_message(a_copy.apex_allocation_message());
  return *this;
}

size_t
cpad::build_mngt::EndCfgCollectionResponseHelper::serialize(char *buffer)
{
  std::string local_buf;
  SerializeToString(&local_buf);
  local_buf.copy(buffer, local_buf.length());
  return local_buf.length();
}

void
cpad::build_mngt::EndCfgCollectionResponseHelper::dump(std::ostream &osb)
{
  osb << "[EndCfgCollectionResponse]" << std::endl;
  osb << "apex allocation status: " << apex_allocation_status() << std::endl;
  osb << "apex allocation message: " << apex_allocation_message() << std::endl;
}

cpad::build_mngt::StartCfgToolingRequestHelper::StartCfgToolingRequestHelper(std::string uuid)
  : ::cpad::build_mngt::StartCfgToolingRequest()
{
  set_uuid(uuid);
}

cpad::build_mngt::StartCfgToolingRequestHelper::StartCfgToolingRequestHelper(const char *buffer)
  : ::cpad::build_mngt::StartCfgToolingRequest()
{
  ParseFromString(std::string(buffer));
}

cpad::build_mngt::StartCfgToolingRequestHelper::StartCfgToolingRequestHelper(const ::cpad::build_mngt::StartCfgToolingRequest *request)
  : ::cpad::build_mngt::StartCfgToolingRequest(*request)
{
}

cpad::build_mngt::StartCfgToolingRequestHelper::~StartCfgToolingRequestHelper()
{
}

cpad::build_mngt::StartCfgToolingRequestHelper::StartCfgToolingRequestHelper(StartCfgToolingRequestHelper const&a_copy)
  : ::cpad::build_mngt::StartCfgToolingRequestHelper(a_copy.uuid())
{
}

cpad::build_mngt::StartCfgToolingRequestHelper&
cpad::build_mngt::StartCfgToolingRequestHelper::operator =(StartCfgToolingRequestHelper const&a_copy)
{
  set_uuid(a_copy.uuid());
  return *this;
}

size_t
cpad::build_mngt::StartCfgToolingRequestHelper::serialize(char *buffer)
{
  std::string local_buf;
  SerializeToString(&local_buf);
  local_buf.copy(buffer, local_buf.length());
  return local_buf.length();
}

void
cpad::build_mngt::StartCfgToolingRequestHelper::dump(std::ostream &osb)
{
  boost::uuids::uuid u;
  std::copy(uuid().begin(), uuid().end(), u.begin());

  osb << "[StartCfgToolingRequest]" << std::endl;
  osb << "uuid: " << u << std::endl;
}

cpad::build_mngt::StartCfgToolingResponseHelper::StartCfgToolingResponseHelper()
  : ::cpad::build_mngt::StartCfgToolingResponse()
{
}

cpad::build_mngt::StartCfgToolingResponseHelper::StartCfgToolingResponseHelper(const char *buffer)
  : ::cpad::build_mngt::StartCfgToolingResponse()
{
  ParseFromString(std::string(buffer));
}

cpad::build_mngt::StartCfgToolingResponseHelper::StartCfgToolingResponseHelper(const ::cpad::build_mngt::StartCfgToolingResponse *response)
  : ::cpad::build_mngt::StartCfgToolingResponse(*response)
{
}

cpad::build_mngt::StartCfgToolingResponseHelper::~StartCfgToolingResponseHelper()
{
}

cpad::build_mngt::StartCfgToolingResponseHelper::StartCfgToolingResponseHelper(StartCfgToolingResponseHelper const&a_copy)
  : ::cpad::build_mngt::StartCfgToolingResponseHelper()
{
}

cpad::build_mngt::StartCfgToolingResponseHelper&
cpad::build_mngt::StartCfgToolingResponseHelper::operator =(StartCfgToolingResponseHelper const&a_copy)
{
  return *this;
}

size_t
cpad::build_mngt::StartCfgToolingResponseHelper::serialize(char *buffer)
{
  std::string local_buf;
  SerializeToString(&local_buf);
  local_buf.copy(buffer, local_buf.length());
  return local_buf.length();
}

void
cpad::build_mngt::StartCfgToolingResponseHelper::dump(std::ostream &osb)
{
  osb << "[StartCfgToolingResponse]" << std::endl;
}

cpad::build_mngt::EndCfgToolingRequestHelper::EndCfgToolingRequestHelper(std::string uuid)
  : ::cpad::build_mngt::EndCfgToolingRequest()
{
  set_uuid(uuid);
}

cpad::build_mngt::EndCfgToolingRequestHelper::EndCfgToolingRequestHelper(const char *buffer)
  : ::cpad::build_mngt::EndCfgToolingRequest()
{
  ParseFromString(std::string(buffer));
}

cpad::build_mngt::EndCfgToolingRequestHelper::EndCfgToolingRequestHelper(const ::cpad::build_mngt::EndCfgToolingRequest *request)
  : ::cpad::build_mngt::EndCfgToolingRequest(*request)
{
}

cpad::build_mngt::EndCfgToolingRequestHelper::~EndCfgToolingRequestHelper()
{
}

cpad::build_mngt::EndCfgToolingRequestHelper::EndCfgToolingRequestHelper(EndCfgToolingRequestHelper const&a_copy)
  : ::cpad::build_mngt::EndCfgToolingRequestHelper(a_copy.uuid())
{
}

cpad::build_mngt::EndCfgToolingRequestHelper&
cpad::build_mngt::EndCfgToolingRequestHelper::operator =(EndCfgToolingRequestHelper const&a_copy)
{
  set_uuid(a_copy.uuid());
  return *this;
}

size_t
cpad::build_mngt::EndCfgToolingRequestHelper::serialize(char *buffer)
{
  std::string local_buf;
  SerializeToString(&local_buf);
  local_buf.copy(buffer, local_buf.length());
  return local_buf.length();
}

void
cpad::build_mngt::EndCfgToolingRequestHelper::dump(std::ostream &osb)
{
  boost::uuids::uuid u;
  std::copy(uuid().begin(), uuid().end(), u.begin());

  osb << "[EndCfgToolingRequest]" << std::endl;
  osb << "uuid: " << u << std::endl;
}

cpad::build_mngt::EndCfgToolingResponseHelper::EndCfgToolingResponseHelper(::google::protobuf::Map< ::std::string, ::cpad::build_mngt::EndCfgToolingResponse_BbStat> const& statistics)
  : ::cpad::build_mngt::EndCfgToolingResponse()
{
  mutable_statistics()->insert(statistics.cbegin(), statistics.cend());
}

cpad::build_mngt::EndCfgToolingResponseHelper::EndCfgToolingResponseHelper(const char *buffer)
  : ::cpad::build_mngt::EndCfgToolingResponse()
{
  ParseFromString(std::string(buffer));
}

cpad::build_mngt::EndCfgToolingResponseHelper::EndCfgToolingResponseHelper(const ::cpad::build_mngt::EndCfgToolingResponse *response)
  : ::cpad::build_mngt::EndCfgToolingResponse(*response)
{
}

cpad::build_mngt::EndCfgToolingResponseHelper::~EndCfgToolingResponseHelper()
{
}

cpad::build_mngt::EndCfgToolingResponseHelper::EndCfgToolingResponseHelper(EndCfgToolingResponseHelper const&a_copy)
  : ::cpad::build_mngt::EndCfgToolingResponseHelper(a_copy.statistics())
{
}

cpad::build_mngt::EndCfgToolingResponseHelper&
cpad::build_mngt::EndCfgToolingResponseHelper::operator =(EndCfgToolingResponseHelper const&a_copy)
{
  mutable_statistics()->insert(a_copy.statistics().cbegin(), a_copy.statistics().cend());
  return *this;
}

size_t
cpad::build_mngt::EndCfgToolingResponseHelper::serialize(char *buffer)
{
  std::string local_buf;
  SerializeToString(&local_buf);
  local_buf.copy(buffer, local_buf.length());
  return local_buf.length();
}

void
cpad::build_mngt::EndCfgToolingResponseHelper::dump(std::ostream &osb)
{
  auto stats = statistics();
  std::map<std::string, ::cpad::build_mngt::EndCfgToolingResponse_BbStat> ordered_map(stats.begin(), stats.end());
  osb << "[EndCfgToolingResponse]" << std::endl;
  for (const auto stat : ordered_map)
    {
      const auto bb_stat = stat.second;
      osb << "statistics for BB '" << stat.first << "' is: " << std::endl;
      osb << "   original length: " << bb_stat.bb_original_length() << std::endl;
      osb << "   modified length: " << bb_stat.bb_modified_length() << std::endl;
    }
}

