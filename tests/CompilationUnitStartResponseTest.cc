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
    memset(buffer, 0, 128);
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

TEST_F(CompilationUnitStartResponseTests, DefaultConstructor)
{
  ::cpad::cfg::CompilationUnitStartResponseHelper cusrh();
}

TEST_F(CompilationUnitStartResponseTests, DeserializeConstructor)
{
  ::cpad::cfg::CompilationUnitStartResponseHelper cusrh2(buffer);
}

TEST_F(CompilationUnitStartResponseTests, DeserializeConstructorFromEmptyString)
{
  ::cpad::cfg::CompilationUnitStartResponseHelper cusrh2("");
}

TEST_F(CompilationUnitStartResponseTests, CopyConstructor)
{
  ::cpad::cfg::CompilationUnitStartResponseHelper cusrh2(*cusrh1);
}

TEST_F(CompilationUnitStartResponseTests, SerializeMethod)
{
  ::cpad::cfg::CompilationUnitStartResponseHelper cusrh;
  char local_buffer[128];
  memset(local_buffer, 0, 128);
  cusrh.serialize(local_buffer);    
  EXPECT_TRUE(memcmp(buffer, local_buffer, 128) == 0);
}

TEST_F(CompilationUnitStartResponseTests, DumpMethod)
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
