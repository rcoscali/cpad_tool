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
  // CUnitTerminate Management
  //
  class CUnitTerminateRequestHelper : public ::cpad_protobuf::CUnitTerminateRequest
  {
  public:
    CUnitTerminateRequestHelper(std::string);
    CUnitTerminateRequestHelper(const char *);
    virtual ~CUnitTerminateRequestHelper();

    CUnitTerminateRequestHelper(CUnitTerminateRequestHelper const&);
    CUnitTerminateRequestHelper& operator =(CUnitTerminateRequestHelper const&);

    size_t serialize(char *);
    void dump(void);
  };

  class CUnitTerminateResponseHelper : public ::cpad_protobuf::CUnitTerminateResponse
  {
  public:
    CUnitTerminateResponseHelper(std::string);
    CUnitTerminateResponseHelper(const char *);
    virtual ~CUnitTerminateResponseHelper();

    CUnitTerminateResponseHelper(CUnitTerminateResponseHelper const&);
    CUnitTerminateResponseHelper& operator =(CUnitTerminateResponseHelper const&);

    size_t serialize(char *);
    void dump(void);
  };
    
}
