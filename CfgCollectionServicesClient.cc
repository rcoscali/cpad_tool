//
// Copyright 2017 NagraFrance
//

#include <iostream>
#include <sstream>

#include "CfgCollectionServicesClient.h"

CfgCollectionServicesClient::CfgCollectionServicesClient(std::shared_ptr<Channel> channel)
  : m_stub(CfgCollectionServices::NewStub(channel))
{
}

void
CfgCollectionServicesClient::CompilationUnitStartService(std::ostream& osb)
{
  ClientContext context;
  CompilationUnitStartRequestHelper cusrh(std::string("FooBar.cc"));
  CompilationUnitStartResponseHelper cusresph;

  osb << "---===[> Client send:" << std::endl;
  cusrh.dump(osb);
    
  Status status = m_stub->CompilationUnitStartService(&context,
                                                      (const CompilationUnitStartRequest&)cusrh,
                                                      (CompilationUnitStartResponse*)&cusresph);
  if (!status.ok())
    {
      osb << "---EEE* CompilationUnitStartService rpc failed." << std::endl;
    }
  else
    {
      osb << "---===[> Server responded:" << std::endl;
      cusresph.dump(osb);
    }
}

void
CfgCollectionServicesClient::CompilationUnitEndService(std::ostream& osb)
{
  ClientContext context;
  CompilationUnitEndRequestHelper cuerh;
  CompilationUnitEndResponseHelper cueresph;

  osb << "---===[> Client send:" << std::endl;
  cuerh.dump(osb);
    
  Status status = m_stub->CompilationUnitEndService(&context,
                                                    (const CompilationUnitEndRequest&)cuerh,
                                                    (CompilationUnitEndResponse*)&cueresph);
  if (!status.ok())
    {
      osb << "---EEE* CompilationUnitEndService rpc failed." << std::endl;
    }
  else
    {
      osb << "---===[> Server responded:" << std::endl;
      cueresph.dump(osb);
    }
}


void
CfgCollectionServicesClient::FunctionService(std::ostream& osb)
{
  ClientContext context;
  FunctionRequestHelper frh(std::string("FooBar.cc"), std::string("Foo"));
  FunctionResponseHelper fresph;

  osb << "---===[> Client send:" << std::endl;
  frh.dump(osb);
    
  Status status = m_stub->FunctionService(&context,
                                          (const FunctionRequest&)frh,
                                          (FunctionResponse*)&fresph);
  if (!status.ok())
    {
      osb << "---EEE* FunctionService rpc failed." << std::endl;
    }
  else
    {
      osb << "---===[> Server responded:" << std::endl;
      fresph.dump(osb);
    }
}

void
CfgCollectionServicesClient::BasicBlockService(std::ostream& osb)
{
  ClientContext context;
  BasicBlockRequestHelper bbrh(std::string("FooBar.cc"), std::string("Foo"), std::string("BB3"));
  BasicBlockResponseHelper bbresph;

  osb << "---===[> Client send:" << std::endl;
  bbrh.dump(osb);
    
  Status status = m_stub->BasicBlockService(&context,
                                            (const BasicBlockRequest&)bbrh,
                                            (BasicBlockResponse*)&bbresph);
  if (!status.ok())
    {
      osb << "---EEE* BasicBlockService rpc failed." << std::endl;
    }
  else
    {
      osb << "---===[> Server responded:" << std::endl;
      bbresph.dump(osb);
    }
}

void
CfgCollectionServicesClient::EdgeService(std::ostream& osb)
{
  ClientContext context;
  EdgeRequestHelper erh(std::string("FooBar.cc"), std::string("Foo"), std::string("BB2"),
                        std::string("FooBaz.cc"), std::string("Baz"), std::string("BB5"),
                        cpad::cfg::EDGE_FALLBACK_BRANCH);
  EdgeResponseHelper eresph;

  osb << "---===[> Client send:" << std::endl;
  erh.dump(osb);
    
  Status status = m_stub->EdgeService(&context,
                                      (const EdgeRequest&)erh,
                                      (EdgeResponse*)&eresph);
  if (!status.ok())
    {
      osb << "---EEE* EdgeService rpc failed." << std::endl;
    }
  else
    {
      osb << "---===[> Server responded:" << std::endl;
      eresph.dump(osb);
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

#endif /* !SINGLE_TEST_EXE */
