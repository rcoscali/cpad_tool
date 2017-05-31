#include <iostream>     // std::cout, std::ostream, std::hex
#include <sstream>      // std::stringbuf
#include <string>       // std::string

#include <gtest/gtest.h>

#include "VersionMsg.h"

class VersionResponseTests : public ::testing::Test
{
public:
  char *buffer;
  ::cpad::insns::VersionResponseHelper *vrh1;
  std::stringbuf strbuf;
  std::ostream *osb;
  std::string dumpval = "[VersionResponseHelper]\n" \
    "server minor: 2\n"                            \
    "server major: 4\n"                            \
    "server provider: testConstructor\n";

  VersionResponseTests()
  {
    buffer = new char[128];
    bzero(buffer, 128);
    vrh1 = new ::cpad::insns::VersionResponseHelper(2, 4, "testConstructor");
    osb = new std::ostream(&strbuf);
  }

  virtual ~VersionResponseTests()
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

TEST_F(VersionResponseTests, DefaultConstructor)
{
  ::cpad::insns::VersionResponseHelper vrh(1, 2, "testDefaultConstructor");
  EXPECT_EQ(vrh.server_version_minor(), 1);
  EXPECT_EQ(vrh.server_version_major(), 2);
  EXPECT_STREQ(vrh.server_provider_name().c_str(), "testDefaultConstructor");
}

TEST_F(VersionResponseTests, DeserializeConstructor)
{
  ::cpad::insns::VersionResponseHelper vrh2(buffer);
  EXPECT_EQ(vrh1->server_version_minor(), vrh2.server_version_minor());
  EXPECT_EQ(vrh1->server_version_major(), vrh2.server_version_major());
  EXPECT_STREQ(vrh1->server_provider_name().c_str(), vrh2.server_provider_name().c_str());  
}

TEST_F(VersionResponseTests, DeserializeConstructorFromEmptyString)
{
  ::cpad::insns::VersionResponseHelper vrh2("");
  EXPECT_EQ(vrh2.server_version_minor(), 0);
  EXPECT_EQ(vrh2.server_version_major(), 0);
  EXPECT_STREQ(vrh2.server_provider_name().c_str(), "");    
}

TEST_F(VersionResponseTests, CopyConstructor)
{
  ::cpad::insns::VersionResponseHelper vrh2(*vrh1);
  EXPECT_EQ(vrh1->server_version_minor(), vrh2.server_version_minor());
  EXPECT_EQ(vrh1->server_version_major(), vrh2.server_version_major());
  EXPECT_STREQ(vrh1->server_provider_name().c_str(), vrh2.server_provider_name().c_str()); 
}

TEST_F(VersionResponseTests, SerializeMethod)
{
  ::cpad::insns::VersionResponseHelper vrh(2, 4, "testConstructor");
  char local_buffer[128];
  bzero(local_buffer, 128);
  vrh.serialize(local_buffer);    
  EXPECT_TRUE(memcmp(buffer, local_buffer, 128) == 0);
}

TEST_F(VersionResponseTests, DumpMethod)
{
  vrh1->dump(*osb);
  EXPECT_STREQ(dumpval.c_str(), strbuf.str().c_str());
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
