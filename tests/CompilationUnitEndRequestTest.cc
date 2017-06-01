#include <iostream>     // std::cout, std::ostream, std::hex
#include <sstream>      // std::stringbuf
#include <string>       // std::string

#include <gtest/gtest.h>

#include "CompilationUnitMsg.h"

class CompilationUnitEndRequestTests : public ::testing::Test
{
public:
  char *buffer;
  ::cpad::cfg::CompilationUnitEndRequestHelper *cusrh1;
  std::stringbuf strbuf;
  std::ostream *osb;
  std::string dumpval = "[CompilationUnitEndRequest]\n";

  CompilationUnitEndRequestTests()
  {
    buffer = new char[128];
    memset(buffer, 0, 128);
    cusrh1 = new ::cpad::cfg::CompilationUnitEndRequestHelper();
    osb = new std::ostream(&strbuf);
  }

  virtual ~CompilationUnitEndRequestTests()
  {
    delete buffer;
    delete cusrh1;
    delete osb;
  }

  virtual void SetUp(void)
  {
  }

  virtual void TearDown(void)
  {
  }
};

TEST_F(CompilationUnitEndRequestTests, DumpMethod)
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
