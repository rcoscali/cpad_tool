//
// Copyright 2017 NagraFrance
//

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

static unsigned int verbose_option = 0;
static char *hostname_option = (char *)"localhost";
static unsigned int port_option = 50051;

class BuildMngtServicesClient
{
public:

  BuildMngtServicesClient(std::shared_ptr<Channel> channel)
    : m_stub(BuildMngtServices::NewStub(channel))
  {
  }

  void StartCfgCollectionService()
  {
    ClientContext context;
    StartCfgCollectionRequestHelper sccrh(std::string("gRPC test Client build"),
                                          16,
                                          std::string("<cpad_config></cpad_config>"));
    StartCfgCollectionResponseHelper sccresph(StartCfgCollectionResponse::CPAD_CONFIG_ERROR,
                                              std::string("\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0"));

    std::cout << "---===[> Client send:" << std::endl;
    sccrh.dump();
    
    Status status = m_stub->StartCfgCollectionService(&context,
                                                      (const StartCfgCollectionRequest&)sccrh,
                                                      (StartCfgCollectionResponse*)&sccresph);
    if (!status.ok())
      {
        std::cout << "---EEE* StartCfgCollectionService rpc failed." << std::endl;
      }
    else
      {
        std::cout << "---===[> Server responded:" << std::endl;
        sccresph.dump();
      }
  }

  void EndCfgCollectionService()
  {
    ClientContext context;
    EndCfgCollectionRequestHelper eccrh(std::string("\x6e\x67\x75\x5f\xef\x1b\x46\x98\x87\x5b\x5f\xa8\x6d\x25\x6c\x39"));
    EndCfgCollectionResponseHelper eccresph(EndCfgCollectionResponse::APEX_ALLOCATION_ERROR, std::string(""));

    std::cout << "---===[> Client send:" << std::endl;
    eccrh.dump();
    
    Status status = m_stub->EndCfgCollectionService(&context,
                                                    (const EndCfgCollectionRequest&)eccrh,
                                                    (EndCfgCollectionResponse*)&eccresph);
    if (!status.ok())
      {
        std::cout << "---EEE* EndCfgCollectionService rpc failed." << std::endl;
      }
    else
      {
        std::cout << "---===[> Server responded:" << std::endl;
        eccresph.dump();
      }
  }

  void StartCfgToolingService()
  {
    ClientContext context;
    StartCfgToolingRequestHelper sctrh(std::string("\x72\x35\x59\x6a\x93\x32\x45\x8c\xb1\x56\xd6\xbd\xb6\x73\x65\x5e"));
    StartCfgToolingResponseHelper sctresph;

    std::cout << "---===[> Client send:" << std::endl;
    sctrh.dump();
    
    Status status = m_stub->StartCfgToolingService(&context,
                                                   (const StartCfgToolingRequest&)sctrh,
                                                   (StartCfgToolingResponse*)&sctresph);
    if (!status.ok())
      {
        std::cout << "---EEE* StartCfgToolingService rpc failed." << std::endl;
      }
    else
      {
        std::cout << "---===[> Server responded:" << std::endl;
        sctresph.dump();
      }
  }

  void EndCfgToolingService()
  {
    ClientContext context;
    EndCfgToolingRequestHelper ectrh(std::string("\xb7\x1c\xc0\x17\x06\x47\x47\xf0\xb6\x05\x0e\xb7\xc1\x42\x6c\xf1"));
    EndCfgToolingResponseHelper ectresph("");

    std::cout << "---===[> Client send:" << std::endl;
    ectrh.dump();
    
    Status status = m_stub->EndCfgToolingService(&context,
                                                 (const EndCfgToolingRequest&)ectrh,
                                                 (EndCfgToolingResponse*)&ectresph);
    if (!status.ok())
      {
        std::cout << "---EEE* EndCfgToolingService rpc failed." << std::endl;
      }
    else
      {
        std::cout << "---===[> Server responded:" << std::endl;
        ectresph.dump();
      }
  }

private:
  std::unique_ptr<BuildMngtServices::Stub> m_stub;
  
};

int
main(int argc, char** argv)
{
  // Check PB compat
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  // Declare the supported options.
  po::options_description desc("Options allowed for test gRPC BuildMngtServices client.");  
  desc.add_options()
    ("help,h", "Produce help message.")
    ("verbose,v", po::value<unsigned int>(&verbose_option)->default_value(0)->implicit_value(1), "Set verbosity level.")
    ("hostname", po::value<std::string>()->default_value("localhost"), "Set server hostname. Default: localhost.")
    ("port,p", po::value<unsigned int>(&port_option)->default_value(50051), "Set server port. Default: 50051.")
    ;
  po::positional_options_description pdesc;
  pdesc.add("hostname", 1);

  po::variables_map vm;
  
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  if (vm.count("help"))
    {
      std::cout << desc << std::endl;
    }
  else
    {
      if (vm.count("hostname"))
        hostname_option = (char *)vm["hostname"].as<std::string>().c_str();

      if (vm.count("port"))
        port_option = vm["port"].as<unsigned int>();
      
      if (verbose_option)
        {
          std::cout << "**> Verbosity set to level " << (unsigned int)verbose_option << std::endl;
          if (vm.count("hostname"))
            std::cout << "**> Hostname set to '" << vm["hostname"].as<std::string>() << "'" << std::endl;
          if (vm.count("port"))
            std::cout << "**> Port set to " << vm["port"].as<unsigned int>() << std::endl;
        }

      std::ostringstream server_os;
      server_os << hostname_option << ":" << port_option;
      std::string server_address_str = server_os.str();

      if (verbose_option)
        std::cout << "**> Connecting to server on '" << server_address_str << "'" << std::endl;


      BuildMngtServicesClient client(::grpc::CreateChannel(server_address_str,
                                                           grpc::InsecureChannelCredentials()));

      std::cout << "**[ StartCfgCollectionService RPC test:" << std::endl;
      client.StartCfgCollectionService();

      std::cout << "**[EndCfgCollectionService  RPC test:" << std::endl;
      client.EndCfgCollectionService();

      std::cout << "**[ StartCfgToolingService RPC test:" << std::endl;
      client.StartCfgToolingService();

      std::cout << "**[ EndCfgToolingService RPC test:" << std::endl;
      client.EndCfgToolingService();

    }
  
  return 0;
}
