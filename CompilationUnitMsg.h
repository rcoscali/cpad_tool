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
    // CompilationUnitStart Management
    //
    class CompilationUnitStartRequestHelper : public ::cpad::cfg::CompilationUnitStartRequest
    {
    public:
      CompilationUnitStartRequestHelper(std::string);
      CompilationUnitStartRequestHelper(const char *);
      virtual ~CompilationUnitStartRequestHelper();
      
      CompilationUnitStartRequestHelper(CompilationUnitStartRequestHelper const&);
      CompilationUnitStartRequestHelper& operator =(CompilationUnitStartRequestHelper const&);
      
      size_t serialize(char *);
      void dump(std::ostream& osb = std::cout);
    };
    
    class CompilationUnitStartResponseHelper : public ::cpad::cfg::CompilationUnitStartResponse
    {
    public:
      CompilationUnitStartResponseHelper();
      CompilationUnitStartResponseHelper(const char *);
      virtual ~CompilationUnitStartResponseHelper();
      
      CompilationUnitStartResponseHelper(CompilationUnitStartResponseHelper const&);
      CompilationUnitStartResponseHelper& operator =(CompilationUnitStartResponseHelper const&);
      
      size_t serialize(char *);
      void dump(std::ostream& osb = std::cout);
    };
    
    //
    // CompilationUnitEnd Management
    //
    class CompilationUnitEndRequestHelper : public ::cpad::cfg::CompilationUnitEndRequest
    {
    public:
      CompilationUnitEndRequestHelper();
      CompilationUnitEndRequestHelper(const char *);
      virtual ~CompilationUnitEndRequestHelper();
      
      CompilationUnitEndRequestHelper(CompilationUnitEndRequestHelper const&);
      CompilationUnitEndRequestHelper& operator =(CompilationUnitEndRequestHelper const&);
      
      size_t serialize(char *);
      void dump(std::ostream& osb = std::cout);
    };
    
    class CompilationUnitEndResponseHelper : public ::cpad::cfg::CompilationUnitEndResponse
    {
    public:
      CompilationUnitEndResponseHelper();
      CompilationUnitEndResponseHelper(const char *);
      virtual ~CompilationUnitEndResponseHelper();
      
      CompilationUnitEndResponseHelper(CompilationUnitEndResponseHelper const&);
      CompilationUnitEndResponseHelper& operator =(CompilationUnitEndResponseHelper const&);
      
      size_t serialize(char *);
      void dump(std::ostream& osb = std::cout);
    };

  }
}
