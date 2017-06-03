#ifdef SINGLE_TEST_EXE
#include <gtest/gtest.h>

#include "PluginServices.h"
#include "CfgCollectionServices.h"
#include "BuildMngtServices.h"

void RunServer(std::string server_address)
{
  CfgCollectionServicesImpl *service1 = new CfgCollectionServicesImpl();
  PluginServicesImpl *service2 = new PluginServicesImpl();
  BuildMngtServicesImpl *service3 = new BuildMngtServicesImpl();

  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  
  builder.RegisterService((grpc::Service*)service1);
  builder.RegisterService((grpc::Service*)service2);
  builder.RegisterService((grpc::Service*)service3);
  
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "!! Server listening on " << server_address << std::endl;
  server->Wait();
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
#endif
