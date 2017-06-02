//
// Copyright 2017, Google Inc.
//

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
  explicit PluginServicesImpl(void)
  {
  }
  
  virtual ~PluginServicesImpl()
  {
  }
  
  virtual ::grpc::Status
    VersionService(::grpc::ServerContext* context,
                   const ::cpad::insns::VersionRequest* request,
                   ::cpad::insns::VersionResponse* response)
  {
    ::cpad::insns::VersionRequestHelper vrh(request);
    vrh.dump();
    
    response->set_server_version_minor(0);
    response->set_server_version_major(1);
    response->set_server_provider_name(std::string("GRPC test server"));
    ::cpad::insns::VersionResponseHelper vresph((const ::cpad::insns::VersionResponse*)response);
    vresph.dump();
    
    return ::Status::OK;
  }
  
  virtual ::grpc::Status
    InsertionPointService(::grpc::ServerContext* context,
                          const ::cpad::insns::InsertionPointRequest* request,
                          ::cpad::insns::InsertionPointResponse* response)
  {
    ::cpad::insns::InsertionPointRequestHelper iph(request);
    iph.dump();
    
    response->set_insert_asm_statement(true);
    response->set_asm_statement(std::string("__asm(Nop; Nop; Nop)"));
    ::cpad::insns::InsertionPointResponseHelper ipresph((const ::cpad::insns::InsertionPointResponse*)response);
    ipresph.dump();
    return ::Status::OK;
  }
  
 private:
  
};

void RunServer(void)
{
  std::string server_address("0.0.0.0:50051");
  PluginServicesImpl *service = new PluginServicesImpl();

  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService((grpc::Service*)service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "!! Server listening on " << server_address << std::endl;
  server->Wait();
}

int main(int argc, char** argv)
{
  RunServer();

  return 0;
}
