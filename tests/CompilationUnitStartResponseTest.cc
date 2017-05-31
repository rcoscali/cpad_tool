#include <iostream>     // std::cout, std::ostream, std::hex
#include <sstream>      // std::stringbuf
#include <string>       // std::string

#include <gtest/gtest.h>

#include "CompilationUnitMsg.h"

class CompilationUnitStartResponseTests : public ::testing::Test
{
public:
  char *buffer;
  ::cpad::cfg::CompilationUnitStartResponseHelper *cusrh1;
  std::stringbuf strbuf;
  std::ostream *osb;
  std::string dumpval = "[CompilationUnitStartResponse]\n";

  CompilationUnitStartResponseTests()
  {
    buffer = new char[128];
    bzero(buffer, 128);
    cusrh1 = new ::cpad::cfg::CompilationUnitStartResponseHelper();
    osb = new std::ostream(&strbuf);
  }

  virtual ~CompilationUnitStartResponseTests()
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

TEST_F(CompilationUnitStartResponseTests, DumpMethod)
{
  cusrh1->dump(*osb);
  EXPECT_STREQ(dumpval.c_str(), strbuf.str().c_str());
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
