//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <cstdlib>
#include <iostream>

#include "Server.h"
#include "plugin_request.pb.h"

using namespace boost::system;
using namespace boost;
using namespace boost::asio;
using namespace boost::asio::ip;

cpad::session::session(io_service& io_service)
  : m_socket(io_service)
{
}

tcp::socket&
cpad::session::socket(void)
{
  return m_socket;
}

void
cpad::session::start(void)
{
  m_socket.async_read_some(buffer(m_data, max_length),
			   boost::bind(&session::handle_read,
				       this,
				       asio::placeholders::error,
				       asio::placeholders::bytes_transferred));
}

void
cpad::session::handle_read(const error_code& error,
			   size_t bytes_transferred)
{
  if (!error)
    {
      std::cout << "handle_read" << std::endl;
      VersionRequest req;
      req.ParseFromString(m_data);
      std::cout << "client minor: " << req.client_version_minor() << std::endl;
      std::cout << "client major: " << req.client_version_major() << std::endl;
      std::cout << "client provider: " << req.client_provider_name() << std::endl;
      std::string response;
      VersionResponse resp;
      resp.set_server_version_minor(3);
      resp.set_server_version_major(4);
      resp.set_server_provider_name("server");
      resp.SerializeToString(&response);
      response.copy(m_data, response.length());
      async_write(m_socket,
                  buffer(m_data, response.length()),
                  boost::bind(&session::handle_write,
                              this,
                              asio::placeholders::error));
    }
  else
    delete this;
}

void
cpad::session::handle_write(const error_code& error)
{
  if (!error)
    {
      std::cout << "handle_write" << std::endl;
      m_socket.async_read_some(buffer(m_data, max_length),
                               boost::bind(&session::handle_read,
                                           this,
                                           asio::placeholders::error,
                                           asio::placeholders::bytes_transferred));
      std::cout << "data written: " << m_data << std::endl;
    }
  else
    delete this;
}



cpad::server::server(io_service& io_svc, short port)
  : m_io_svc(io_svc),
    m_signal(io_svc, SIGCHLD),
    m_acceptor(io_svc, tcp::endpoint(tcp::v4(), port))
{
  start_accept();
}

void
cpad::server::start_signal_wait(void)
{
  m_signal.async_wait(boost::bind(&server::handle_signal_wait, this));
}

void
cpad::server::handle_signal_wait(void)
{
  if (m_acceptor.is_open())
    {
      // Reap completed child processes so that we don't end up with zombies.
      int status = 0;
      while (waitpid(-1, &status, WNOHANG) > 0) {}

      start_signal_wait();
    }
}

void
cpad::server::start_accept()
{
  session* new_session = new cpad::session(m_io_svc);
  m_acceptor.async_accept(new_session->socket(),
			  boost::bind(&server::handle_accept,
				      this,
                                      new_session,
				      asio::placeholders::error));
}

void
cpad::server::handle_accept(session* new_session,
			    const error_code& error)
{
  if (!error)
    {
      std::cout << "Forking for handling session\n";
      m_io_svc.notify_fork(io_service::fork_prepare);
      if (fork() > 0)
        {
          m_io_svc.notify_fork(io_service::fork_child);
          m_acceptor.close();
          m_signal.cancel();

          std::cout << "PID " << getpid() << " forked for handling session\n";
          
          new_session->start();
        }
    }

  else
    delete new_session;
  
  start_accept();
}

