//
// Copyright 2017 NagraFrance
//

#include <iostream>

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

  PluginServicesClient(std::shared_ptr<Channel> channel)
    : m_stub(PluginServices::NewStub(channel))
  {
  }

  void VersionService()
  {
    ClientContext context;
    VersionRequestHelper vrh(0, 1, std::string("gRPC test Client"));
    VersionResponseHelper vresph(0, 0, std::string(""));

    std::cout << "Client send:" << std::endl;
    vrh.dump();
    
    Status status = m_stub->VersionService(&context,
                                           (const VersionRequest&)vrh,
                                           (VersionResponse*)&vresph);
    if (!status.ok())
      {
        std::cout << "VersionService rpc failed." << std::endl;
      }
    else
      {
        std::cout << "Server responded:" << std::endl;
        vresph.dump();
      }
  }

  void InsertionPointService()
  {
    ClientContext context;
    InsertionPointRequestHelper iprh(std::string("foobar.c"),
                                     std::string("foo"),
                                     cpad::insns::FUNCTION_BEFORE_CALL);
    InsertionPointResponseHelper ipresph("");

    std::cout << "Client send:" << std::endl;
    iprh.dump();

    Status status = m_stub->InsertionPointService(&context,
                                                  (const InsertionPointRequest&)iprh,
                                                  (InsertionPointResponse*)&ipresph);
    if (!status.ok())
      {
        std::cout << "InsertionPointService rpc failed." << std::endl;
      }
    else
      {
        std::cout << "Server responded:" << std::endl;
        ipresph.dump();
      }
    
  }

private:
  std::unique_ptr<PluginServices::Stub> m_stub;
  
};

int
main(int argc, char** argv)
{
  PluginServicesClient client(::grpc::CreateChannel("localhost:50051",
                                                    grpc::InsecureChannelCredentials()));

  std::cout << "**[ VersionService RPC test:" << std::endl;
  client.VersionService();
  std::cout << "**[ InsertionPointService RPC test:" << std::endl;
  client.InsertionPointService();
  
  return 0;
}
