/*
 * Copyright ©2017 NagraFrance
 */

#include "Server.h"

using namespace std;
using namespace boost::asio;
using namespace boost::asio::ip;

int
main(int argc, char **argv)
{
  try
    {
      if (argc != 2)
	{
	  cerr << "Usage: cpad_srv <port>" << endl;
	  return 1;
	}

      io_service io_svc;
      cpad::server s(io_svc, atoi(argv[1]));

      io_svc.run();
    }
  catch (exception& e)
    {
      cerr << "Exception while accepting request: " << e.what() << "!" << endl;
    }
      
  return (0);
}
