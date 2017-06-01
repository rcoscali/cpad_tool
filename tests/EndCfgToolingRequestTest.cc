#include <iostream>     // std::cout, std::ostream, std::hex
#include <sstream>      // std::stringbuf
#include <string>       // std::string

#include <gtest/gtest.h>

#include "BuildMngtMsg.h"

#define TEST_UUID_VALUE  "800c0df3-9fd5-4662-85e4-937d6fd67ff2"

class EndCfgToolingRequestTests : public ::testing::Test
{
public:
  char *buffer;
  ::cpad::build_mngt::EndCfgToolingRequestHelper *sccrh1;
  std::stringbuf strbuf;
  std::ostream *osb;
  std::string dumpval = "[EndCfgToolingRequest]\n"       \
    "uuid: " TEST_UUID_VALUE "\n";
  
  EndCfgToolingRequestTests()
  {
    buffer = new char[128];
    memset(buffer, 0, 128);
    sccrh1 = new ::cpad::build_mngt::EndCfgToolingRequestHelper(std::string(TEST_UUID_VALUE));
    osb = new std::ostream(&strbuf);
  }

  virtual ~EndCfgToolingRequestTests()
  {
    delete buffer;
    delete sccrh1;
  }

  virtual void SetUp(void)
  {
    sccrh1->serialize(buffer);    
  }

  virtual void TearDown(void)
  {
  }
};

TEST_F(EndCfgToolingRequestTests, DefaultConstructor)
{
  ::cpad::build_mngt::EndCfgToolingRequestHelper sccrh(std::string(TEST_UUID_VALUE));
  EXPECT_STREQ(sccrh.uuid().c_str(), TEST_UUID_VALUE);
}

TEST_F(EndCfgToolingRequestTests, DeserializeConstructor)
{
  ::cpad::build_mngt::EndCfgToolingRequestHelper sccrh2(buffer);
  EXPECT_STREQ(sccrh2.uuid().c_str(), TEST_UUID_VALUE);
}

TEST_F(EndCfgToolingRequestTests, DeserializeConstructorFromEmptyString)
{
  ::cpad::build_mngt::EndCfgToolingRequestHelper sccrh2("");
  EXPECT_STREQ(sccrh2.uuid().c_str(), "");
}

TEST_F(EndCfgToolingRequestTests, CopyConstructor)
{
  ::cpad::build_mngt::EndCfgToolingRequestHelper sccrh2(*sccrh1);
  EXPECT_STREQ(sccrh2.uuid().c_str(), sccrh1->uuid().c_str());
}

TEST_F(EndCfgToolingRequestTests, SerializeMethod)
{
  ::cpad::build_mngt::EndCfgToolingRequestHelper sccrh(std::string(TEST_UUID_VALUE));
  char local_buffer[128];
  memset(local_buffer, 0, 128);
  sccrh.serialize(local_buffer);    
  EXPECT_TRUE(memcmp(buffer, local_buffer, 128) == 0);
}

TEST_F(EndCfgToolingRequestTests, DumpMethod)
{
  sccrh1->dump(*osb);
  EXPECT_STREQ(dumpval.c_str(), strbuf.str().c_str());
}

#ifndef SINGLE_TEST_EXE
int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
#endif
