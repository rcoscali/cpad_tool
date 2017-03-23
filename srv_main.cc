/*
 * Copyright ©2017 NagraFrance
 */

#include <syslog.h>
#include <unistd.h>

#include <ctime>
#include <iostream>

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/udp.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>

#include "Server.h"
#include "plugin_request.pb.h"

using namespace std;
using namespace boost::asio;
using namespace boost::asio::ip;

int
main(int argc, char **argv)
{
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  try
    {
      pid_t pid;
      
      if (argc != 2)
	{
	  cerr << "Usage: cpad_srv <port>" << endl;
	  return 1;
	}

      io_service io_svc;
      
      boost::asio::signal_set signals(io_svc, SIGINT, SIGTERM, SIGHUP);
      signals.async_wait(boost::bind(&io_service::stop, &io_svc));
      io_svc.notify_fork(io_service::fork_prepare);
      if (pid = fork())
        {
          if (pid == 0)
            exit(0);
          
          else
            {
              syslog(LOG_ERR | LOG_USER, "First fork failed: %m");
              return 1;
            }
        }
      setsid();
      // Eventually change dir to root
      //chdir("/");
      umask(0);
      
      // Second fork to be sure process will not
      // acquire controlling terminal
      if (pid_t pid2 = fork())
        {
          if (pid2 > 0)
            exit(0);
          
          else
            {
              syslog(LOG_ERR | LOG_USER, "Second fork failed: %m");
              return 1;
            }
        }
      
      // Close std input, output & error
      close(0);
      close(1);
      close(2);
      
      // No more std input possible
      if (open("/dev/null", O_RDONLY) < 0)
        {
          syslog(LOG_ERR | LOG_USER, "Unable to open /dev/null: %m");
          return 1;
        }
      
      // Configure std output, error to a log file
      const char* output = "cpad_srv.log";
      const int flags = O_WRONLY | O_CREAT | O_APPEND;
      const mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
      if (open(output, flags, mode) < 0)
        {
          syslog(LOG_ERR | LOG_USER, "Unable to open output file %s: %m", output);
          return 1;
        }
      
      // Also send standard error to the same log file.
      if (dup(1) < 0)
        {
          syslog(LOG_ERR | LOG_USER, "Unable to dup output descriptor: %m");
          return 1;
        }
      
      io_svc.notify_fork(boost::asio::io_service::fork_child);
      
      cout << "PID " << getpid() << ": CPAD server started!" << endl;
      cpad::server s(io_svc, atoi(argv[1]));
      
      syslog(LOG_INFO | LOG_USER, "Daemon started");
      io_svc.run();
      syslog(LOG_INFO | LOG_USER, "Daemon stopped");
    }
  catch (exception& e)
    {
      cerr << "Exception while accepting request: " << e.what() << "!" << endl;
    }
      
  return (0);
}
