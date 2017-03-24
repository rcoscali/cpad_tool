//
// Copyright ©2017 Nagravision
//

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>

#include "VersionMsg.h"
#include "InsertionPointMsg.h"
#include "CUnitTerminateMsg.h"

namespace cpad
{
  class Client
  {
  public:
    Client(boost::asio::io_service io_svc);
    cirtual ~Client();

    void do_connect(std::string, std::string);
    send_version_request();

  private:
    // Boost I/O service
    boost::asio::io_service m_io_svc;
    tcp::socket m_socket;

  }
