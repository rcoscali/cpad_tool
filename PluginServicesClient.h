//
// Copyright 2017 NagraFrance
//

#ifndef _PLUGIN_SERVICES_CLIENT_H_
#define _PLUGIN_SERVICES_CLIENT_H_

#include <grpc/grpc.h>
#include <grpc++/channel.h>
#include <grpc++/client_context.h>
#include <grpc++/create_channel.h>
#include <grpc++/security/credentials.h>

#include "VersionMsg.h"
#include "InsertionPointMsg.h"
#include "plugin_request.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;

using cpad::insns::PluginServices;
using cpad::insns::VersionRequest;
using cpad::insns::VersionRequestHelper;
using cpad::insns::VersionResponse;
using cpad::insns::VersionResponseHelper;
using cpad::insns::InsertionPointRequest;
using cpad::insns::InsertionPointRequestHelper;
using cpad::insns::InsertionPointResponse;
using cpad::insns::InsertionPointResponseHelper;

class PluginServicesClient
{
public:

  PluginServicesClient(std::shared_ptr<Channel> channel);

  void VersionService(std::ostream& osb = std::cout);
  void InsertionPointService(std::ostream& osb = std::cout);

private:
  std::unique_ptr<PluginServices::Stub> m_stub;
  
};

#endif /* !_PLUGIN_SERVICES_CLIENT_H_ */
