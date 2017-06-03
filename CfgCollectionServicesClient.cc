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

#include "CompilationUnitMsg.h"
#include "FunctionMsg.h"
#include "BasicBlockMsg.h"
#include "EdgeMsg.h"
#include "cfg_request.grpc.pb.h"

namespace po = boost::program_options;

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

static unsigned int verbose_option = 0;
static char *hostname_option = (char *)"localhost";
static unsigned int port_option = 50051;

class CfgCollectionServicesClient
{
public:

  CfgCollectionServicesClient(std::shared_ptr<Channel> channel)
    : m_stub(CfgCollectionServices::NewStub(channel))
  {
  }

  void CompilationUnitStartService()
  {
    ClientContext context;
    CompilationUnitStartRequestHelper cusrh(std::string("FooBar.cc"));
    CompilationUnitStartResponseHelper cusresph;

    std::cout << "---===[> Client send:" << std::endl;
    cusrh.dump();
    
    Status status = m_stub->CompilationUnitStartService(&context,
                                                        (const CompilationUnitStartRequest&)cusrh,
                                                        (CompilationUnitStartResponse*)&cusresph);
    if (!status.ok())
      {
        std::cout << "---EEE* CompilationUnitStartService rpc failed." << std::endl;
      }
    else
      {
        std::cout << "---===[> Server responded:" << std::endl;
        cusresph.dump();
      }
  }

  void CompilationUnitEndService()
  {
    ClientContext context;
    CompilationUnitEndRequestHelper cuerh;
    CompilationUnitEndResponseHelper cueresph;

    std::cout << "---===[> Client send:" << std::endl;
    cuerh.dump();
    
    Status status = m_stub->CompilationUnitEndService(&context,
                                                      (const CompilationUnitEndRequest&)cuerh,
                                                      (CompilationUnitEndResponse*)&cueresph);
    if (!status.ok())
      {
        std::cout << "---EEE* CompilationUnitEndService rpc failed." << std::endl;
      }
    else
      {
        std::cout << "---===[> Server responded:" << std::endl;
        cueresph.dump();
      }
  }


  void FunctionService()
  {
    ClientContext context;
    FunctionRequestHelper frh(std::string("FooBar.cc"), std::string("Foo"));
    FunctionResponseHelper fresph;

    std::cout << "---===[> Client send:" << std::endl;
    frh.dump();
    
    Status status = m_stub->FunctionService(&context,
                                            (const FunctionRequest&)frh,
                                            (FunctionResponse*)&fresph);
    if (!status.ok())
      {
        std::cout << "---EEE* FunctionService rpc failed." << std::endl;
      }
    else
      {
        std::cout << "---===[> Server responded:" << std::endl;
        fresph.dump();
      }
  }

  void BasicBlockService()
  {
    ClientContext context;
    BasicBlockRequestHelper bbrh(std::string("FooBar.cc"), std::string("Foo"), std::string("BB3"));
    BasicBlockResponseHelper bbresph;

    std::cout << "---===[> Client send:" << std::endl;
    bbrh.dump();
    
    Status status = m_stub->BasicBlockService(&context,
                                              (const BasicBlockRequest&)bbrh,
                                              (BasicBlockResponse*)&bbresph);
    if (!status.ok())
      {
        std::cout << "---EEE* BasicBlockService rpc failed." << std::endl;
      }
    else
      {
        std::cout << "---===[> Server responded:" << std::endl;
        bbresph.dump();
      }
  }

  void EdgeService()
  {
    ClientContext context;
    EdgeRequestHelper erh(std::string("FooBar.cc"), std::string("Foo"), std::string("BB2"),
                          std::string("FooBaz.cc"), std::string("Baz"), std::string("BB5"),
                          cpad::cfg::EDGE_FALLBACK_BRANCH);
    EdgeResponseHelper eresph;

    std::cout << "---===[> Client send:" << std::endl;
    erh.dump();
    
    Status status = m_stub->EdgeService(&context,
                                        (const EdgeRequest&)erh,
                                        (EdgeResponse*)&eresph);
    if (!status.ok())
      {
        std::cout << "---EEE* EdgeService rpc failed." << std::endl;
      }
    else
      {
        std::cout << "---===[> Server responded:" << std::endl;
        eresph.dump();
      }
  }


private:
  std::unique_ptr<CfgCollectionServices::Stub> m_stub;
  
};

int
main(int argc, char** argv)
{
  // Check PB compat
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  // Declare the supported options.
  po::options_description desc("Options allowed for test gRPC CfgCollectionServices client.");  
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


      CfgCollectionServicesClient client(::grpc::CreateChannel(server_address_str,
                                                               grpc::InsecureChannelCredentials()));

      std::cout << "**[ CompilationUnitStartService RPC test:" << std::endl;
      client.CompilationUnitStartService();

      std::cout << "**[ CompilationUnitEndService RPC test:" << std::endl;
      client.CompilationUnitEndService();

      std::cout << "**[ FunctionService RPC test:" << std::endl;
      client.FunctionService();

      std::cout << "**[ BasicBlockService RPC test:" << std::endl;
      client.BasicBlockService();

      std::cout << "**[ EdgeService RPC test:" << std::endl;
      client.EdgeService();

    }
  
  return 0;
}
