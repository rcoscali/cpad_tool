//
// Copyright ©2017 Nagravision
//

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>

#include "VersionMsg.h"
#include "CUnitTerminateMsg.h"

using boost::asio::ip::tcp;

enum { max_length = 1024 };

Client::Client(boost::asio::io_service io_svc)
  : m_io_svc(io_svc),
    m_socket(io_svc)
{
}

void
Client::do_connect(std::string hostname, std::string port)
{
  try
    {
      // Use network (dns, tcp, etc...)
      tcp::resolver resolver(m_io_svc);
      tcp::resolver::query query(tcp::v4(), argv[1], argv[2]);
      tcp::resolver::iterator iterator = resolver.resolve(query);
  
      // Get socket and connect
      boost::asio::connect(m_socket, iterator);
    }
  catch (Exception &e)
    {
      std::cerr << "Exception: " << e.what() << std::endl;
    }
}

void
Client::check_version(void)
{
  GOOGLE_PROTOBUF_VERIFY_VERSION;
  
  // Create version request
  cpad::VersionRequestHelper req(1, 2, "client");
  
  // Serialize and send
  char request[max_length];    
  size_t request_length = req.serialize(request);
  boost::asio::write(s,
                     boost::asio::buffer(request,
                                         request_length));
  
  // Read response
  char reply[max_length];
  size_t reply_length = boost::asio::read(s,
                                          boost::asio::buffer(reply,
                                                              request_length));
  
  // Display unserialized response
  cpad::VersionResponseHelper resp((const char *)reply);
  std::cout << "Reply is: " << std::endl;
  resp.dump();
}

void
send_insertion_point()
{
}

void
send_cunit_terminate()
{
    // Create Terminate request
    cpad::CUnitTerminateRequestHelper req2(std::string("clt_main.cc"));
    request_length = req.serialize(request);
    boost::asio::write(s,
                       boost::asio::buffer(request,
                                           request_length));

    // Read response
    reply_length = boost::asio::read(s,
                                     boost::asio::buffer(reply,
                                                         request_length));
    
    // Display unserialized response
    cpad::CUnitTerminateResponseHelper resp2((const char *)reply);
    std::cout << "Reply is: " << std::endl;
    resp2.dump();
}
