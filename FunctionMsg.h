//
// Copyright ©2017 NagraFrance
//

#include <stdint.h>

#include <string>
#include <iostream>

#include "cfg_request.pb.h"

namespace cpad::cfg
{
  //
  // Function Management
  //
  class FunctionRequestHelper : public ::cpad::cfg::FunctionRequest
  {
  public:
    FunctionRequestHelper(std::string);
    FunctionRequestHelper(const char *);
    virtual ~FunctionRequestHelper();

    FunctionRequestHelper(FunctionRequestHelper const&);
    FunctionRequestHelper& operator =(FunctionRequestHelper const&);

    size_t serialize(char *);
    void dump(void);
  };

  class FunctionResponseHelper : public ::cpad::cfg::FunctionResponse
  {
  public:
    FunctionResponseHelper(std::string);
    FunctionResponseHelper(const char *);
    virtual ~FunctionResponseHelper();

    FunctionResponseHelper(FunctionResponseHelper const&);
    FunctionResponseHelper& operator =(FunctionResponseHelper const&);

    size_t serialize(char *);
    void dump(void);
  };
    
}
