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
  // BasicBlock Management
  //
  class BasicBlockRequestHelper : public ::cpad::cfg::BasicBlockRequest
  {
  public:
    BasicBlockRequestHelper(std::string);
    BasicBlockRequestHelper(const char *);
    virtual ~BasicBlockRequestHelper();

    BasicBlockRequestHelper(BasicBlockRequestHelper const&);
    BasicBlockRequestHelper& operator =(BasicBlockRequestHelper const&);

    size_t serialize(char *);
    void dump(void);
  };

  class BasicBlockResponseHelper : public ::cpad::cfg::BasicBlockResponse
  {
  public:
    BasicBlockResponseHelper(std::string);
    BasicBlockResponseHelper(const char *);
    virtual ~BasicBlockResponseHelper();

    BasicBlockResponseHelper(BasicBlockResponseHelper const&);
    BasicBlockResponseHelper& operator =(BasicBlockResponseHelper const&);

    size_t serialize(char *);
    void dump(void);
  };
    
}
