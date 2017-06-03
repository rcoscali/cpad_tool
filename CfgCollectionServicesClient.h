//
// Copyright 2017 NagraFrance
//

#ifndef _CFG_COLLECTION_SERVICES_CLIENT_H_

#include <grpc/grpc.h>
#include <grpc++/channel.h>
#include <grpc++/client_context.h>
#include <grpc++/create_channel.h>
#include <grpc++/security/credentials.h>

#include "CompilationUnitMsg.h"
#include "FunctionMsg.h"
#include "BasicBlockMsg.h"
#include "EdgeMsg.h"
#include "cfg_request.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
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

class CfgCollectionServicesClient
{
 public:

  CfgCollectionServicesClient(std::shared_ptr<Channel> channel);

  void CompilationUnitStartService(void);
  void CompilationUnitEndService(void);
  void FunctionService(void);
  void BasicBlockService(void);
  void EdgeService(void);


private:
  std::unique_ptr<CfgCollectionServices::Stub> m_stub;
  
};

#endif /* !_CFG_COLLECTION_SERVICES_CLIENT_H_ */
