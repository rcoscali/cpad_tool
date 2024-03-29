//
// Copyright 2017, Google Inc.
//
#include <iostream>
#include <sstream>

#include "PluginServices.h"

PluginServicesImpl::PluginServicesImpl(std::ostream* osb)
{
  m_osb = osb ? osb : &std::cout;
}
  
PluginServicesImpl::~PluginServicesImpl()
{
}
  
::grpc::Status
PluginServicesImpl::VersionService(::grpc::ServerContext* context,
                                   const ::cpad::insns::VersionRequest* request,
                                   ::cpad::insns::VersionResponse* response)
{
  (*m_osb) << "---===[> Client sent:" << std::endl;
  ::cpad::insns::VersionRequestHelper vrh(request);
  vrh.dump((*m_osb));
    
  response->set_server_version_minor(0);
  response->set_server_version_major(1);
  response->set_server_provider_name(std::string("gRPC test server"));

  (*m_osb) << "---===[> Server respond:" << std::endl;
  ::cpad::insns::VersionResponseHelper vresph((const ::cpad::insns::VersionResponse*)response);
  vresph.dump((*m_osb));
    
  return ::Status::OK;
}
  
::grpc::Status
PluginServicesImpl::InsertionPointService(::grpc::ServerContext* context,
                                          const ::cpad::insns::InsertionPointRequest* request,
                                          ::cpad::insns::InsertionPointResponse* response)
{
  (*m_osb) << "---===[> Client sent:" << std::endl;
  ::cpad::insns::InsertionPointRequestHelper iph(request);
  iph.dump((*m_osb));
    
  response->set_insert_asm_statement(true);
  response->set_asm_statement(std::string("__asm(Nop; Nop; Nop)"));

  (*m_osb) << "---===[> Server respond:" << std::endl;
  ::cpad::insns::InsertionPointResponseHelper ipresph((const ::cpad::insns::InsertionPointResponse*)response);
  ipresph.dump((*m_osb));
  return ::Status::OK;
}
  
#ifndef SINGLE_TEST_EXE

#include <boost/program_options.hpp>

namespace po = boost::program_options;

static unsigned int verbose_option = 0;
static char *hostname_option = (char *)"localhost";
static unsigned int port_option = 50051;

void
RunServer(std::string server_address)
{
  PluginServicesImpl *service = new PluginServicesImpl();

  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService((grpc::Service*)service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cerr << "!! Server listening on " << server_address << std::endl;
  server->Wait();
}

int
main(int argc, char** argv)
{
  // Check PB compat
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  // Declare the supported options.
  po::options_description desc("Options allowed for test gRPC PluginServices server.");
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

#endif /* SINGLE_TEST_EXE */
