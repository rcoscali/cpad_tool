//
// Copyright 2017, Google Inc.
//

// This define is set when an automatic test client is requested  at build time
#ifdef SINGLE_TEST_EXE

#include <sys/types.h>
#include <sys/wait.h>

#include <iostream>     // std::cout, std::ostream, std::hex
#include <sstream>      // std::stringbuf
#include <string>       // std::string

#include <gtest/gtest.h>

// Include Server & Client classes def for PluginServices
#include "PluginServices.h"
#include "PluginServicesClient.h"

class PluginServicesClientServerTests : public ::testing::Test
{
public:
  static constexpr const char * SERVER_ADDRESS = "localhost:50080";
  pid_t m_pid;
  ServerBuilder m_builder;
  PluginServicesImpl *m_service;
  PluginServicesClient *m_client;
  std::unique_ptr<Server> m_server;
  std::stringbuf m_strbuf;
  std::ostream *m_osb;
  std::stringbuf m_strbuf_srv;
  std::ostream *m_osb_srv;
  const std::string DUMPVAL_CLT = "**[ VersionService RPC test:\n" \
    "---===[> Client send:\n"                                  \
    "[VersionRequest]\n"                                       \
    "client minor: 0\n"                                        \
    "client major: 1\n"                                        \
    "client provider: gRPC test Client\n"                      \
    "---===[> Server responded:\n"                             \
    "[VersionResponse]\n"                                      \
    "server minor: 0\n"                                        \
    "server major: 1\n"                                        \
    "server provider: gRPC test server\n"                      \
    "**[ InsertionPointService RPC test:\n"                    \
    "---===[> Client send:\n"                                  \
    "[InsertionPointRequest]\n"                                \
    "cunit name: foobar.c\n"                                   \
    "cfun name: foo\n"                                         \
    "location: ::cpad::insns::FUNCTION_BEFORE_CALL (5)\n"      \
    "---===[> Server responded:\n"                             \
    "[InsertionPointResponse]\n"                               \
    "insert asm statement: 1\n"                                \
    "asm statement: __asm(Nop; Nop; Nop)\n";
  const std::string DUMPVAL_SRV = "---===[> Client sent:\n" \
    "[VersionRequest]\n"                                    \
    "client minor: 0\n"                                     \
    "client major: 1\n"                                     \
    "client provider: gRPC test Client\n"                   \
    "---===[> Server respond:\n"                            \
    "[VersionResponse]\n"                                   \
    "server minor: 0\n"                                     \
    "server major: 1\n"                                     \
    "server provider: gRPC test server\n"                   \
    "---===[> Client sent:\n"                               \
    "[InsertionPointRequest]\n"                             \
    "cunit name: foobar.c\n"                                \
    "cfun name: foo\n"                                      \
    "location: ::cpad::insns::FUNCTION_BEFORE_CALL (5)\n"   \
    "---===[> Server respond:\n"                            \
    "[InsertionPointResponse]\n"                            \
    "insert asm statement: 1\n"                             \
    "asm statement: __asm(Nop; Nop; Nop)\n";

  PluginServicesClientServerTests()
  {
    m_osb = new std::ostream(&m_strbuf);
    m_osb_srv = new std::ostream(&m_strbuf_srv);
    m_service = new PluginServicesImpl(m_osb_srv);
    m_client = new PluginServicesClient(::grpc::CreateChannel(SERVER_ADDRESS,
                                                              grpc::InsecureChannelCredentials()));;
    m_builder.AddListeningPort(SERVER_ADDRESS, grpc::InsecureServerCredentials());
    m_builder.RegisterService((grpc::Service*)m_service);
  }

  virtual ~PluginServicesClientServerTests()
  {
    delete m_client;
    delete m_service;
    delete m_osb;
  }

  virtual void SetUp(void)
  {
    m_server = m_builder.BuildAndStart();
    if ((m_pid = fork()) == 0)
      {
        (*m_osb) << "!! Server listening on " << SERVER_ADDRESS << " !" << std::endl;
        m_server->Wait();        
      }
  }

  virtual void TearDown(void)
  {
    m_server.release();
  }
};

TEST_F(PluginServicesClientServerTests, ClientServerOptimalTest)
{
  (*m_osb) << "**[ VersionService RPC test:" << std::endl;
  m_client->VersionService((*m_osb));

  (*m_osb) << "**[ InsertionPointService RPC test:" << std::endl;
  m_client->InsertionPointService((*m_osb));

  EXPECT_STREQ(DUMPVAL_CLT.c_str(), m_strbuf.str().c_str());
  EXPECT_STREQ(DUMPVAL_SRV.c_str(), m_strbuf_srv.str().c_str());

  (*m_osb) << "**[ Shutdown server:" << std::endl;
  m_server->Shutdown();
  (*m_osb) << "**[ Server down!" << std::endl;
}

