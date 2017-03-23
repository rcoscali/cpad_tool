//
// Copyright ©2017 NagraFrance
//

#include "plugin_request.pb.h"

namespace cpad
{
  class VersionRequestHelper : public ::cpad_protobuf::VersionRequest
  {
  public:
    VersionRequestHelper(uint32_t minor, uint32_t major, std::string provider_name);
    virtual ~VersionRequestHelper();

    VersionRequestHelper(VersionRequestHelper const&);
    VersionRequestHelper& operator =(VersionRequestHelper const&);
  }

  class VersionResponseHelper : public ::cpad_protobuf::VersionResponse
  {
  public:
    VersionResponseHelper(uint32_t minor, uint32_t major, std::string provider_name);
    virtual ~VersionResponseHelper();

    VersionResponseHelper(VersionResponseHelper const&);
    VersionResponseHelper& operator =(VersionResponseHelper const&);
  }
    
