//
// Copyright ©2017 NagraFrance
//

#include <stdint.h>

#include <string>
#include <iostream>

#include "build_mngt.pb.h"

namespace cpad
{
  //
  // StartCfgCollection Management
  //
  class StartCfgCollectionRequestHelper : public ::cpad::build_mngt::StartCfgCollectionRequest
  {
  public:
    StartCfgCollectionRequestHelper(std::string, uint32_t, std::string);
    StartCfgCollectionRequestHelper(const char *);
    virtual ~StartCfgCollectionRequestHelper(void);

    StartCfgCollectionRequestHelper(StartCfgCollectionRequestHelper const&);
    StartCfgCollectionRequestHelper& operator =(StartCfgCollectionRequestHelper const&);

    size_t serialize(char *);
    void dump(void);
  };

  class StartCfgCollectionResponseHelper : public ::cpad::build_mngt::StartCfgCollectionResponse
  {
  public:
    StartCfgCollectionResponseHelper(bool, std::string);
    StartCfgCollectionResponseHelper(const char *);
    virtual ~StartCfgCollectionResponseHelper(void);

    StartCfgCollectionResponseHelper(StartCfgCollectionResponseHelper const&);
    StartCfgCollectionResponseHelper& operator =(StartCfgCollectionResponseHelper const&);

    size_t serialize(char *);
    void dump(void);
  };
    
  //
  // EndCfgCollection Management
  //
  class EndCfgCollectionRequestHelper : public ::cpad::build_mngt::EndCfgCollectionRequest
  {
  public:
    EndCfgCollectionRequestHelper();
    EndCfgCollectionRequestHelper(const char *);
    virtual ~EndCfgCollectionRequestHelper(void);

    EndCfgCollectionRequestHelper(EndCfgCollectionRequestHelper const&);
    EndCfgCollectionRequestHelper& operator =(EndCfgCollectionRequestHelper const&);

    size_t serialize(char *);
    void dump(void);
  };

  class EndCfgCollectionResponseHelper : public ::cpad::build_mngt::EndCfgCollectionResponse
  {
  public:
    EndCfgCollectionResponseHelper(bool);
    EndCfgCollectionResponseHelper(const char *);
    virtual ~EndCfgCollectionResponseHelper(void);

    EndCfgCollectionResponseHelper(EndCfgCollectionResponseHelper const&);
    EndCfgCollectionResponseHelper& operator =(EndCfgCollectionResponseHelper const&);

    size_t serialize(char *);
    void dump(void);
  };
  
  //
  // StartCfgTooling Management
  //
  class StartCfgToolingRequestHelper : public ::cpad::build_mngt::StartCfgToolingRequest
  {
  public:
    StartCfgToolingRequestHelper();
    StartCfgToolingRequestHelper(const char *);
    virtual ~StartCfgToolingRequestHelper(void);

    StartCfgToolingRequestHelper(StartCfgToolingRequestHelper const&);
    StartCfgToolingRequestHelper& operator =(StartCfgToolingRequestHelper const&);

    size_t serialize(char *);
    void dump(void);
  };

  class StartCfgToolingResponseHelper : public ::cpad::build_mngt::StartCfgToolingResponse
  {
  public:
    StartCfgToolingResponseHelper();
    StartCfgToolingResponseHelper(const char *);
    virtual ~StartCfgToolingResponseHelper(void);

    StartCfgToolingResponseHelper(StartCfgToolingResponseHelper const&);
    StartCfgToolingResponseHelper& operator =(StartCfgToolingResponseHelper const&);

    size_t serialize(char *);
    void dump(void);
  };

  //
  // EndCfgTooling Management
  //
  class EndCfgToolingRequestHelper : public ::cpad::build_mngt::EndCfgToolingRequest
  {
  public:
    EndCfgToolingRequestHelper(uint32_t, uint32_t, std::string);
    EndCfgToolingRequestHelper(const char *);
    virtual ~EndCfgToolingRequestHelper(void);

    EndCfgToolingRequestHelper(EndCfgToolingRequestHelper const&);
    EndCfgToolingRequestHelper& operator =(EndCfgToolingRequestHelper const&);

    size_t serialize(char *);
    void dump(void);
  };

  class EndCfgToolingResponseHelper : public ::cpad::build_mngt::EndCfgToolingResponse
  {
  public:
    EndCfgToolingResponseHelper(uint32_t, uint32_t);
    EndCfgToolingResponseHelper(const char *);
    virtual ~EndCfgToolingResponseHelper(void);

    EndCfgToolingResponseHelper(EndCfgToolingResponseHelper const&);
    EndCfgToolingResponseHelper& operator =(EndCfgToolingResponseHelper const&);

    size_t serialize(char *);
    void dump(void);
  };
}
