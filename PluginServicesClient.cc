//
// Copyright 2017 NagraFrance
//

#include <iostream>
#include <sstream>

#include "PluginServicesClient.h"

PluginServicesClient::PluginServicesClient(std::shared_ptr<Channel> channel)
  : m_stub(PluginServices::NewStub(channel))
{
}

void PluginServicesClient::VersionService(std::ostream& osb)
{
  ClientContext context;
  VersionRequestHelper vrh(0, 1, std::string("gRPC test Client"));
  VersionResponseHelper vresph(0, 0, std::string(""));

  osb << "---===[> Client send:" << std::endl;
  vrh.dump(osb);
    
  Status status = m_stub->VersionService(&context,
                                         (const VersionRequest&)vrh,
                                         (VersionResponse*)&vresph);
  if (!status.ok())
    {
      osb << "---EEE* VersionService rpc failed." << std::endl;
    }
  else
    {
      osb << "---===[> Server responded:" << std::endl;
      vresph.dump(osb);
    }
}

void
PluginServicesClient::InsertionPointService(std::ostream& osb)
{
  ClientContext context;
  InsertionPointRequestHelper iprh(std::string("foobar.c"),
                                   std::string("foo"),
                                   cpad::insns::FUNCTION_BEFORE_CALL);
  InsertionPointResponseHelper ipresph("");

  osb << "---===[> Client send:" << std::endl;
  iprh.dump(osb);

  Status status = m_stub->InsertionPointService(&context,
                                                (const InsertionPointRequest&)iprh,
                                                (InsertionPointResponse*)&ipresph);
  if (!status.ok())
    {
      osb << "---EEE* InsertionPointService rpc failed." << std::endl;
    }
  else
    {
      osb << "---===[> Server responded:" << std::endl;
      ipresph.dump(osb);
    }
    
}

#ifndef SINGLE_TEST_EXE

#include <boost/program_options.hpp>

namespace po = boost::program_options;

static unsigned int verbose_option = 0;
static char *hostname_option = (char *)"localhost";
static unsigned int port_option = 50051;

int
main(int argc, char** argv)
{
  // Check PB compat
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  // Declare the supported options.
  po::options_description desc("Options allowed for test gRPC PluginServices client.");  
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


      PluginServicesClient client(::grpc::CreateChannel(server_address_str,
                                                        grpc::InsecureChannelCredentials()));

      std::cout << "**[ VersionService RPC test:" << std::endl;
      client.VersionService();
      std::cout << "**[ InsertionPointService RPC test:" << std::endl;
      client.InsertionPointService();
    }
  
  return 0;
}

#endif /* SINGLE_TEST_EXE */
