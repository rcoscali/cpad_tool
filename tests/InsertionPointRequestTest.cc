#include <iostream>     // std::cout, std::ostream, std::hex
#include <sstream>      // std::stringbuf
#include <string>       // std::string

#include <gtest/gtest.h>

#include "InsertionPointMsg.h"

class InsertionPointRequestTests : public ::testing::Test
{
public:
  char *buffer;
  ::cpad::insns::InsertionPointRequestHelper *iprh1;
  std::stringbuf strbuf;
  std::ostream *osb;
  std::string dumpval = "[InsertionPointRequestHelper]\n"       \
    "cunit name: foobar.c\n"                                    \
    "cfun name: foo\n"                                          \
    "location: 5\n";

  InsertionPointRequestTests()
  {
    buffer = new char[128];
    memset(buffer, 0, 128);
    iprh1 = new ::cpad::insns::InsertionPointRequestHelper("foobar.c", "foo", ::cpad::insns::FUNCTION_BEFORE_CALL);
    osb = new std::ostream(&strbuf);
  }

  virtual ~InsertionPointRequestTests()
  {
    delete buffer;
    delete iprh1;
  }

  virtual void SetUp(void)
  {
    iprh1->serialize(buffer);    
  }

  virtual void TearDown(void)
  {
  }
};

TEST_F(InsertionPointRequestTests, DefaultConstructor)
{
  ::cpad::insns::InsertionPointRequestHelper iprh("foobar.c", "foo", ::cpad::insns::FUNCTION_BEFORE_CALL);
  EXPECT_STREQ(iprh.cunit_name().c_str(), "foobar.c");
  EXPECT_STREQ(iprh.cfun_name().c_str(), "foo");
  EXPECT_EQ(iprh.location(), ::cpad::insns::FUNCTION_BEFORE_CALL);
}

TEST_F(InsertionPointRequestTests, DeserializeConstructor)
{
  ::cpad::insns::InsertionPointRequestHelper iprh2(buffer);
  EXPECT_STREQ(iprh1->cunit_name().c_str(), "foobar.c");
  EXPECT_STREQ(iprh1->cfun_name().c_str(), "foo");
  EXPECT_EQ(iprh1->location(), ::cpad::insns::FUNCTION_BEFORE_CALL);
}

TEST_F(InsertionPointRequestTests, DeserializeConstructorFromEmptyString)
{
  ::cpad::insns::InsertionPointRequestHelper iprh2("");
  EXPECT_STREQ(iprh2.cunit_name().c_str(), "");
  EXPECT_STREQ(iprh2.cfun_name().c_str(), "");
  EXPECT_EQ(iprh2.location(), ::cpad::insns::FUNCTION_ENTRY_BLOCK);
}

TEST_F(InsertionPointRequestTests, CopyConstructor)
{
  ::cpad::insns::InsertionPointRequestHelper iprh2(*iprh1);
  EXPECT_STREQ(iprh2.cunit_name().c_str(), iprh1->cunit_name().c_str());
  EXPECT_STREQ(iprh2.cfun_name().c_str(), iprh1->cfun_name().c_str());
  EXPECT_EQ(iprh2.location(), iprh1->location());
}

TEST_F(InsertionPointRequestTests, SerializeMethod)
{
  ::cpad::insns::InsertionPointRequestHelper iprh("foobar.c", "foo", ::cpad::insns::FUNCTION_BEFORE_CALL);
  char local_buffer[128];
  memset(local_buffer, 0, 128);
  iprh.serialize(local_buffer);    
  EXPECT_TRUE(memcmp(buffer, local_buffer, 128) == 0);
}

TEST_F(InsertionPointRequestTests, DumpMethod)
{
  iprh1->dump(*osb);
  EXPECT_STREQ(dumpval.c_str(), strbuf.str().c_str());
}

#ifndef SINGLE_TEST_EXE
int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
#endif
