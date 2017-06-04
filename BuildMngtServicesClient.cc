//
// Copyright 2017 NagraFrance
//

#include <iostream>
#include <sstream>

#include "BuildMngtServicesClient.h"

BuildMngtServicesClient::BuildMngtServicesClient(std::shared_ptr<Channel> channel)
  : m_stub(BuildMngtServices::NewStub(channel))
{
}

void
BuildMngtServicesClient::StartCfgCollectionService(std::ostream& osb)
{
  ClientContext context;
  StartCfgCollectionRequestHelper sccrh(std::string("gRPC test Client build"),
                                        16,
                                        std::string("<cpad_config></cpad_config>"));
  StartCfgCollectionResponseHelper sccresph(StartCfgCollectionResponse::CPAD_CONFIG_ERROR,
                                            std::string("\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0"));

  osb << "---===[> Client send:" << std::endl;
  sccrh.dump(osb);
    
  Status status = m_stub->StartCfgCollectionService(&context,
                                                    (const StartCfgCollectionRequest&)sccrh,
                                                    (StartCfgCollectionResponse*)&sccresph);
  if (!status.ok())
    {
      osb << "---EEE* StartCfgCollectionService rpc failed." << std::endl;
    }
  else
    {
      osb << "---===[> Server responded:" << std::endl;
      sccresph.dump(osb);
    }
}

void
BuildMngtServicesClient::EndCfgCollectionService(std::ostream& osb)
{
  ClientContext context;
  EndCfgCollectionRequestHelper eccrh(std::string("\x6e\x67\x75\x5f\xef\x1b\x46\x98\x87\x5b\x5f\xa8\x6d\x25\x6c\x39"));
  EndCfgCollectionResponseHelper eccresph(EndCfgCollectionResponse::APEX_ALLOCATION_ERROR, std::string(""));

  osb << "---===[> Client send:" << std::endl;
  eccrh.dump(osb);
    
  Status status = m_stub->EndCfgCollectionService(&context,
                                                  (const EndCfgCollectionRequest&)eccrh,
                                                  (EndCfgCollectionResponse*)&eccresph);
  if (!status.ok())
    {
      osb << "---EEE* EndCfgCollectionService rpc failed." << std::endl;
    }
  else
    {
      osb << "---===[> Server responded:" << std::endl;
      eccresph.dump(osb);
    }
}

void
BuildMngtServicesClient::StartCfgToolingService(std::ostream& osb)
{
  ClientContext context;
  StartCfgToolingRequestHelper sctrh(std::string("\x72\x35\x59\x6a\x93\x32\x45\x8c\xb1\x56\xd6\xbd\xb6\x73\x65\x5e"));
  StartCfgToolingResponseHelper sctresph;

  osb << "---===[> Client send:" << std::endl;
  sctrh.dump(osb);
    
  Status status = m_stub->StartCfgToolingService(&context,
                                                 (const StartCfgToolingRequest&)sctrh,
                                                 (StartCfgToolingResponse*)&sctresph);
  if (!status.ok())
    {
      osb << "---EEE* StartCfgToolingService rpc failed." << std::endl;
    }
  else
    {
      osb << "---===[> Server responded:" << std::endl;
      sctresph.dump(osb);
    }
}

void
BuildMngtServicesClient::EndCfgToolingService(std::ostream& osb)
{
  ClientContext context;
  EndCfgToolingRequestHelper ectrh(std::string("\xb7\x1c\xc0\x17\x06\x47\x47\xf0\xb6\x05\x0e\xb7\xc1\x42\x6c\xf1"));
  EndCfgToolingResponseHelper ectresph("");

  osb << "---===[> Client send:" << std::endl;
  ectrh.dump(osb);
    
  Status status = m_stub->EndCfgToolingService(&context,
                                               (const EndCfgToolingRequest&)ectrh,
                                               (EndCfgToolingResponse*)&ectresph);
  if (!status.ok())
    {
      osb << "---EEE* EndCfgToolingService rpc failed." << std::endl;
    }
  else
    {
      osb << "---===[> Server responded:" << std::endl;
      ectresph.dump(osb);
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

#endif /* !SINGLE_TEST_EXE */
