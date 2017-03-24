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
#include "VersionMsg.h"

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
cpad::session::dump_data(size_t size)
{
  char chardump[17];
  bzero(chardump, 17);
  char dumped = 0;
  
  for (int i = 0; i < size; i++)
    {
      dumped = 0;
      chardump[i%16] = (m_data[i] > 32 ? (m_data[i] < 127 ? m_data[i] : '.') : '.');
      if (i % 16 == 0)
        printf("%08x ", i);
      printf("%02x", m_data[i]);
      if (i % 2 == 1)
        printf(" ");
      if (i % 16 == 15)
        {
          dumped = 1;
          printf("  %16s \n", chardump);
          bzero(chardump, 16);
        }
    }
  if (!dumped)
    printf("  %16s \n", chardump);
  else
    printf("\n");
}

void
cpad::session::handle_read(const error_code& error,
			   size_t bytes_transferred)
{
  std::cout << "handle_read: entry" << std::endl;
  if (!error)
    {
      // Dump bytes received
      std::cout << "recv data:\n";
      dump_data(bytes_transferred);

      // Create request from data
      VersionRequestHelper req((const char *)m_data);
      req.dump();

      // Create response
      VersionResponseHelper resp(3, 4, "server");
      resp.dump();

      // Serialize response
      size_t response_len = resp.serialize(m_data);
      std::cout << "sent data:\n";
      dump_data(response_len);

      // And send it asynchronously
      async_write(m_socket,
                  buffer(m_data, response_len),
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
      m_io_svc.notify_fork(io_service::fork_prepare);
      if (fork() > 0)
        {
          m_io_svc.notify_fork(io_service::fork_child);
          m_acceptor.close();
          m_signal.cancel();

          new_session->start();
        }
    }

  else
    delete new_session;
  
  start_accept();
}

