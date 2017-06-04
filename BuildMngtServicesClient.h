//
// Copyright 2017 NagraFrance
//

#ifndef _BUILD_MNGT_SERVICES_CLIENT_H_
#define _BUILD_MNGT_SERVICES_CLIENT_H_

#include <iostream>
#include <sstream>

#include <boost/program_options.hpp>

#include <grpc/grpc.h>
#include <grpc++/channel.h>
#include <grpc++/client_context.h>
#include <grpc++/create_channel.h>
#include <grpc++/security/credentials.h>

#include "BuildMngtMsg.h"
#include "build_mngt.grpc.pb.h"

namespace po = boost::program_options;

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
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

class BuildMngtServicesClient
{
public:

  BuildMngtServicesClient(std::shared_ptr<Channel> channel);

  void StartCfgCollectionService(std::ostream& osb = std::cout);
  void EndCfgCollectionService(std::ostream& osb = std::cout);
  void StartCfgToolingService(std::ostream& osb = std::cout);
  void EndCfgToolingService(std::ostream& osb = std::cout);

private:
  std::unique_ptr<BuildMngtServices::Stub> m_stub;
  
};

#endif /* !_BUILD_MNGT_SERVICES_CLIENT_H_ */
