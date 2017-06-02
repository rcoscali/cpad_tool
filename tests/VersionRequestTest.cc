#include <iostream>     // std::cout, std::ostream, std::hex
#include <sstream>      // std::stringbuf
#include <string>       // std::string

#include <gtest/gtest.h>

#include "VersionMsg.h"

class VersionRequestTests : public ::testing::Test
{
public:
  char *buffer;
  ::cpad::insns::VersionRequestHelper *vrh1;
  std::stringbuf strbuf;
  std::ostream *osb;
  std::string dumpval = "[VersionRequest]\n"       \
    "client minor: 2\n"                            \
    "client major: 4\n"                            \
    "client provider: testConstructor\n";

  VersionRequestTests()
  {
    buffer = new char[128];
    memset(buffer, 0, 128);
    vrh1 = new ::cpad::insns::VersionRequestHelper(2, 4, "testConstructor");
    osb = new std::ostream(&strbuf);
  }

  virtual ~VersionRequestTests()
  {
    delete buffer;
    delete vrh1;
  }

  virtual void SetUp(void)
  {
    vrh1->serialize(buffer);    
  }

  virtual void TearDown(void)
  {
  }
};

TEST_F(VersionRequestTests, DefaultConstructor)
{
  ::cpad::insns::VersionRequestHelper vrh(1, 2, "testDefaultConstructor");
  EXPECT_EQ(vrh.client_version_minor(), 1);
  EXPECT_EQ(vrh.client_version_major(), 2);
  EXPECT_STREQ(vrh.client_provider_name().c_str(), "testDefaultConstructor");
}

TEST_F(VersionRequestTests, DeserializeConstructor)
{
  ::cpad::insns::VersionRequestHelper vrh2(buffer);
  EXPECT_EQ(vrh1->client_version_minor(), vrh2.client_version_minor());
  EXPECT_EQ(vrh1->client_version_major(), vrh2.client_version_major());
  EXPECT_STREQ(vrh1->client_provider_name().c_str(), vrh2.client_provider_name().c_str());  
}

TEST_F(VersionRequestTests, DeserializeConstructorFromEmptyString)
{
  ::cpad::insns::VersionRequestHelper vrh2("");
  EXPECT_EQ(vrh2.client_version_minor(), 0);
  EXPECT_EQ(vrh2.client_version_major(), 0);
  EXPECT_STREQ(vrh2.client_provider_name().c_str(), "");    
}

TEST_F(VersionRequestTests, CopyConstructor)
{
  ::cpad::insns::VersionRequestHelper vrh2(*vrh1);
  EXPECT_EQ(vrh1->client_version_minor(), vrh2.client_version_minor());
  EXPECT_EQ(vrh1->client_version_major(), vrh2.client_version_major());
  EXPECT_STREQ(vrh1->client_provider_name().c_str(), vrh2.client_provider_name().c_str());  
}

TEST_F(VersionRequestTests, SerializeMethod)
{
  ::cpad::insns::VersionRequestHelper vrh(2, 4, "testConstructor");
  char local_buffer[128];
  memset(local_buffer, 0, 128);
  vrh.serialize(local_buffer);    
  EXPECT_TRUE(memcmp(buffer, local_buffer, 128) == 0);
}

TEST_F(VersionRequestTests, DumpMethod)
{
  vrh1->dump(*osb);
  EXPECT_STREQ(dumpval.c_str(), strbuf.str().c_str());
}

#ifndef SINGLE_TEST_EXE
int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
#endif
