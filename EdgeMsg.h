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
  // Edge Management
  //
  class EdgeRequestHelper : public ::cpad::cfg::EdgeRequest
  {
  public:
    EdgeRequestHelper(std::string);
    EdgeRequestHelper(const char *);
    virtual ~EdgeRequestHelper();

    EdgeRequestHelper(EdgeRequestHelper const&);
    EdgeRequestHelper& operator =(EdgeRequestHelper const&);

    size_t serialize(char *);
    void dump(void);
  };

  class EdgeResponseHelper : public ::cpad::cfg::EdgeResponse
  {
  public:
    EdgeResponseHelper(std::string);
    EdgeResponseHelper(const char *);
    virtual ~EdgeResponseHelper();

    EdgeResponseHelper(EdgeResponseHelper const&);
    EdgeResponseHelper& operator =(EdgeResponseHelper const&);

    size_t serialize(char *);
    void dump(void);
  };
    
}
