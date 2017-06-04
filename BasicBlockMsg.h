//
// Copyright ©2017 NagraFrance
//

#ifndef _BASIC_BLOCK_MSG_H_
#define _BASIC_BLOCK_MSG_H_

#include <stdint.h>

#include <string>
#include <iostream>

#include "cfg_request.pb.h"

namespace cpad
{
  namespace cfg
  {
    //
    // BasicBlock Management
    //
    class BasicBlockRequestHelper : public ::cpad::cfg::BasicBlockRequest
    {
    public:
      BasicBlockRequestHelper(std::string, std::string, std::string);
      BasicBlockRequestHelper(const char *);
      BasicBlockRequestHelper(const ::cpad::cfg::BasicBlockRequest*);
      virtual ~BasicBlockRequestHelper();

      BasicBlockRequestHelper(BasicBlockRequestHelper const&);
      BasicBlockRequestHelper& operator =(BasicBlockRequestHelper const&);

      size_t serialize(char *);
      void dump(std::ostream& osb = std::cout);
    };

    class BasicBlockResponseHelper : public ::cpad::cfg::BasicBlockResponse
    {
    public:
      BasicBlockResponseHelper();
      BasicBlockResponseHelper(const char *);
      BasicBlockResponseHelper(const ::cpad::cfg::BasicBlockResponse*);
      virtual ~BasicBlockResponseHelper();

      BasicBlockResponseHelper(BasicBlockResponseHelper const&);
      BasicBlockResponseHelper& operator =(BasicBlockResponseHelper const&);

      size_t serialize(char *);
      void dump(std::ostream& osb = std::cout);
    };
    
  }
}

#endif /* !_BASIC_BLOCK_MSG_H_ */
