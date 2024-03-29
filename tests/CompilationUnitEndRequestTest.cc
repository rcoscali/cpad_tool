#include <iostream>     // std::cout, std::ostream, std::hex
#include <sstream>      // std::stringbuf
#include <string>       // std::string

#include <gtest/gtest.h>

#include "CompilationUnitMsg.h"

class CompilationUnitEndRequestTests : public ::testing::Test
{
public:
  char *buffer;
  ::cpad::cfg::CompilationUnitEndRequestHelper *cuerh1;
  std::stringbuf strbuf;
  std::ostream *osb;
  std::string dumpval = "[CompilationUnitEndRequest]\n";

  CompilationUnitEndRequestTests()
  {
    buffer = new char[128];
    memset(buffer, 0, 128);
    cuerh1 = new ::cpad::cfg::CompilationUnitEndRequestHelper();
    osb = new std::ostream(&strbuf);
  }

  virtual ~CompilationUnitEndRequestTests()
  {
    delete buffer;
    delete cuerh1;
    delete osb;
  }

  virtual void SetUp(void)
  {
  }

  virtual void TearDown(void)
  {
  }
};

TEST_F(CompilationUnitEndRequestTests, DefaultConstructor)
{
  ::cpad::cfg::CompilationUnitEndRequestHelper cuerh();
}

TEST_F(CompilationUnitEndRequestTests, DeserializeConstructor)
{
  ::cpad::cfg::CompilationUnitEndRequestHelper cuerh2(buffer);
}

TEST_F(CompilationUnitEndRequestTests, DeserializeConstructorFromEmptyString)
{
  ::cpad::cfg::CompilationUnitEndRequestHelper cuerh2("");
}

TEST_F(CompilationUnitEndRequestTests, CopyConstructor)
{
  ::cpad::cfg::CompilationUnitEndRequestHelper cuerh2(*cuerh1);
}

TEST_F(CompilationUnitEndRequestTests, SerializeMethod)
{
  ::cpad::cfg::CompilationUnitEndRequestHelper cuerh;
  char local_buffer[128];
  memset(local_buffer, 0, 128);
  cuerh.serialize(local_buffer);    
  EXPECT_TRUE(memcmp(buffer, local_buffer, 128) == 0);
}

TEST_F(CompilationUnitEndRequestTests, DumpMethod)
{
  cuerh1->dump(*osb);
  EXPECT_STREQ(dumpval.c_str(), strbuf.str().c_str());
}

#ifndef SINGLE_TEST_EXE
int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
#endif
