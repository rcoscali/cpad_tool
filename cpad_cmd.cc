//
// @file cpad.cc
//
// Copyright ©2017 NagraFrance
//
// CPAD client command:
// This command allows the server to be notified at important build process steps.
// The following diagrams roughly describe the CPAD build processes.
//
// A CPAD build is made of two phases:
//  - (CFG-coll-phase) The CFG collection phase:
//    this phase allows the CPAD server to collect and consolidate the control flow graph
//    from the compilation of each source file going through the compiler thanks to our
//    GCC plugin architecture
//  - (CFG-tool-phase) the CFG tooling phase
//
// +-------+    
// | Start |--+ 
// +-------+  |  
//            |    +----------------------+ (1)                   (1): Message StartCfgCollectionRequest sent
//            +->  | Start CFG collection |-----+                      and server respond StartCfgCollectionResponse
//                 +----------------------+     |
//           (2)+---------------------------+   |                 (2): Message from plugin_request.proto are sent and
//              |     Plugin create CFG     |   |                      answered for collecting Control Flow Graph and
//          +---|    while gcc build each   | <-+                      consolidating it in server (msgs between plugin
//          |   |     compilation unit      |                          and server are not shown)
//          |   +---------------------------+
//          |      +--------------------+ 
//          +----> | End CFG collection | --+                     (3): Message EndCfgCollectionRequest allows to notify
//             (3) +--------------------+   |                          the server the whole CFG shall be collected. Server
//                                          |                          then allocate APEX checkpoints and send back its
//              (4)+--------------------+   |                          status.
//          +------|  Start CFG tooling | <-+                     (4): Actual code insertion will really start after 
//          |      +--------------------+                              server answer (StartCfgToolingResponse) to msg
//          |(5)+---------------------------+                          StartCfgToolingRequest
//          |   |     Plugin insert APEX    |    
//          +-> |    while gcc build each   |--+                  (5): Plugin will send messages from plugin_request.proto
//              |     compilation unit      |  |                       and code to insert are in resp. responses.
//              +---------------------------+  |
//                                             |
//                 +-----------------+         |                  (6): The EndCfgToolingRequest tells the server the 
//              (6)| End CFG tooling | <-------+                       compilation process is terminated. The message
//                 +-----------------+                                 EndCfgToolingResponse may contain stats about 
//                                                                     code inserted

#include <cstdlib>
#include <cstring>
#include <iostream>

#include <boost/program_options.hpp>
#include <boost/asio.hpp>

#include "VersionMsg.h"
#include "CUnitTerminateMsg.h"
#include "BuildMngtMsg.h"

using namespace boost;
namespace po = boost::program_options;
using boost::asio::ip::tcp;
using namespace std;

enum { max_length = 1024 };

int
main(int argc, char *argv[])
{
  int ret = 1;
  
  // Check PB compat
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  try
    {
      do
	{
	  // Declare the supported options.
	  po::options_description desc("CPAD command options");
	
	  // Add spec for options
	  desc.add_options()
	    ("help", "CPAD help message")
	    ("collect", "CPAD CFG collection phase")
	    ("tooling", "CPAD CFG tooling phase")
	    ("start", "CPAD phase start")
	    ("end", "CPAD phase end")
	    ("config", po::value<std::string>(), "CPAD configuration file")
	    ;
	
	  po::variables_map vm;
	  po::store(po::parse_command_line(argc, argv, desc), vm);
	  po::notify(vm);
	
	  if (vm.count("help"))
	    {
	      cout << desc << "\n";
	    }
	  else
	    {
	      int opt_err = 0;
	    
	      if (vm.count("collect") && vm.count("tooling"))
		{
		  cerr << "You cannot request both phases (collect & tooling) together\n";
		  opt_err = 1;
		}
	      else if (vm.count("collect") == 0 && vm.count("tooling") == 0)
		{
		  cerr << "You must select at least one phase (collect or tooling).\n";
		  opt_err = 1;
		}
	      else if (vm.count("collect"))
		{
		  cout << "Collect phase requested.\n";
		}
	      else if (vm.count("tooling"))
		{
		  cout << "Tooling phase requested.\n";
		}
	    
	      if (vm.count("start") && vm.count("end"))
		{
		  cerr << "You cannot request both phase step (start & end) together\n";
		  opt_err = 1;
		}
	      else if (vm.count("start") == 0 && vm.count("end") == 0)
		{
		  cerr << "You must select at least phase step (start or end).\n";
		  opt_err = 1;
		}
	      else if (vm.count("start"))
		{
		  cout << "Phase start requested.\n";
		}
	      else if (vm.count("end"))
		{
		  cout << "Phase end requested.\n";
		}
	    
	      if (opt_err)
		break;
	    }
	}
      while (0);
      
      ret = 0;
    }
  catch (std::exception& e)
    {
      std::cerr << "cpad_cmd: Exception: " << e.what() << "\n";
    }

  return ret;
}
