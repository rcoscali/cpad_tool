//
// Copyright 2017, Google Inc.
//

#ifndef __CFG_COLLECTION_SERVICES_H_
#define __CFG_COLLECTION_SERVICES_H_

#include <grpc/grpc.h>
#include <grpc++/server.h>
#include <grpc++/server_builder.h>
#include <grpc++/server_context.h>
#include <grpc++/security/server_credentials.h>

#include "CompilationUnitMsg.h"
#include "FunctionMsg.h"
#include "BasicBlockMsg.h"
#include "EdgeMsg.h"
#include "cfg_request.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;

using cpad::cfg::CfgCollectionServices;
using cpad::cfg::CompilationUnitStartRequest;
using cpad::cfg::CompilationUnitStartRequestHelper;
using cpad::cfg::CompilationUnitStartResponse;
using cpad::cfg::CompilationUnitStartResponseHelper;
using cpad::cfg::CompilationUnitEndRequest;
using cpad::cfg::CompilationUnitEndRequestHelper;
using cpad::cfg::CompilationUnitEndResponse;
using cpad::cfg::CompilationUnitEndResponseHelper;
using cpad::cfg::FunctionRequest;
using cpad::cfg::FunctionRequestHelper;
using cpad::cfg::FunctionResponse;
using cpad::cfg::FunctionResponseHelper;
using cpad::cfg::BasicBlockRequest;
using cpad::cfg::BasicBlockRequestHelper;
using cpad::cfg::BasicBlockResponse;
using cpad::cfg::BasicBlockResponseHelper;
using cpad::cfg::EdgeRequest;
using cpad::cfg::EdgeRequestHelper;
using cpad::cfg::EdgeResponse;
using cpad::cfg::EdgeResponseHelper;

class CfgCollectionServicesImpl final : public CfgCollectionServices::Service
{
 public:
  explicit CfgCollectionServicesImpl(std::ostream*);
  
  virtual ~CfgCollectionServicesImpl();
  
  virtual ::grpc::Status
    CompilationUnitStartService(::grpc::ServerContext* context,
                                const CompilationUnitStartRequest* request,
                                CompilationUnitStartResponse* response);
  
  virtual ::grpc::Status
    CompilationUnitEndService(::grpc::ServerContext* context,
                              const CompilationUnitEndRequest* request,
                              CompilationUnitEndResponse* response);
    
  virtual ::grpc::Status
    FunctionService(::grpc::ServerContext* context,
                    const FunctionRequest* request,
                    FunctionResponse* response);
  
  virtual ::grpc::Status
    BasicBlockService(::grpc::ServerContext* context,
                      const BasicBlockRequest* request,
                      BasicBlockResponse* response);
  
  virtual ::grpc::Status
    EdgeService(::grpc::ServerContext* context,
                const EdgeRequest* request,
                EdgeResponse* response);

  
 private:

  std::ostream* m_osb;
};

#endif /* __CFG_COLLECTION_SERVICES_H_ */
