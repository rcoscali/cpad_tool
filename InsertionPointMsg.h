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
  // InsertionPoint Management
  //
  class InsertionPointRequestHelper : public ::cpad_protobuf::InsertionPointRequest
  {
  public:
    InsertionPointRequestHelper(std::string,
                                std::string,
                                cpad_protobuf::InsertionLocation);
    InsertionPointRequestHelper(const char *);
    virtual ~InsertionPointRequestHelper();

    InsertionPointRequestHelper(InsertionPointRequestHelper const&);
    InsertionPointRequestHelper& operator =(InsertionPointRequestHelper const&);

    size_t serialize(char *);
    void dump(void);
  };

  class InsertionPointResponseHelper : public ::cpad_protobuf::InsertionPointResponse
  {
  public:
    InsertionPointResponseHelper(bool, std::string);
    InsertionPointResponseHelper(const char *);
    virtual ~InsertionPointResponseHelper();

    InsertionPointResponseHelper(InsertionPointResponseHelper const&);
    InsertionPointResponseHelper& operator =(InsertionPointResponseHelper const&);
    
    size_t serialize(char *);
    void dump(void);
  };
    
}
