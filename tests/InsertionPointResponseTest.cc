#include <iostream>     // std::cout, std::ostream, std::hex
#include <sstream>      // std::stringbuf
#include <string>       // std::string

#include <gtest/gtest.h>

#include "InsertionPointMsg.h"

class InsertionPointResponseTests : public ::testing::Test
{
public:
  char *buffer;
  ::cpad::insns::InsertionPointResponseHelper *iprh1;
  std::stringbuf strbuf;
  std::ostream *osb;
  std::string dumpval = "[InsertionPointResponse]\n"             \
    "insert asm statement: 1\n"                                  \
    "asm statement: foobarnop\n";

  InsertionPointResponseTests()
  {
    buffer = new char[128];
    memset(buffer, 0, 128);
    iprh1 = new ::cpad::insns::InsertionPointResponseHelper(true, "foobarnop");
    osb = new std::ostream(&strbuf);
  }

  virtual ~InsertionPointResponseTests()
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

TEST_F(InsertionPointResponseTests, DefaultConstructor)
{
  ::cpad::insns::InsertionPointResponseHelper iprh(true, "foobarnop");
  EXPECT_TRUE(iprh.insert_asm_statement());
  EXPECT_STREQ(iprh.asm_statement().c_str(), "foobarnop");
}

TEST_F(InsertionPointResponseTests, DeserializeConstructor)
{
  ::cpad::insns::InsertionPointResponseHelper iprh2(buffer);
  EXPECT_TRUE(iprh1->insert_asm_statement());
  EXPECT_STREQ(iprh1->asm_statement().c_str(), "foobarnop");
}

TEST_F(InsertionPointResponseTests, DeserializeConstructorFromEmptyString)
{
  ::cpad::insns::InsertionPointResponseHelper iprh2("");
  EXPECT_FALSE(iprh2.insert_asm_statement());
  EXPECT_STREQ(iprh2.asm_statement().c_str(), "");
}

TEST_F(InsertionPointResponseTests, CopyConstructor)
{
  ::cpad::insns::InsertionPointResponseHelper iprh2(*iprh1);
  EXPECT_EQ(iprh2.insert_asm_statement(), iprh1->insert_asm_statement());
  EXPECT_STREQ(iprh2.asm_statement().c_str(), iprh1->asm_statement().c_str());
}

TEST_F(InsertionPointResponseTests, SerializeMethod)
{
  ::cpad::insns::InsertionPointResponseHelper iprh(true, "foobarnop");
  char local_buffer[128];
  memset(local_buffer, 0, 128);
  iprh.serialize(local_buffer);    
  EXPECT_TRUE(memcmp(buffer, local_buffer, 128) == 0);
}

TEST_F(InsertionPointResponseTests, DumpMethod)
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
