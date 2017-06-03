//
// Copyright 2017, Google Inc.
//
#include <iostream>
#include <sstream>

#include <boost/program_options.hpp>

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

namespace po = boost::program_options;

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

static unsigned int verbose_option = 0;
static char *hostname_option = (char *)"localhost";
static unsigned int port_option = 50051;

class CfgCollectionServicesImpl final : public CfgCollectionServices::Service
{
 public:
  explicit CfgCollectionServicesImpl(void)
  {
  }
  
  virtual ~CfgCollectionServicesImpl()
  {
  }
  
  virtual ::grpc::Status
    CompilationUnitStartService(::grpc::ServerContext* context,
                                const CompilationUnitStartRequest* request,
                                CompilationUnitStartResponse* response)
  {
    std::cout << "---===[> Client sent:" << std::endl;
    CompilationUnitStartRequestHelper cusrh(request);
    cusrh.dump();
    
    std::cout << "---===[> Server respond:" << std::endl;
    CompilationUnitStartResponseHelper cusresph((const CompilationUnitStartResponse*)response);
    cusresph.dump();
    
    return ::Status::OK;
  }
  
  virtual ::grpc::Status
    CompilationUnitEndService(::grpc::ServerContext* context,
                              const CompilationUnitEndRequest* request,
                              CompilationUnitEndResponse* response)
  {
    std::cout << "---===[> Client sent:" << std::endl;
    CompilationUnitEndRequestHelper cuerh(request);
    cuerh.dump();
    
    std::cout << "---===[> Server respond:" << std::endl;
    CompilationUnitEndResponseHelper cueresph((const CompilationUnitEndResponse*)response);
    cueresph.dump();
    return ::Status::OK;
  }
  
  virtual ::grpc::Status
    FunctionService(::grpc::ServerContext* context,
                    const FunctionRequest* request,
                    FunctionResponse* response)
  {
    std::cout << "---===[> Client sent:" << std::endl;
    FunctionRequestHelper frh(request);
    frh.dump();
    
    std::cout << "---===[> Server respond:" << std::endl;
    FunctionResponseHelper fresph((const FunctionResponse*)response);
    fresph.dump();
    return ::Status::OK;
  }
  
  virtual ::grpc::Status
    BasicBlockService(::grpc::ServerContext* context,
                      const BasicBlockRequest* request,
                      BasicBlockResponse* response)
  {
    std::cout << "---===[> Client sent:" << std::endl;
    BasicBlockRequestHelper bbrh(request);
    bbrh.dump();
    
    std::cout << "---===[> Server respond:" << std::endl;
    BasicBlockResponseHelper bbresph((const BasicBlockResponse*)response);
    bbresph.dump();
    return ::Status::OK;
  }
  
  virtual ::grpc::Status
    EdgeService(::grpc::ServerContext* context,
                const EdgeRequest* request,
                EdgeResponse* response)
  {
    std::cout << "---===[> Client sent:" << std::endl;
    EdgeRequestHelper erh(request);
    erh.dump();
    
    std::cout << "---===[> Server respond:" << std::endl;
    EdgeResponseHelper eresph((const EdgeResponse*)response);
    eresph.dump();
    return ::Status::OK;
  }
  
 private:
  
};

void RunServer(std::string server_address)
{
  CfgCollectionServicesImpl *service = new CfgCollectionServicesImpl();

  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService((grpc::Service*)service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "!! Server listening on " << server_address << std::endl;
  server->Wait();
}

int main(int argc, char** argv)
{
  // Check PB compat
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  // Declare the supported options.
  po::options_description desc("Options allowed for test gRPC CfgCollectionServices server.");
  desc.add_options()
    ("help,h", "Produce help message.")
    ("verbose,v", po::value<unsigned int>(&verbose_option)->default_value(0)->implicit_value(1), "Set verbosity level.")
    ("hostname", po::value<std::string>()->default_value("localhost"), "Set server hostname. Default: localhost.")
    ("port,p", po::value<unsigned int>(&port_option)->default_value(50051), "Set server port. Default: 50051.")
    ;

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
        std::cout << "**> Running server on '" << server_address_str << "'" << std::endl;

      RunServer(server_address_str);
    }

  return 0;
}

