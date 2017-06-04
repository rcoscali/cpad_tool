//
// Copyright 2017, Google Inc.
//
#include <iostream>
#include <sstream>

#include "CfgCollectionServices.h"

CfgCollectionServicesImpl::CfgCollectionServicesImpl(std::ostream* osb)
{
  m_osb = osb ? osb : &std::cout;
}
  
CfgCollectionServicesImpl::~CfgCollectionServicesImpl()
{
}
  
::grpc::Status
CfgCollectionServicesImpl::CompilationUnitStartService(::grpc::ServerContext* context,
                                                       const CompilationUnitStartRequest* request,
                                                       CompilationUnitStartResponse* response)
{
  (*m_osb) << "---===[> Client sent:" << std::endl;
  CompilationUnitStartRequestHelper cusrh(request);
  cusrh.dump((*m_osb));
    
  (*m_osb) << "---===[> Server respond:" << std::endl;
  CompilationUnitStartResponseHelper cusresph((const CompilationUnitStartResponse*)response);
  cusresph.dump((*m_osb));
    
  return ::Status::OK;
}
  
::grpc::Status
CfgCollectionServicesImpl::CompilationUnitEndService(::grpc::ServerContext* context,
                                                     const CompilationUnitEndRequest* request,
                                                     CompilationUnitEndResponse* response)
{
  (*m_osb) << "---===[> Client sent:" << std::endl;
  CompilationUnitEndRequestHelper cuerh(request);
  cuerh.dump((*m_osb));
    
  (*m_osb) << "---===[> Server respond:" << std::endl;
  CompilationUnitEndResponseHelper cueresph((const CompilationUnitEndResponse*)response);
  cueresph.dump((*m_osb));
  return ::Status::OK;
}
  
::grpc::Status
CfgCollectionServicesImpl::FunctionService(::grpc::ServerContext* context,
                                           const FunctionRequest* request,
                                           FunctionResponse* response)
{
  (*m_osb) << "---===[> Client sent:" << std::endl;
  FunctionRequestHelper frh(request);
  frh.dump((*m_osb));
    
  (*m_osb) << "---===[> Server respond:" << std::endl;
  FunctionResponseHelper fresph((const FunctionResponse*)response);
  fresph.dump((*m_osb));
  return ::Status::OK;
}
  
::grpc::Status
CfgCollectionServicesImpl::BasicBlockService(::grpc::ServerContext* context,
                                             const BasicBlockRequest* request,
                                             BasicBlockResponse* response)
{
  (*m_osb) << "---===[> Client sent:" << std::endl;
  BasicBlockRequestHelper bbrh(request);
  bbrh.dump((*m_osb));
    
  (*m_osb) << "---===[> Server respond:" << std::endl;
  BasicBlockResponseHelper bbresph((const BasicBlockResponse*)response);
  bbresph.dump((*m_osb));
  return ::Status::OK;
}
  
::grpc::Status
CfgCollectionServicesImpl::EdgeService(::grpc::ServerContext* context,
                                       const EdgeRequest* request,
                                       EdgeResponse* response)
{
  (*m_osb) << "---===[> Client sent:" << std::endl;
  EdgeRequestHelper erh(request);
  erh.dump((*m_osb));
    
  (*m_osb) << "---===[> Server respond:" << std::endl;
  EdgeResponseHelper eresph((const EdgeResponse*)response);
  eresph.dump((*m_osb));
  return ::Status::OK;
}
  
#ifndef SINGLE_TEST_EXE

#include <boost/program_options.hpp>

namespace po = boost::program_options;

void
RunServer(std::string server_address)
{
  CfgCollectionServicesImpl *service = new CfgCollectionServicesImpl(&std::cout);

  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService((grpc::Service*)service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  (*m_osb) << "!! Server listening on " << server_address << std::endl;
  server->Wait();
}

static unsigned int verbose_option = 0;
static char *hostname_option = (char *)"localhost";
static unsigned int port_option = 50051;

int
main(int argc, char** argv)
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

#endif
