//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>

#include "VersionMsg.h"
#include "CUnitTerminateMsg.h"

using boost::asio::ip::tcp;

enum { max_length = 1024 };

int
main(int argc, char* argv[])
{
  // Check PB compat
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  try
  {
    if (argc != 3)
    {
      std::cerr << "Usage: cpad_clt <host> <port>\n";
      return 1;
    }

    // Boost I/O service
    boost::asio::io_service io_service;

    // Use network (dns, tcp, etc...)
    tcp::resolver resolver(io_service);
    tcp::resolver::query query(tcp::v4(), argv[1], argv[2]);
    tcp::resolver::iterator iterator = resolver.resolve(query);

    // Get socket and connect
    tcp::socket s(io_service);
    boost::asio::connect(s, iterator);

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
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