// Include Server & Client classes def for CfgCollectionServices
#include "CfgCollectionServices.h"
#include "CfgCollectionServicesClient.h"

class CfgCollectionServicesClientServerTests : public ::testing::Test
{
public:
  static constexpr const char * SERVER_ADDRESS = "localhost:50081";
  pid_t m_pid;
  ServerBuilder m_builder;
  CfgCollectionServicesImpl *m_service;
  CfgCollectionServicesClient *m_client;
  std::unique_ptr<Server> m_server;
  std::stringbuf m_strbuf;
  std::ostream *m_osb;
  std::stringbuf m_strbuf_srv;
  std::ostream *m_osb_srv;
  const std::string DUMPVAL_CLT = "**[ CompilationUnitStartService RPC test:\n" \
    "---===[> Client send:\n"                                           \
    "[CompilationUnitStartRequest]\n"                                   \
    "CUnit filename: FooBar.cc\n"                                       \
    "---===[> Server responded:\n"                                      \
    "[CompilationUnitStartResponse]\n"                                  \
    "**[ CompilationUnitEndService RPC test:\n"                         \
    "---===[> Client send:\n"                                           \
    "[CompilationUnitEndRequest]\n"                                     \
    "---===[> Server responded:\n"                                      \
    "[CompilationUnitEndResponse]\n"                                    \
    "**[ FunctionService RPC test:\n"                                   \
    "---===[> Client send:\n"                                           \
    "[FunctionRequest]\n"                                               \
    "  CUnit name: FooBar.cc\n"                                         \
    "  CFun name: Foo\n"                                                \
    "---===[> Server responded:\n"                                      \
    "[FunctionResponse]\n"                                              \
    "**[ BasicBlockService RPC test:\n"                                 \
    "---===[> Client send:\n"                                           \
    "[BasicBlockRequest]\n"                                             \
    "  CUnit name: FooBar.cc\n"                                         \
    "  CFun name: Foo\n"                                                \
    "  BB name: BB3\n"                                                  \
    "---===[> Server responded:\n"                                      \
    "[BasicBlockResponse]\n"                                            \
    "**[ EdgeService RPC test:\n"                                       \
    "---===[> Client send:\n"                                           \
    "[EdgeRequest]\n"                                                   \
    "  Start BB: \n"                                                    \
    "    | CUnit name: FooBar.cc\n"                                     \
    "    | CFun name: Foo\n"                                            \
    "    | BB name: BB2\n"                                              \
    "  End BB: \n"                                                      \
    "    | CUnit name: FooBaz.cc\n"                                     \
    "    | CFun name: Baz\n"                                            \
    "    | BB name: BB5\n"                                              \
    "  Branch kind: EDGE_FALLBACK_BRANCH\n"                             \
    "---===[> Server responded:\n"                                      \
    "[EdgeResponse]\n"                                                  \
    "";
  const std::string DUMPVAL_SRV = "---===[> Client sent:\n" \
    "[CompilationUnitStartRequest]\n"                       \
    "CUnit filename: FooBar.cc\n"                           \
    "---===[> Server respond:\n"                            \
    "[CompilationUnitStartResponse]\n"                      \
    "---===[> Client sent:\n"                               \
    "[CompilationUnitEndRequest]\n"                         \
    "---===[> Server respond:\n"                            \
    "[CompilationUnitEndResponse]\n"                        \
    "---===[> Client sent:\n"                               \
    "[FunctionRequest]\n"                                   \
    "  CUnit name: FooBar.cc\n"                             \
    "  CFun name: Foo\n"                                    \
    "---===[> Server respond:\n"                            \
    "[FunctionResponse]\n"                                  \
    "---===[> Client sent:\n"                               \
    "[BasicBlockRequest]\n"                                 \
    "  CUnit name: FooBar.cc\n"                             \
    "  CFun name: Foo\n"                                    \
    "  BB name: BB3\n"                                      \
    "---===[> Server respond:\n"                            \
    "[BasicBlockResponse]\n"                                \
    "---===[> Client sent:\n"                               \
    "[EdgeRequest]\n"                                       \
    "  Start BB: \n"                                        \
    "    | CUnit name: FooBar.cc\n"                         \
    "    | CFun name: Foo\n"                                \
    "    | BB name: BB2\n"                                  \
    "  End BB: \n"                                          \
    "    | CUnit name: FooBaz.cc\n"                         \
    "    | CFun name: Baz\n"                                \
    "    | BB name: BB5\n"                                  \
    "  Branch kind: EDGE_FALLBACK_BRANCH\n"                 \
    "---===[> Server respond:\n"                            \
    "[EdgeResponse]\n";

