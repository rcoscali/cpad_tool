#include <iostream>     // std::cout, std::ostream, std::hex
#include <sstream>      // std::stringbuf
#include <string>       // std::string

#include <gtest/gtest.h>

#include "CompilationUnitMsg.h"

class CompilationUnitStartRequestTests : public ::testing::Test
{
public:
  char *buffer;
  ::cpad::cfg::CompilationUnitStartRequestHelper *cusrh1;
  std::stringbuf strbuf;
  std::ostream *osb;
  std::string dumpval = "[CompilationUnitStartRequest]\n"       \
    "CUnit filename: foobar.c\n";

  CompilationUnitStartRequestTests()
  {
    buffer = new char[128];
    memset(buffer, 0, 128);
    cusrh1 = new ::cpad::cfg::CompilationUnitStartRequestHelper(std::string("foobar.c"));
    osb = new std::ostream(&strbuf);
  }

  virtual ~CompilationUnitStartRequestTests()
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

TEST_F(CompilationUnitStartRequestTests, DefaultConstructor)
{
  ::cpad::cfg::CompilationUnitStartRequestHelper cusrh(std::string("foobar.c"));
  EXPECT_STREQ(cusrh.filename().c_str(), "foobar.c");
}

TEST_F(CompilationUnitStartRequestTests, DeserializeConstructor)
{
  ::cpad::cfg::CompilationUnitStartRequestHelper cusrh2(buffer);
  EXPECT_STREQ(cusrh1->filename().c_str(), "foobar.c");
}

TEST_F(CompilationUnitStartRequestTests, DeserializeConstructorFromEmptyString)
{
  ::cpad::cfg::CompilationUnitStartRequestHelper cusrh2("");
  EXPECT_STREQ(cusrh2.filename().c_str(), "");
}

TEST_F(CompilationUnitStartRequestTests, CopyConstructor)
{
  ::cpad::cfg::CompilationUnitStartRequestHelper cusrh2(*cusrh1);
  EXPECT_STREQ(cusrh2.filename().c_str(), cusrh1->filename().c_str());
}

TEST_F(CompilationUnitStartRequestTests, SerializeMethod)
{
  ::cpad::cfg::CompilationUnitStartRequestHelper cusrh(std::string("foobar.c"));
  char local_buffer[128];
  memset(local_buffer, 0, 128);
  cusrh.serialize(local_buffer);    
  EXPECT_TRUE(memcmp(buffer, local_buffer, 128) == 0);
}

TEST_F(CompilationUnitStartRequestTests, DumpMethod)
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
