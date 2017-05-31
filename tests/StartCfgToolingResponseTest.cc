#include <iostream>     // std::cout, std::ostream, std::hex
#include <sstream>      // std::stringbuf
#include <string>       // std::string

#include <gtest/gtest.h>

#include "BuildMngtMsg.h"

class StartCfgToolingResponseTests : public ::testing::Test
{
public:
  char *buffer;
  ::cpad::build_mngt::StartCfgToolingResponseHelper *sctrh1;
  std::stringbuf strbuf;
  std::ostream *osb;
  std::string dumpval = "[StartCfgToolingResponse]\n";
  
  StartCfgToolingResponseTests()
  {
    buffer = new char[128];
    bzero(buffer, 128);
    sctrh1 = new ::cpad::build_mngt::StartCfgToolingResponseHelper();
    osb = new std::ostream(&strbuf);
  }

  virtual ~StartCfgToolingResponseTests()
  {
    delete buffer;
    delete sctrh1;
  }

  virtual void SetUp(void)
  {
    sctrh1->serialize(buffer);    
  }

  virtual void TearDown(void)
  {
  }
};


// TEST_F(StartCfgToolingResponseTests, SerializeMethod)
// {
//   ::cpad::build_mngt::StartCfgToolingResponseHelper sctrh();
//   char local_buffer[128];
//   bzero(local_buffer, 128);
//   sctrh.serialize(local_buffer);    
//   EXPECT_TRUE(memcmp(buffer, local_buffer, 128) == 0);
// }

TEST_F(StartCfgToolingResponseTests, DumpMethod)
{
  sctrh1->dump(*osb);
  EXPECT_STREQ(dumpval.c_str(), strbuf.str().c_str());
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
