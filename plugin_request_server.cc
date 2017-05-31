//
// Copyright ©2017 NagraFrance
//

#include <grpc/grpc.h>
#include <grpc++/server.h>
#include <grpc++/server_builder.h>
#include <grpc++/server_context.h>
#include <grpc++/security/server_credentials.h>

#include "plugin_request.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;

using versionservice::VersionRequest;
using versionservice::VersionResponse;
using versionservice::InsertionPointRequest;
using versionservice::InsertionPointResponse;

class VersionServiceImpl final: public VersionService::Service
{
 public:
  explicit VersionServiceImpl(const std::string& db)
  {
    versionservice::ParseDb(db, &feature_list_);
  }

  Status 
}
