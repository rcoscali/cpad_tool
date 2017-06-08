//
// Copyright 2017, Google Inc.
//

#include <iostream>
#include <sstream>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/string_generator.hpp>

#include <boost/program_options.hpp>

namespace po = boost::program_options;

#include "BuildMngtServices.h"

#define TEST_UUID_VALUE { 0xdb, 0xfa, 0x53, 0x67, 0xed, 0xd4, 0x46, 0x97, 0x90, 0x09, 0x40, 0x3f, 0xd7, 0x1b, 0x8f, 0xed }
#define TEST_UUID_STR "dbfa5367-edd4-4697-9009-403fd71b8fed"

static unsigned int verbose_option = 0;
static char *hostname_option = (char *)"localhost";
static unsigned int port_option = 50051;

BuildMngtServicesImpl::BuildMngtServicesImpl(std::ostream* osb)
{
  m_osb = osb ? osb : &std::cout;
}

BuildMngtServicesImpl::~BuildMngtServicesImpl()
{
}
  
::grpc::Status
BuildMngtServicesImpl::StartCfgCollectionService(::grpc::ServerContext* context,
                                                 const StartCfgCollectionRequest* request,
                                                 StartCfgCollectionResponse* response)
{
  (*m_osb) << "---===[> Client sent:" << std::endl;
  StartCfgCollectionRequestHelper sccrh(request);
  sccrh.dump((*m_osb));

  boost::uuids::uuid u = TEST_UUID_VALUE;
  response->set_cpad_config_status(StartCfgCollectionResponse::CPAD_CONFIG_OK);
  response->set_uuid(to_string(u));
  
  (*m_osb) << "---===[> Server respond:" << std::endl;
  StartCfgCollectionResponseHelper sccresph((const StartCfgCollectionResponse*)response);
  sccresph.dump((*m_osb));
  
  return ::Status::OK;
}

::grpc::Status
BuildMngtServicesImpl::EndCfgCollectionService(::grpc::ServerContext* context,
                                               const EndCfgCollectionRequest* request,
                                               EndCfgCollectionResponse* response)
{
  (*m_osb) << "---===[> Client sent:" << std::endl;
  EndCfgCollectionRequestHelper eccrh(request);
  eccrh.dump((*m_osb));
  
  response->set_apex_allocation_status(EndCfgCollectionResponse::APEX_ALLOCATION_OK);
  response->set_apex_allocation_message(std::string("APEX Allocated!"));
  
  (*m_osb) << "---===[> Server respond:" << std::endl;
  EndCfgCollectionResponseHelper eccresph((const EndCfgCollectionResponse*)response);
  eccresph.dump((*m_osb));
  
  return ::Status::OK;
}

::grpc::Status
BuildMngtServicesImpl::StartCfgToolingService(::grpc::ServerContext* context,
                                              const StartCfgToolingRequest* request,
                                              StartCfgToolingResponse* response)
{
  (*m_osb) << "---===[> Client sent:" << std::endl;
  StartCfgToolingRequestHelper sctrh(request);
  sctrh.dump((*m_osb));
    
  (*m_osb) << "---===[> Server respond:" << std::endl;
  StartCfgToolingResponseHelper sctresph((const StartCfgToolingResponse*)response);
  sctresph.dump((*m_osb));
    
  return ::Status::OK;
}

::grpc::Status
BuildMngtServicesImpl::EndCfgToolingService(::grpc::ServerContext* context,
                                            const EndCfgToolingRequest* request,
                                            EndCfgToolingResponse* response)
{
  (*m_osb) << "---===[> Client sent:" << std::endl;
  EndCfgToolingRequestHelper ectrh(request);
  ectrh.dump((*m_osb));
    
  ::google::protobuf::Map<::std::string, ::cpad::build_mngt::EndCfgToolingResponse_BbStat> *stat = response->mutable_statistics();
  ::cpad::build_mngt::EndCfgToolingResponse_BbStat bb1stat;
  bb1stat.set_bb_original_length(10);
  bb1stat.set_bb_modified_length(15);
  (*stat)[std::string("BB1")] = bb1stat;
  ::cpad::build_mngt::EndCfgToolingResponse_BbStat bb2stat;
  bb2stat.set_bb_original_length(12);
  bb2stat.set_bb_modified_length(19);
  (*stat)[std::string("BB2")] = bb2stat;
  ::cpad::build_mngt::EndCfgToolingResponse_BbStat bb3stat;
  bb3stat.set_bb_original_length(14);
  bb3stat.set_bb_modified_length(17);
  (*stat)[std::string("BB3")] = bb3stat;
  ::cpad::build_mngt::EndCfgToolingResponse_BbStat bb4stat;
  bb4stat.set_bb_original_length(34);
  bb4stat.set_bb_modified_length(65);
  (*stat)[std::string("BB4")] = bb4stat;

  (*m_osb) << "---===[> Server respond:" << std::endl;
  EndCfgToolingResponseHelper ectresph((const EndCfgToolingResponse*)response);
  ectresph.dump((*m_osb));
    
  return ::Status::OK;
}

#ifndef SINGLE_TEST_EXE

#include <boost/program_options.hpp>

namespace po = boost::program_options;

void
RunServer(std::string server_address)
{
  BuildMngtServicesImpl *service = new BuildMngtServicesImpl();

  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService((grpc::Service*)service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cerr << "!! Server listening on " << server_address << std::endl;
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
  po::options_description desc("Options allowed for test gRPC BuildMngtServices server.");
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
      std::cerr << desc << std::endl;
    }
  else
    {
      if (vm.count("hostname"))
        hostname_option = (char *)vm["hostname"].as<std::string>().c_str();

      if (vm.count("port"))
        port_option = vm["port"].as<unsigned int>();
      
      if (verbose_option)
        {
          std::cerr << "**> Verbosity set to level " << (unsigned int)verbose_option << std::endl;
          if (vm.count("hostname"))
            std::cerr << "**> Hostname set to '" << vm["hostname"].as<std::string>() << "'" << std::endl;
          if (vm.count("port"))
            std::cerr << "**> Port set to " << vm["port"].as<unsigned int>() << std::endl;
        }

      std::ostringstream server_os;
      server_os << hostname_option << ":" << port_option;
      std::string server_address_str = server_os.str();

      if (verbose_option)
        std::cerr << "**> Running server on '" << server_address_str << "'" << std::endl;

      RunServer(server_address_str);
    }

  return 0;
}

#endif
