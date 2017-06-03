#include <iostream>     // std::cout, std::ostream, std::hex
#include <sstream>      // std::stringbuf
#include <string>       // std::string

#include <gtest/gtest.h>

#include "BasicBlockMsg.h"

class BasicBlockRequestTests : public ::testing::Test
{
public:
  char *buffer;
  ::cpad::cfg::BasicBlockRequestHelper *bbrh1;
  std::stringbuf strbuf;
  std::ostream *osb;
  std::string dumpval = "[BasicBlockRequest]\n" \
    "  CUnit name: foobar.c\n"                  \
    "  CFun name: bar\n"                        \
    "  BB name: BB1\n";

  BasicBlockRequestTests()
  {
    buffer = new char[128];
    memset(buffer, 0, 128);
    bbrh1 = new ::cpad::cfg::BasicBlockRequestHelper(std::string("foobar.c"),
                                                      std::string("bar"),
                                                      std::string("BB1"));
    osb = new std::ostream(&strbuf);
  }

  virtual ~BasicBlockRequestTests()
  {
    delete buffer;
    delete bbrh1;
  }

  virtual void SetUp(void)
  {
    bbrh1->serialize(buffer);    
  }

  virtual void TearDown(void)
  {
  }
};

TEST_F(BasicBlockRequestTests, DefaultConstructor)
{
  ::cpad::cfg::BasicBlockRequestHelper bbrh(std::string("foobar.c"),
                                             std::string("bar"),
                                             std::string("BB1"));
  EXPECT_STREQ(bbrh.cunit_name().c_str(), "foobar.c");
  EXPECT_STREQ(bbrh.cfun_name().c_str(), "bar");
  EXPECT_STREQ(bbrh.bb_name().c_str(), "BB1");
}

TEST_F(BasicBlockRequestTests, DeserializeConstructor)
{
  ::cpad::cfg::BasicBlockRequestHelper bbrh2(buffer);
  EXPECT_STREQ(bbrh1->cunit_name().c_str(), "foobar.c");
  EXPECT_STREQ(bbrh1->cfun_name().c_str(), "bar");
  EXPECT_STREQ(bbrh1->bb_name().c_str(), "BB1");
}

TEST_F(BasicBlockRequestTests, DeserializeConstructorFromEmptyString)
{
  ::cpad::cfg::BasicBlockRequestHelper bbrh2("");
  EXPECT_STREQ(bbrh2.cunit_name().c_str(), "");
  EXPECT_STREQ(bbrh2.cfun_name().c_str(), "");
  EXPECT_STREQ(bbrh2.bb_name().c_str(), "");
}

TEST_F(BasicBlockRequestTests, CopyConstructor)
{
  ::cpad::cfg::BasicBlockRequestHelper bbrh2(*bbrh1);
  EXPECT_STREQ(bbrh2.cunit_name().c_str(), bbrh1->cunit_name().c_str());
  EXPECT_STREQ(bbrh2.cfun_name().c_str(), bbrh1->cfun_name().c_str());
  EXPECT_STREQ(bbrh2.bb_name().c_str(), bbrh1->bb_name().c_str());
}

TEST_F(BasicBlockRequestTests, SerializeMethod)
{
  ::cpad::cfg::BasicBlockRequestHelper bbrh(std::string("foobar.c"),
                                             std::string("bar"),
                                             std::string("BB1"));
  char local_buffer[128];
  memset(local_buffer, 0, 128);
  bbrh.serialize(local_buffer);    
  EXPECT_TRUE(memcmp(buffer, local_buffer, 128) == 0);
}

TEST_F(BasicBlockRequestTests, DumpMethod)
{
  bbrh1->dump(*osb);
  EXPECT_STREQ(dumpval.c_str(), strbuf.str().c_str());
}

#ifndef SINGLE_TEST_EXE
int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
#endif
