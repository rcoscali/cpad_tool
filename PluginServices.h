//
// Copyright 2017, Google Inc.
//

#ifndef _PLUGIN_SERVICES_H_
#define _PLUGIN_SERVICES_H_

#include <grpc/grpc.h>
#include <grpc++/server.h>
#include <grpc++/server_builder.h>
#include <grpc++/server_context.h>
#include <grpc++/security/server_credentials.h>

#include "VersionMsg.h"
#include "InsertionPointMsg.h"
#include "plugin_request.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;

class PluginServicesImpl final : public ::cpad::insns::PluginServices::Service
{
 public:
  explicit PluginServicesImpl(std::ostream* osb = &std::cout);
  
  virtual ~PluginServicesImpl();
  
  virtual ::grpc::Status
    VersionService(::grpc::ServerContext* context,
                   const ::cpad::insns::VersionRequest* request,
                   ::cpad::insns::VersionResponse* response);
  
  virtual ::grpc::Status
    InsertionPointService(::grpc::ServerContext* context,
                          const ::cpad::insns::InsertionPointRequest* request,
                          ::cpad::insns::InsertionPointResponse* response);
  
 private:
  std::ostream* m_osb;
};

#endif /* _PLUGIN_SERVICES_H_ */