  CfgCollectionServicesClientServerTests()
  {
    m_osb = new std::ostream(&m_strbuf);
    m_osb_srv = new std::ostream(&m_strbuf_srv);
    m_service = new CfgCollectionServicesImpl(m_osb_srv);
    m_client = new CfgCollectionServicesClient(::grpc::CreateChannel(SERVER_ADDRESS,
                                                                     grpc::InsecureChannelCredentials()));
    m_builder.AddListeningPort(SERVER_ADDRESS, grpc::InsecureServerCredentials());
    m_builder.RegisterService((grpc::Service*)m_service);
  }

  virtual ~CfgCollectionServicesClientServerTests()
  {
    delete m_client;
    delete m_service;
    delete m_osb;    
  }

  virtual void SetUp(void)
  {
    m_server = m_builder.BuildAndStart();
    if ((m_pid = fork()) == 0)
      {
        (*m_osb) << "!! Server listening on " << SERVER_ADDRESS << " !" << std::endl;
        m_server->Wait();        
      }
  }

  virtual void TearDown(void)
  {
    m_server.release();
  }
};

TEST_F(CfgCollectionServicesClientServerTests, ClientServerOptimalTest)
{
  (*m_osb) << "**[ CompilationUnitStartService RPC test:" << std::endl;
  m_client->CompilationUnitStartService((*m_osb));
  
  (*m_osb) << "**[ CompilationUnitEndService RPC test:" << std::endl;
  m_client->CompilationUnitEndService((*m_osb));
  
  (*m_osb) << "**[ FunctionService RPC test:" << std::endl;
  m_client->FunctionService((*m_osb));
  
  (*m_osb) << "**[ BasicBlockService RPC test:" << std::endl;
  m_client->BasicBlockService((*m_osb));
  
  (*m_osb) << "**[ EdgeService RPC test:" << std::endl;
  m_client->EdgeService((*m_osb));
  
  EXPECT_STREQ(DUMPVAL_CLT.c_str(), m_strbuf.str().c_str());
  EXPECT_STREQ(DUMPVAL_SRV.c_str(), m_strbuf_srv.str().c_str());

  (*m_osb) << "**[ Shutdown server:" << std::endl;
  m_server->Shutdown();
  (*m_osb) << "**[ Server down!" << std::endl;
}

// Include Server & Client classes def for BuildMngtServices
#include "BuildMngtServicesClient.h"
#include "BuildMngtServices.h"

