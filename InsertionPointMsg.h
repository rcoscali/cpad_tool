//
// Copyright ©2017 NagraFrance
//

#ifndef _INSERTION_POINT_MSH_H_
#define _INSERTION_POINT_MSH_H_

#include <stdint.h>

#include <string>
#include <iostream>

#include "plugin_request.pb.h"

namespace cpad
{
  namespace insns
  {
    //
    // InsertionPoint Management
    //
    class InsertionPointRequestHelper : public ::cpad::insns::InsertionPointRequest
    {
    public:
      InsertionPointRequestHelper(std::string,
                                  std::string,
                                  cpad::insns::InsertionLocation);
      InsertionPointRequestHelper(const char *);
      InsertionPointRequestHelper(const ::cpad::insns::InsertionPointRequest*);
      virtual ~InsertionPointRequestHelper();
      
      InsertionPointRequestHelper(InsertionPointRequestHelper const&);
      InsertionPointRequestHelper& operator =(InsertionPointRequestHelper const&);
      
      size_t serialize(char *);
      void dump(std::ostream &osb = std::cout);
    };
    
    class InsertionPointResponseHelper : public ::cpad::insns::InsertionPointResponse
    {
    public:
      InsertionPointResponseHelper(bool, std::string);
      InsertionPointResponseHelper(const char *);
      InsertionPointResponseHelper(const ::cpad::insns::InsertionPointResponse*);
      virtual ~InsertionPointResponseHelper();
      
      InsertionPointResponseHelper(InsertionPointResponseHelper const&);
      InsertionPointResponseHelper& operator =(InsertionPointResponseHelper const&);
      
      size_t serialize(char *);
      void dump(std::ostream &osb = std::cout);
    };

  } // namespace insns
} // namespace cpad

#endif /* !_INSERTION_POINT_MSH_H_ */
