//
// Copyright ©2017 NagraFrance
//

#include <stdint.h>

#include <string>
#include <iostream>

#include "cfg_request.pb.h"

namespace cpad
{
  namespace cfg
  {
    //
    // Function Management
    //
    class FunctionRequestHelper : public ::cpad::cfg::FunctionRequest
    {
    public:
      FunctionRequestHelper(std::string);
      FunctionRequestHelper(const char *);
      FunctionRequestHelper(const ::cpad::cfg::FunctionRequest*);
      virtual ~FunctionRequestHelper();

      FunctionRequestHelper(FunctionRequestHelper const&);
      FunctionRequestHelper& operator =(FunctionRequestHelper const&);

      size_t serialize(char *);
      void dump(std::ostream& osb = std::cout);
    };

    class FunctionResponseHelper : public ::cpad::cfg::FunctionResponse
    {
    public:
      FunctionResponseHelper(std::string);
      FunctionResponseHelper(const char *);
      FunctionResponseHelper(::cpad::cfg::FunctionResponse*);
      virtual ~FunctionResponseHelper();

      FunctionResponseHelper(FunctionResponseHelper const&);
      FunctionResponseHelper& operator =(FunctionResponseHelper const&);

      size_t serialize(char *);
      void dump(std::ostream& osb = std::cout);
    };
    
  }
}
