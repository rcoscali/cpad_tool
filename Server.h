/*
 * Copyright ©2017 NagraFrance
 */

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

using namespace boost::asio;
using namespace boost::system;
using namespace boost::asio::ip;

namespace cpad
{
  class session
  {
  public:
    session(io_service& io_service);
    tcp::socket& socket(void);
    void start(void);
    
  private:
    void handle_read(const error_code& error,
		     size_t  bytes_transferred);
    
    void handle_write(const error_code& error);
    
    tcp::socket m_socket;
    enum {
      max_length = 1024
    };
    
    char m_data[max_length];
  };

  class server
  {
  public:
    server(io_service& io_svc, short port);
    
  private:
    void start_accept(void);

    void handle_accept(session* new_session,
		       const error_code& error);

    io_service& m_io_svc;
    tcp::acceptor m_acceptor;
};

}
