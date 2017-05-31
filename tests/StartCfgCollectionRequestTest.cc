#include <iostream>     // std::cout, std::ostream, std::hex
#include <sstream>      // std::stringbuf
#include <string>       // std::string

#include <gtest/gtest.h>

#include "BuildMngtMsg.h"

class StartCfgCollectionRequestTests : public ::testing::Test
{
public:
  char *buffer;
  ::cpad::build_mngt::StartCfgCollectionRequestHelper *sccrh1;
  std::stringbuf strbuf;
  std::ostream *osb;
  std::string dumpval = "[StartCfgCollectionRequest]\n"       \
    "build name: abuild\n" \
    "number cunits: 10\n" \
    "cpad_config: <cpad_config></cpad_config>\n";
  
  StartCfgCollectionRequestTests()
  {
    buffer = new char[128];
    bzero(buffer, 128);
    sccrh1 = new ::cpad::build_mngt::StartCfgCollectionRequestHelper(std::string("abuild"),
                                                                     10,
                                                                     std::string("<cpad_config></cpad_config>"));
    osb = new std::ostream(&strbuf);
  }

  virtual ~StartCfgCollectionRequestTests()
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

TEST_F(StartCfgCollectionRequestTests, DefaultConstructor)
{
  ::cpad::build_mngt::StartCfgCollectionRequestHelper sccrh(std::string("abuild"),
                                                            10,
                                                            std::string("<cpad_config></cpad_config>"));
  EXPECT_STREQ(sccrh.build_name().c_str(), "abuild");
  EXPECT_EQ(sccrh.number_cunits(), 10);
  EXPECT_STREQ(sccrh.cpad_config().c_str(), "<cpad_config></cpad_config>");
}

TEST_F(StartCfgCollectionRequestTests, DeserializeConstructor)
{
  ::cpad::build_mngt::StartCfgCollectionRequestHelper sccrh2(buffer);
  EXPECT_STREQ(sccrh2.build_name().c_str(), "abuild");
  EXPECT_EQ(sccrh2.number_cunits(), 10);
  EXPECT_STREQ(sccrh2.cpad_config().c_str(), "<cpad_config></cpad_config>");
}

TEST_F(StartCfgCollectionRequestTests, DeserializeConstructorFromEmptyString)
{
  ::cpad::build_mngt::StartCfgCollectionRequestHelper sccrh2("");
  EXPECT_STREQ(sccrh2.build_name().c_str(), "");
  EXPECT_EQ(sccrh2.number_cunits(), 0);
  EXPECT_STREQ(sccrh2.cpad_config().c_str(), "");
}

TEST_F(StartCfgCollectionRequestTests, CopyConstructor)
{
  ::cpad::build_mngt::StartCfgCollectionRequestHelper sccrh2(*sccrh1);
  EXPECT_STREQ(sccrh2.build_name().c_str(), sccrh1->build_name().c_str());
  EXPECT_EQ(sccrh2.number_cunits(), sccrh1->number_cunits());
  EXPECT_STREQ(sccrh2.cpad_config().c_str(), sccrh1->cpad_config().c_str());
}

TEST_F(StartCfgCollectionRequestTests, SerializeMethod)
{
  ::cpad::build_mngt::StartCfgCollectionRequestHelper sccrh(std::string("abuild"),
                                                            10,
                                                            std::string("<cpad_config></cpad_config>"));
  char local_buffer[128];
  bzero(local_buffer, 128);
  sccrh.serialize(local_buffer);    
  EXPECT_TRUE(memcmp(buffer, local_buffer, 128) == 0);
}

TEST_F(StartCfgCollectionRequestTests, DumpMethod)
{
  sccrh1->dump(*osb);
  EXPECT_STREQ(dumpval.c_str(), strbuf.str().c_str());
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
