//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>

#include "plugin_request.pb.h"

using boost::asio::ip::tcp;

enum { max_length = 1024 };

int main(int argc, char* argv[])
{
  GOOGLE_PROTOBUF_VERIFY_VERSION;
  try
  {
    if (argc != 3)
    {
      std::cerr << "Usage: cpad_clt <host> <port>\n";
      return 1;
    }

    boost::asio::io_service io_service;

    tcp::resolver resolver(io_service);
    tcp::resolver::query query(tcp::v4(), argv[1], argv[2]);
    tcp::resolver::iterator iterator = resolver.resolve(query);

    tcp::socket s(io_service);
    boost::asio::connect(s, iterator);

    cpad::VersionRequest req;
    req.set_client_version_minor(1);
    req.set_client_version_major(2);
    req.set_client_provider_name("client");
    
    std::string request;
    req.SerializeToString(&request);
    size_t request_length = request.length();
    boost::asio::write(s, boost::asio::buffer(request, request_length));

    char reply[max_length];
    size_t reply_length = boost::asio::read(s,
                                            boost::asio::buffer(reply, request_length));
    cpad::VersionResponse resp;
    resp.ParseFromString(reply);
    std::cout << "Reply is: " << std::endl;
    std::cout << "minor: ";
    std::cout << resp.server_version_minor() << std::endl;
    std::cout << "major: ";
    std::cout << resp.server_version_major() << std::endl;
    std::cout << "provider: ";
    std::cout << resp.server_provider_name() << std::endl;
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
