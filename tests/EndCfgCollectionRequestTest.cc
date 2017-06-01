#include <iostream>     // std::cout, std::ostream, std::hex
#include <sstream>      // std::stringbuf
#include <string>       // std::string

#include <gtest/gtest.h>

#include "BuildMngtMsg.h"

class EndCfgCollectionRequestTests : public ::testing::Test
{
public:
  char *buffer;
  ::cpad::build_mngt::EndCfgCollectionRequestHelper *sccrh1;
  std::stringbuf strbuf;
  std::ostream *osb;
  std::string dumpval = "[EndCfgCollectionRequest]\n"       \
    "uuid: 800c0df3-9fd5-4662-85e4-937d6fd67ff2\n";
  
  EndCfgCollectionRequestTests()
  {
    buffer = new char[128];
    memset(buffer, 0, 128);
    sccrh1 = new ::cpad::build_mngt::EndCfgCollectionRequestHelper(std::string("800c0df3-9fd5-4662-85e4-937d6fd67ff2"));
    osb = new std::ostream(&strbuf);
  }

  virtual ~EndCfgCollectionRequestTests()
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

TEST_F(EndCfgCollectionRequestTests, DefaultConstructor)
{
  ::cpad::build_mngt::EndCfgCollectionRequestHelper sccrh(std::string("800c0df3-9fd5-4662-85e4-937d6fd67ff2"));
  EXPECT_STREQ(sccrh.uuid().c_str(), "800c0df3-9fd5-4662-85e4-937d6fd67ff2");
}

TEST_F(EndCfgCollectionRequestTests, DeserializeConstructor)
{
  ::cpad::build_mngt::EndCfgCollectionRequestHelper sccrh2(buffer);
  EXPECT_STREQ(sccrh2.uuid().c_str(), "800c0df3-9fd5-4662-85e4-937d6fd67ff2");
}

TEST_F(EndCfgCollectionRequestTests, DeserializeConstructorFromEmptyString)
{
  ::cpad::build_mngt::EndCfgCollectionRequestHelper sccrh2("");
  EXPECT_STREQ(sccrh2.uuid().c_str(), "");
}

TEST_F(EndCfgCollectionRequestTests, CopyConstructor)
{
  ::cpad::build_mngt::EndCfgCollectionRequestHelper sccrh2(*sccrh1);
  EXPECT_STREQ(sccrh2.uuid().c_str(), sccrh1->uuid().c_str());
}

TEST_F(EndCfgCollectionRequestTests, SerializeMethod)
{
  ::cpad::build_mngt::EndCfgCollectionRequestHelper sccrh(std::string("800c0df3-9fd5-4662-85e4-937d6fd67ff2"));
  char local_buffer[128];
  memset(local_buffer, 0, 128);
  sccrh.serialize(local_buffer);    
  EXPECT_TRUE(memcmp(buffer, local_buffer, 128) == 0);
}

TEST_F(EndCfgCollectionRequestTests, DumpMethod)
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
