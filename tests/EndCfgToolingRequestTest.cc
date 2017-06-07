#include <iostream>     // std::cout, std::ostream, std::hex
#include <sstream>      // std::stringbuf
#include <string>       // std::string

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/string_generator.hpp>

#include <gtest/gtest.h>

#include "BuildMngtMsg.h"

#define TEST_UUID_VALUE  { 0x80, 0x0c, 0x0d, 0xf3, 0x9f, 0xd5, 0x46, 0x62, 0x85, 0xe4, 0x93, 0x7d, 0x6f, 0xd6, 0x7f, 0xf2 }
#define TEST_UUID_STR "800c0df3-9fd5-4662-85e4-937d6fd67ff2"

class EndCfgToolingRequestTests : public ::testing::Test
{
public:
  static constexpr const boost::uuids::uuid& u = TEST_UUID_VALUE;
  char *buffer;
  ::cpad::build_mngt::EndCfgToolingRequestHelper *sccrh1;
  std::stringbuf strbuf;
  std::ostream *osb;
  std::string dumpval = "[EndCfgToolingRequest]\n"       \
    "uuid: 800c0df3-9fd5-4662-85e4-937d6fd67ff2\n";
  
  EndCfgToolingRequestTests()
  {
    buffer = new char[128];
    memset(buffer, 0, 128);
    sccrh1 = new ::cpad::build_mngt::EndCfgToolingRequestHelper(to_string(u));
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
  ::cpad::build_mngt::EndCfgToolingRequestHelper sccrh(to_string(u));
  EXPECT_STREQ(sccrh.uuid().c_str(), TEST_UUID_STR);
}

TEST_F(EndCfgToolingRequestTests, DeserializeConstructor)
{
  ::cpad::build_mngt::EndCfgToolingRequestHelper sccrh2(buffer);
  EXPECT_STREQ(sccrh2.uuid().c_str(), TEST_UUID_STR);
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
  ::cpad::build_mngt::EndCfgToolingRequestHelper sccrh(to_string(u));
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
