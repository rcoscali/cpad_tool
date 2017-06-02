#include <iostream>     // std::cout, std::ostream, std::hex
#include <sstream>      // std::stringbuf
#include <string>       // std::string

#include <gtest/gtest.h>

#include "BasicBlockMsg.h"

class BasicBlockRequestTests : public ::testing::Test
{
public:
  char *buffer;
  ::cpad::cfg::BasicBlockRequestHelper *cusrh1;
  std::stringbuf strbuf;
  std::ostream *osb;
  std::string dumpval = "[BasicBlockRequest]\n"       \
    "CUnit filename: foobar.c\n";

  BasicBlockRequestTests()
  {
    buffer = new char[128];
    memset(buffer, 0, 128);
    cusrh1 = new ::cpad::cfg::BasicBlockRequestHelper(std::string("foobar.c"));
    osb = new std::ostream(&strbuf);
  }

  virtual ~BasicBlockRequestTests()
  {
    delete buffer;
    delete cusrh1;
  }

  virtual void SetUp(void)
  {
    cusrh1->serialize(buffer);    
  }

  virtual void TearDown(void)
  {
  }
};

TEST_F(BasicBlockRequestTests, DefaultConstructor)
{
  ::cpad::cfg::BasicBlockRequestHelper cusrh(std::string("foobar.c"));
  EXPECT_STREQ(cusrh.filename().c_str(), "foobar.c");
}

TEST_F(BasicBlockRequestTests, DeserializeConstructor)
{
  ::cpad::cfg::BasicBlockRequestHelper cusrh2(buffer);
  EXPECT_STREQ(cusrh1->filename().c_str(), "foobar.c");
}

TEST_F(BasicBlockRequestTests, DeserializeConstructorFromEmptyString)
{
  ::cpad::cfg::BasicBlockRequestHelper cusrh2("");
  EXPECT_STREQ(cusrh2.filename().c_str(), "");
}

TEST_F(BasicBlockRequestTests, CopyConstructor)
{
  ::cpad::cfg::BasicBlockRequestHelper cusrh2(*cusrh1);
  EXPECT_STREQ(cusrh2.filename().c_str(), cusrh1->filename().c_str());
}

TEST_F(BasicBlockRequestTests, SerializeMethod)
{
  ::cpad::cfg::BasicBlockRequestHelper cusrh(std::string("foobar.c"));
  char local_buffer[128];
  memset(local_buffer, 0, 128);
  cusrh.serialize(local_buffer);    
  EXPECT_TRUE(memcmp(buffer, local_buffer, 128) == 0);
}

TEST_F(BasicBlockRequestTests, DumpMethod)
{
  cusrh1->dump(*osb);
  EXPECT_STREQ(dumpval.c_str(), strbuf.str().c_str());
}

#ifndef SINGLE_TEST_EXE
int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
#endif
