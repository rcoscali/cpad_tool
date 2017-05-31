//
// Copyright ©2017 NagraFrance
//

#ifndef __VERSION_MSG_H__
#define __VERSION_MSG_H__

#include <stdint.h>

#include <string>

#include "plugin_request.pb.h"

namespace cpad
{
  namespace insns
  {
    //
    // Version Management
    //
    class VersionRequestHelper : public ::cpad::insns::VersionRequest
    {
    public:
      VersionRequestHelper(uint32_t, uint32_t, std::string);
      VersionRequestHelper(const char *);
      virtual ~VersionRequestHelper(void);
      
      VersionRequestHelper(VersionRequestHelper const&);
      VersionRequestHelper& operator =(VersionRequestHelper const&);
      
      size_t serialize(char *);
      void dump(std::ostream &osb = std::cout);
    };
    
    class VersionResponseHelper : public ::cpad::insns::VersionResponse
    {
    public:
      VersionResponseHelper(uint32_t, uint32_t, std::string);
      VersionResponseHelper(const char *);
      virtual ~VersionResponseHelper(void);
      
      VersionResponseHelper(VersionResponseHelper const&);
      VersionResponseHelper& operator =(VersionResponseHelper const&);
      
      size_t serialize(char *);
      void dump(std::ostream &osb = std::cout);
    };
    
  }
}

#endif /* __VERSION_MSG_H__ */
