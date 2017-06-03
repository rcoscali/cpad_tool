#include <iostream>     // std::cout, std::ostream, std::hex
#include <sstream>      // std::stringbuf
#include <string>       // std::string

#include <gtest/gtest.h>

#include "FunctionMsg.h"

class FunctionRequestTests : public ::testing::Test
{
public:
  char *buffer;
  ::cpad::cfg::FunctionRequestHelper *frh1;
  std::stringbuf strbuf;
  std::ostream *osb;
  std::string dumpval = "[FunctionRequest]\n"       \
    "  CUnit name: foobar.c\n"                      \
    "  CFun name: bar\n";

  FunctionRequestTests()
  {
    buffer = new char[128];
    memset(buffer, 0, 128);
    frh1 = new ::cpad::cfg::FunctionRequestHelper(std::string("foobar.c"),
                                                    std::string("bar"));
    osb = new std::ostream(&strbuf);
  }

  virtual ~FunctionRequestTests()
  {
    delete buffer;
    delete frh1;
  }

  virtual void SetUp(void)
  {
    frh1->serialize(buffer);    
  }

  virtual void TearDown(void)
  {
  }
};

TEST_F(FunctionRequestTests, DefaultConstructor)
{
  ::cpad::cfg::FunctionRequestHelper frh(std::string("foobar.c"),
                                           std::string("bar"));
  EXPECT_STREQ(frh.cunit_name().c_str(), "foobar.c");
  EXPECT_STREQ(frh.cfun_name().c_str(), "bar");
}

TEST_F(FunctionRequestTests, DeserializeConstructor)
{
  ::cpad::cfg::FunctionRequestHelper frh2(buffer);
  EXPECT_STREQ(frh1->cunit_name().c_str(), "foobar.c");
  EXPECT_STREQ(frh1->cfun_name().c_str(), "bar");
}

TEST_F(FunctionRequestTests, DeserializeConstructorFromEmptyString)
{
  ::cpad::cfg::FunctionRequestHelper frh2("");
  EXPECT_STREQ(frh2.cunit_name().c_str(), "");
  EXPECT_STREQ(frh2.cfun_name().c_str(), "");
}

TEST_F(FunctionRequestTests, CopyConstructor)
{
  ::cpad::cfg::FunctionRequestHelper frh2(*frh1);
  EXPECT_STREQ(frh2.cunit_name().c_str(), frh1->cunit_name().c_str());
  EXPECT_STREQ(frh2.cfun_name().c_str(), frh1->cfun_name().c_str());
}

TEST_F(FunctionRequestTests, SerializeMethod)
{
  ::cpad::cfg::FunctionRequestHelper frh(std::string("foobar.c"),
                                           std::string("bar"));
  char local_buffer[128];
  memset(local_buffer, 0, 128);
  frh.serialize(local_buffer);    
  EXPECT_TRUE(memcmp(buffer, local_buffer, 128) == 0);
}

TEST_F(FunctionRequestTests, DumpMethod)
{
  frh1->dump(*osb);
  EXPECT_STREQ(dumpval.c_str(), strbuf.str().c_str());
}

#ifndef SINGLE_TEST_EXE
int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
#endif
