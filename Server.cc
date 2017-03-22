//
// async_tcp_echo_server.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
// http://www.boost.org/doc/libs/1_53_0/doc/html/boost_asio/examples.html
// Copyright (c) 2003-2012 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <iostream>

#include "Server.h"

using namespace std;
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
    async_write(m_socket,
		buffer(m_data, bytes_transferred),
		boost::bind(&session::handle_write,
			    this,
			    asio::placeholders::error));

  else
    delete this;
}

void
cpad::session::handle_write(const error_code& error)
{
  if (!error)
    m_socket.async_read_some(buffer(m_data, max_length),
			     boost::bind(&session::handle_read,
					 this,
					 asio::placeholders::error,
					 asio::placeholders::bytes_transferred));
  else
    delete this;
}



cpad::server::server(io_service& io_svc, short port)
  : m_io_svc(io_svc),
    m_acceptor(io_svc, tcp::endpoint(tcp::v4(), port))
{
  start_accept();
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
    new_session->start();

  else
    delete new_session;
  
  start_accept();
}

