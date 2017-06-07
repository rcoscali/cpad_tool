//
// Copyright 2017 NagraFrance
//

#include <iostream>
#include <sstream>

#include <boost/program_options.hpp>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/string_generator.hpp>
#include <boost/uuid/nil_generator.hpp>

#include "BuildMngtServicesClient.h"

namespace po = boost::program_options;

static unsigned int verbose_option = 0;
static char *hostname_option = (char *)"localhost";
static unsigned int port_option = 50051;

#define TEST_UUID1_VALUE { 0x6e, 0x67, 0x75, 0x5f, 0xef, 0x1b, 0x46, 0x98, 0x87, 0x5b, 0x5f, 0xa8, 0x6d, 0x25, 0x6c, 0x39 }
#define TEST_UUID1_STR "6e67755f-ef1b-4698-875b-5fa86d256c39"
#define TEST_UUID2_VALUE { 0x72, 0x35, 0x59, 0x6a, 0x93, 0x32, 0x45, 0x8c, 0xb1, 0x56, 0xd6, 0xbd, 0xb6, 0x73, 0x65, 0x5e }
#define TEST_UUID2_STR "7235596a-9332-458c-b156-d6bdb673655e"
#define TEST_UUID3_VALUE { 0xb7, 0x1c, 0xc0, 0x17, 0x06, 0x47, 0x47, 0xf0, 0xb6, 0x05, 0x0e, 0xb7, 0xc1, 0x42, 0x6c, 0xf1 }
#define TEST_UUID3_STR "b71cc017-0647-47f0-b605-0eb7c1426cf1"

BuildMngtServicesClient::BuildMngtServicesClient(std::shared_ptr<Channel> channel)
  : m_stub(BuildMngtServices::NewStub(channel))
{
}

void
BuildMngtServicesClient::StartCfgCollectionService(std::ostream& osb)
{
  boost::uuids::nil_generator niluuidgen;
  boost::uuids::uuid niluuid = niluuidgen();
  ClientContext context;
  StartCfgCollectionRequestHelper sccrh(std::string("gRPC test Client build"),
                                        16,
                                        std::string("<cpad_config></cpad_config>"));
  StartCfgCollectionResponseHelper sccresph(StartCfgCollectionResponse::CPAD_CONFIG_ERROR,
                                            to_string(niluuid));

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
  boost::uuids::uuid u = TEST_UUID1_VALUE;
  ClientContext context;
  EndCfgCollectionRequestHelper eccrh(to_string(u));
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
  boost::uuids::uuid u = TEST_UUID2_VALUE;
  ClientContext context;
  StartCfgToolingRequestHelper sctrh(to_string(u));
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
  boost::uuids::uuid u = TEST_UUID3_VALUE;
  ClientContext context;
  EndCfgToolingRequestHelper ectrh(to_string(u));
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
