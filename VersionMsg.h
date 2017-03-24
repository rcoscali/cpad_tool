//
// Copyright ©2017 NagraFrance
//

#include <stdint.h>

#include <string>
#include <iostream>

#include "plugin_request.pb.h"

namespace cpad
{
  //
  // Version Management
  //
  class VersionRequestHelper : public ::cpad_protobuf::VersionRequest
  {
  public:
    VersionRequestHelper(uint32_t, uint32_t, std::string);
    VersionRequestHelper(const char *);
    virtual ~VersionRequestHelper(void);

    VersionRequestHelper(VersionRequestHelper const&);
    VersionRequestHelper& operator =(VersionRequestHelper const&);

    size_t serialize(char *);
    void dump(void);
  };

  class VersionResponseHelper : public ::cpad_protobuf::VersionResponse
  {
  public:
    VersionResponseHelper(uint32_t, uint32_t, std::string);
    VersionResponseHelper(const char *);
    virtual ~VersionResponseHelper(void);

    VersionResponseHelper(VersionResponseHelper const&);
    VersionResponseHelper& operator =(VersionResponseHelper const&);

    size_t serialize(char *);
    void dump(void);
  };
    
}
