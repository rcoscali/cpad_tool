#include <iostream>     // std::cout, std::ostream, std::hex
#include <sstream>      // std::stringbuf
#include <string>       // std::string

#include <gtest/gtest.h>

#include "BuildMngtMsg.h"

class StartCfgCollectionResponseTests : public ::testing::Test
{
public:
  char *buffer;
  ::cpad::build_mngt::StartCfgCollectionResponseHelper *sccrh1;
  std::stringbuf strbuf;
  std::ostream *osb;
  std::string dumpval = "[StartCfgCollectionResponse]\n"       \
    "cpad config status: 1\n"                                  \
    "uuid: 800c0df3-9fd5-4662-85e4-937d6fd67ff2\n";
  
  StartCfgCollectionResponseTests()
  {
    buffer = new char[128];
    bzero(buffer, 128);
    sccrh1 = new ::cpad::build_mngt::StartCfgCollectionResponseHelper(cpad::build_mngt::StartCfgCollectionResponse::CPAD_CONFIG_OK,
                                                                      std::string("800c0df3-9fd5-4662-85e4-937d6fd67ff2"));
    osb = new std::ostream(&strbuf);
  }

  virtual ~StartCfgCollectionResponseTests()
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

TEST_F(StartCfgCollectionResponseTests, DefaultConstructor)
{
  ::cpad::build_mngt::StartCfgCollectionResponseHelper sccrh(cpad::build_mngt::StartCfgCollectionResponse::CPAD_CONFIG_OK,
                                                             std::string("800c0df3-9fd5-4662-85e4-937d6fd67ff2"));
  EXPECT_EQ(sccrh.cpad_config_status(), cpad::build_mngt::StartCfgCollectionResponse::CPAD_CONFIG_OK);
  EXPECT_STREQ(sccrh.uuid().c_str(), "800c0df3-9fd5-4662-85e4-937d6fd67ff2");
}

TEST_F(StartCfgCollectionResponseTests, DeserializeConstructor)
{
  ::cpad::build_mngt::StartCfgCollectionResponseHelper sccrh2(buffer);
  EXPECT_EQ(sccrh2.cpad_config_status(), cpad::build_mngt::StartCfgCollectionResponse::CPAD_CONFIG_OK);
  EXPECT_STREQ(sccrh2.uuid().c_str(), "800c0df3-9fd5-4662-85e4-937d6fd67ff2");
}

TEST_F(StartCfgCollectionResponseTests, DeserializeConstructorFromEmptyString)
{
  ::cpad::build_mngt::StartCfgCollectionResponseHelper sccrh2("");
  EXPECT_EQ(sccrh2.cpad_config_status(), 0);
  EXPECT_TRUE(cpad::build_mngt::StartCfgCollectionResponse::CpadConfigStatus_IsValid(sccrh2.cpad_config_status()));
  EXPECT_STREQ(sccrh2.uuid().c_str(), "");
}

TEST_F(StartCfgCollectionResponseTests, CopyConstructor)
{
  ::cpad::build_mngt::StartCfgCollectionResponseHelper sccrh2(*sccrh1);
  EXPECT_EQ(sccrh2.cpad_config_status(), sccrh1->cpad_config_status());
  EXPECT_STREQ(sccrh2.uuid().c_str(), sccrh1->uuid().c_str());
}

TEST_F(StartCfgCollectionResponseTests, SerializeMethod)
{
  ::cpad::build_mngt::StartCfgCollectionResponseHelper sccrh(cpad::build_mngt::StartCfgCollectionResponse::CPAD_CONFIG_OK,
                                                             std::string("800c0df3-9fd5-4662-85e4-937d6fd67ff2"));
  char local_buffer[128];
  bzero(local_buffer, 128);
  sccrh.serialize(local_buffer);    
  EXPECT_TRUE(memcmp(buffer, local_buffer, 128) == 0);
}

TEST_F(StartCfgCollectionResponseTests, DumpMethod)
{
  sccrh1->dump(*osb);
  EXPECT_STREQ(dumpval.c_str(), strbuf.str().c_str());
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
