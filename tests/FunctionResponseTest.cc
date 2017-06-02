#include <iostream>     // std::cout, std::ostream, std::hex
#include <sstream>      // std::stringbuf
#include <string>       // std::string

#include <gtest/gtest.h>

#include "FunctionMsg.h"

class FunctionResponseTests : public ::testing::Test
{
public:
  char *buffer;
  ::cpad::cfg::FunctionResponseHelper *cusrh1;
  std::stringbuf strbuf;
  std::ostream *osb;
  std::string dumpval = "[FunctionResponse]\n"       \
    "CUnit filename: foobar.c\n";

  FunctionResponseTests()
  {
    buffer = new char[128];
    memset(buffer, 0, 128);
    cusrh1 = new ::cpad::cfg::FunctionResponseHelper(std::string("foobar.c"));
    osb = new std::ostream(&strbuf);
  }

  virtual ~FunctionResponseTests()
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

TEST_F(FunctionResponseTests, DefaultConstructor)
{
  ::cpad::cfg::FunctionResponseHelper cusrh(std::string("foobar.c"));
  EXPECT_STREQ(cusrh.filename().c_str(), "foobar.c");
}

TEST_F(FunctionResponseTests, DeserializeConstructor)
{
  ::cpad::cfg::FunctionResponseHelper cusrh2(buffer);
  EXPECT_STREQ(cusrh1->filename().c_str(), "foobar.c");
}

TEST_F(FunctionResponseTests, DeserializeConstructorFromEmptyString)
{
  ::cpad::cfg::FunctionResponseHelper cusrh2("");
  EXPECT_STREQ(cusrh2.filename().c_str(), "");
}

TEST_F(FunctionResponseTests, CopyConstructor)
{
  ::cpad::cfg::FunctionResponseHelper cusrh2(*cusrh1);
  EXPECT_STREQ(cusrh2.filename().c_str(), cusrh1->filename().c_str());
}

TEST_F(FunctionResponseTests, SerializeMethod)
{
  ::cpad::cfg::FunctionResponseHelper cusrh(std::string("foobar.c"));
  char local_buffer[128];
  memset(local_buffer, 0, 128);
  cusrh.serialize(local_buffer);    
  EXPECT_TRUE(memcmp(buffer, local_buffer, 128) == 0);
}

TEST_F(FunctionResponseTests, DumpMethod)
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
