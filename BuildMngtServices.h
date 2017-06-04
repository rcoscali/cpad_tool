//
// Copyright 2017, Google Inc.
//

#ifndef __BUILDMNGT_SERVICES_H_
#define __BUILDMNGT_SERVICES_H_

#include <grpc/grpc.h>
#include <grpc++/server.h>
#include <grpc++/server_builder.h>
#include <grpc++/server_context.h>
#include <grpc++/security/server_credentials.h>

#include "BuildMngtMsg.h"
#include "build_mngt.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;

using cpad::build_mngt::BuildMngtServices;
using cpad::build_mngt::StartCfgCollectionRequest;
using cpad::build_mngt::StartCfgCollectionRequestHelper;
using cpad::build_mngt::StartCfgCollectionResponse;
using cpad::build_mngt::StartCfgCollectionResponseHelper;
using cpad::build_mngt::EndCfgCollectionRequest;
using cpad::build_mngt::EndCfgCollectionRequestHelper;
using cpad::build_mngt::EndCfgCollectionResponse;
using cpad::build_mngt::EndCfgCollectionResponseHelper;
using cpad::build_mngt::StartCfgToolingRequest;
using cpad::build_mngt::StartCfgToolingRequestHelper;
using cpad::build_mngt::StartCfgToolingResponse;
using cpad::build_mngt::StartCfgToolingResponseHelper;
using cpad::build_mngt::EndCfgToolingRequest;
using cpad::build_mngt::EndCfgToolingRequestHelper;
using cpad::build_mngt::EndCfgToolingResponse;
using cpad::build_mngt::EndCfgToolingResponseHelper;

class BuildMngtServicesImpl final : public BuildMngtServices::Service
{
 public:
  explicit BuildMngtServicesImpl(std::ostream*);
  
  virtual ~BuildMngtServicesImpl();
  
  virtual ::grpc::Status StartCfgCollectionService(::grpc::ServerContext* context,
                                                   const StartCfgCollectionRequest* request,
                                                   StartCfgCollectionResponse* response);

  virtual ::grpc::Status EndCfgCollectionService(::grpc::ServerContext* context,
                                                 const EndCfgCollectionRequest* request,
                                                 EndCfgCollectionResponse* response);

  virtual ::grpc::Status StartCfgToolingService(::grpc::ServerContext* context,
                                                const StartCfgToolingRequest* request,
                                                StartCfgToolingResponse* response);

  virtual ::grpc::Status EndCfgToolingService(::grpc::ServerContext* context,
                                              const EndCfgToolingRequest* request,
                                              EndCfgToolingResponse* response);

 private:

  std::ostream* m_osb;
};

#endif
