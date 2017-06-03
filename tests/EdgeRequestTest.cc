#include <iostream>     // std::cout, std::ostream, std::hex
#include <sstream>      // std::stringbuf
#include <string>       // std::string

#include <gtest/gtest.h>

#include "EdgeMsg.h"

class EdgeRequestTests : public ::testing::Test
{
public:
  char *buffer;
  ::cpad::cfg::EdgeRequestHelper *erh1;
  std::stringbuf strbuf;
  std::ostream *osb;
  std::string dumpval = "[EdgeRequest]\n"       \
    "  Start BB: \n"                            \
    "    | CUnit name: foobar.c\n"              \
    "    | CFun name: bar\n"                    \
    "    | BB name: BB1\n"                      \
    "  End BB: \n"                              \
    "    | CUnit name: foobaz.c\n"              \
    "    | CFun name: baz\n"                    \
    "    | BB name: BB2\n"                      \
    "  Branch kind: EDGE_FALLBACK_BRANCH\n";
  
  EdgeRequestTests()
  {
    buffer = new char[128];
    memset(buffer, 0, 128);
    erh1 = new ::cpad::cfg::EdgeRequestHelper(std::string("foobar.c"), std::string("bar"), std::string("BB1"),
                                                std::string("foobaz.c"), std::string("baz"), std::string("BB2"),
                                                cpad::cfg::EDGE_FALLBACK_BRANCH);
    osb = new std::ostream(&strbuf);
  }

  virtual ~EdgeRequestTests()
  {
    delete buffer;
    delete erh1;
  }

  virtual void SetUp(void)
  {
    erh1->serialize(buffer);    
  }

  virtual void TearDown(void)
  {
  }
};

TEST_F(EdgeRequestTests, DefaultConstructor)
{
  ::cpad::cfg::EdgeRequestHelper erh(std::string("foobar.c"), std::string("bar"), std::string("BB1"),
                                       std::string("foobaz.c"), std::string("baz"), std::string("BB2"),
                                       cpad::cfg::EDGE_FALLBACK_BRANCH);
  EXPECT_STREQ(erh.start_cunit_name().c_str(), "foobar.c");
  EXPECT_STREQ(erh.start_cfun_name().c_str(), "bar");
  EXPECT_STREQ(erh.start_bb_name().c_str(), "BB1");
  EXPECT_STREQ(erh.end_cunit_name().c_str(), "foobaz.c");
  EXPECT_STREQ(erh.end_cfun_name().c_str(), "baz");
  EXPECT_STREQ(erh.end_bb_name().c_str(), "BB2");
  EXPECT_EQ(erh.edge_branch(), cpad::cfg::EDGE_FALLBACK_BRANCH);
}

TEST_F(EdgeRequestTests, DeserializeConstructor)
{
  ::cpad::cfg::EdgeRequestHelper erh2(buffer);
  EXPECT_STREQ(erh1->start_cunit_name().c_str(), "foobar.c");
  EXPECT_STREQ(erh1->start_cfun_name().c_str(), "bar");
  EXPECT_STREQ(erh1->start_bb_name().c_str(), "BB1");
  EXPECT_STREQ(erh1->end_cunit_name().c_str(), "foobaz.c");
  EXPECT_STREQ(erh1->end_cfun_name().c_str(), "baz");
  EXPECT_STREQ(erh1->end_bb_name().c_str(), "BB2");
  EXPECT_EQ(erh1->edge_branch(), cpad::cfg::EDGE_FALLBACK_BRANCH);
}

TEST_F(EdgeRequestTests, DeserializeConstructorFromEmptyString)
{
  ::cpad::cfg::EdgeRequestHelper erh2("");
  EXPECT_STREQ(erh2.start_cunit_name().c_str(), "");
  EXPECT_STREQ(erh2.start_cfun_name().c_str(), "");
  EXPECT_STREQ(erh2.start_bb_name().c_str(), "");
  EXPECT_STREQ(erh2.end_cunit_name().c_str(), "");
  EXPECT_STREQ(erh2.end_cfun_name().c_str(), "");
  EXPECT_STREQ(erh2.end_bb_name().c_str(), "");
  EXPECT_EQ(erh2.edge_branch(), cpad::cfg::EDGE_DEFAULT_BRANCH);
}

TEST_F(EdgeRequestTests, CopyConstructor)
{
  ::cpad::cfg::EdgeRequestHelper erh2(*erh1);
  EXPECT_STREQ(erh2.start_cunit_name().c_str(), erh1->start_cunit_name().c_str());
  EXPECT_STREQ(erh2.start_cfun_name().c_str(), erh1->start_cfun_name().c_str());
  EXPECT_STREQ(erh2.start_bb_name().c_str(), erh1->start_bb_name().c_str());
  EXPECT_STREQ(erh2.end_cunit_name().c_str(), erh1->end_cunit_name().c_str());
  EXPECT_STREQ(erh2.end_cfun_name().c_str(), erh1->end_cfun_name().c_str());
  EXPECT_STREQ(erh2.end_bb_name().c_str(), erh1->end_bb_name().c_str());
  EXPECT_EQ(erh2.edge_branch(), erh1->edge_branch());
}

TEST_F(EdgeRequestTests, SerializeMethod)
{
  ::cpad::cfg::EdgeRequestHelper erh(std::string("foobar.c"), std::string("bar"), std::string("BB1"),
                                       std::string("foobaz.c"), std::string("baz"), std::string("BB2"),
                                       cpad::cfg::EDGE_FALLBACK_BRANCH);
  char local_buffer[128];
  memset(local_buffer, 0, 128);
  erh.serialize(local_buffer);    
  EXPECT_TRUE(memcmp(buffer, local_buffer, 128) == 0);
}

TEST_F(EdgeRequestTests, DumpMethod)
{
  erh1->dump(*osb);
  EXPECT_STREQ(dumpval.c_str(), strbuf.str().c_str());
}

#ifndef SINGLE_TEST_EXE
int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
#endif