class BuildMngtServicesClientServerTests : public ::testing::Test
{
public:
  static constexpr const char * SERVER_ADDRESS = "localhost:50082";
  pid_t m_pid;
  ServerBuilder m_builder;
  BuildMngtServicesImpl *m_service;
  BuildMngtServicesClient *m_client;
  std::unique_ptr<Server> m_server;
  std::stringbuf m_strbuf;
  std::ostream *m_osb;
  std::stringbuf m_strbuf_srv;
  std::ostream *m_osb_srv;
  const std::string DUMPVAL_CLT = "**[ StartCfgCollectionService RPC test:\n" \
    "---===[> Client send:\n"                                           \
    "[StartCfgCollectionRequest]\n"                                     \
    "build name: gRPC test Client build\n"                              \
    "number cunits: 16\n"                                               \
    "cpad_config: <cpad_config></cpad_config>\n"                        \
    "---===[> Server responded:\n"                                      \
    "[StartCfgCollectionResponse]\n"                                    \
    "cpad config status: 1\n"                                           \
    "uuid: dbfa5367-edd4-4697-9009-403fd71b8fed\n"                      \
    "**[ EndCfgCollectionService RPC test:\n"                           \
    "---===[> Client send:\n"                                           \
    "[EndCfgCollectionRequest]\n"                                       \
    "uuid: 6e67755f-ef1b-4698-875b-5fa86d256c39\n"                      \
    "---===[> Server responded:\n"                                      \
    "[EndCfgCollectionResponse]\n"                                      \
    "apex allocation status: 1\n"                                       \
    "apex allocation message: APEX Allocated!\n"                        \
    "**[ StartCfgToolingService RPC test:\n"                            \
    "---===[> Client send:\n"                                           \
    "[StartCfgToolingRequest]\n"                                        \
    "uuid: 7235596a-9332-458c-b156-d6bdb673655e\n"                      \
    "---===[> Server responded:\n"                                      \
    "[StartCfgToolingResponse]\n"                                       \
    "**[ EndCfgToolingService RPC test:\n"                              \
    "---===[> Client send:\n"                                           \
    "[EndCfgToolingRequest]\n"                                          \
    "uuid: b71cc017-0647-47f0-b605-0eb7c1426cf1\n"                      \
    "---===[> Server responded:\n"                                      \
    "[EndCfgToolingResponse]\n"                                         \
    "statistics for BB 'BB1' is: \n"                                    \
    "   original length: 10\n"                                          \
    "   modified length: 15\n"                                          \
    "statistics for BB 'BB2' is: \n"                                    \
    "   original length: 12\n"                                          \
    "   modified length: 19\n"                                          \
    "statistics for BB 'BB3' is: \n"                                    \
    "   original length: 14\n"                                          \
    "   modified length: 17\n"                                          \
    "statistics for BB 'BB4' is: \n"                                    \
    "   original length: 34\n"                                          \
    "   modified length: 65\n"                                          \
    "";
  const std::string DUMPVAL_SRV = "---===[> Client sent:\n" \
    "[StartCfgCollectionRequest]\n"                         \
    "build name: gRPC test Client build\n"                  \
    "number cunits: 16\n"                                   \
    "cpad_config: <cpad_config></cpad_config>\n"            \
    "---===[> Server respond:\n"                            \
    "[StartCfgCollectionResponse]\n"                        \
    "cpad config status: 1\n"                               \
    "uuid: dbfa5367-edd4-4697-9009-403fd71b8fed\n"          \
    "---===[> Client sent:\n"                               \
    "[EndCfgCollectionRequest]\n"                           \
    "uuid: 6e67755f-ef1b-4698-875b-5fa86d256c39\n"          \
    "---===[> Server respond:\n"                            \
    "[EndCfgCollectionResponse]\n"                          \
    "apex allocation status: 1\n"                           \
    "apex allocation message: APEX Allocated!\n"            \
    "---===[> Client sent:\n"                               \
    "[StartCfgToolingRequest]\n"                            \
    "uuid: 7235596a-9332-458c-b156-d6bdb673655e\n"          \
    "---===[> Server respond:\n"                            \
    "[StartCfgToolingResponse]\n"                           \
    "---===[> Client sent:\n"                               \
    "[EndCfgToolingRequest]\n"                              \
    "uuid: b71cc017-0647-47f0-b605-0eb7c1426cf1\n"          \
    "---===[> Server respond:\n"                            \
    "[EndCfgToolingResponse]\n"                             \
    "statistics for BB 'BB1' is: \n"                        \
    "   original length: 10\n"                              \
    "   modified length: 15\n"                              \
    "statistics for BB 'BB2' is: \n"                        \
    "   original length: 12\n"                              \
    "   modified length: 19\n"                              \
    "statistics for BB 'BB3' is: \n"                        \
    "   original length: 14\n"                              \
    "   modified length: 17\n"                              \
    "statistics for BB 'BB4' is: \n"                        \
    "   original length: 34\n"                              \
    "   modified length: 65\n";


  BuildMngtServicesClientServerTests()
  {
    m_osb = new std::ostream(&m_strbuf);
    m_osb_srv = new std::ostream(&m_strbuf_srv);
    m_service = new BuildMngtServicesImpl(m_osb_srv);
    m_client = new BuildMngtServicesClient(::grpc::CreateChannel(SERVER_ADDRESS,
                                                                 grpc::InsecureChannelCredentials()));
    m_builder.AddListeningPort(SERVER_ADDRESS, grpc::InsecureServerCredentials());
    m_builder.RegisterService((grpc::Service*)m_service);
  }

  virtual ~BuildMngtServicesClientServerTests()
  {
  }

  virtual void SetUp(void)
  {
    m_server = m_builder.BuildAndStart();
    if ((m_pid = fork()) == 0)
      {
        (*m_osb) << "!! Server listening on " << SERVER_ADDRESS << " !" << std::endl;
        m_server->Wait();        
      }
  }

  virtual void TearDown(void)
  {
    m_server.release();
  }
};

TEST_F(BuildMngtServicesClientServerTests, ClientServerOptimalTest)
{
  (*m_osb) << "**[ StartCfgCollectionService RPC test:" << std::endl;
  m_client->StartCfgCollectionService((*m_osb));

  (*m_osb) << "**[ EndCfgCollectionService RPC test:" << std::endl;
  m_client->EndCfgCollectionService((*m_osb));
  
  (*m_osb) << "**[ StartCfgToolingService RPC test:" << std::endl;
  m_client->StartCfgToolingService((*m_osb));
  
  (*m_osb) << "**[ EndCfgToolingService RPC test:" << std::endl;
  m_client->EndCfgToolingService((*m_osb));
  
  EXPECT_STREQ(DUMPVAL_CLT.c_str(), m_strbuf.str().c_str());
  EXPECT_STREQ(DUMPVAL_SRV.c_str(), m_strbuf_srv.str().c_str());

  (*m_osb) << "**[ Shutdown server:" << std::endl;
  m_server->Shutdown();
  (*m_osb) << "**[ Server down!" << std::endl;
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

#endif /* SINGLE_TEST_EXE */
