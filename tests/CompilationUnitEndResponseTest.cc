#include <iostream>     // std::cout, std::ostream, std::hex
#include <sstream>      // std::stringbuf
#include <string>       // std::string

#include <gtest/gtest.h>

#include "CompilationUnitMsg.h"

class CompilationUnitEndResponseTests : public ::testing::Test
{
public:
  char *buffer;
  ::cpad::cfg::CompilationUnitEndResponseHelper *cuerh1;
  std::stringbuf strbuf;
  std::ostream *osb;
  std::string dumpval = "[CompilationUnitEndResponse]\n";

  CompilationUnitEndResponseTests()
  {
    buffer = new char[128];
    memset(buffer, 0, 128);
    cuerh1 = new ::cpad::cfg::CompilationUnitEndResponseHelper();
    osb = new std::ostream(&strbuf);
  }

  virtual ~CompilationUnitEndResponseTests()
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

TEST_F(CompilationUnitEndResponseTests, DefaultConstructor)
{
  ::cpad::cfg::CompilationUnitEndResponseHelper cuerh();
}

TEST_F(CompilationUnitEndResponseTests, DeserializeConstructor)
{
  ::cpad::cfg::CompilationUnitEndResponseHelper cuerh2(buffer);
}

TEST_F(CompilationUnitEndResponseTests, DeserializeConstructorFromEmptyString)
{
  ::cpad::cfg::CompilationUnitEndResponseHelper cuerh2("");
}

TEST_F(CompilationUnitEndResponseTests, CopyConstructor)
{
  ::cpad::cfg::CompilationUnitEndResponseHelper cuerh2(*cuerh1);
}

TEST_F(CompilationUnitEndResponseTests, SerializeMethod)
{
  ::cpad::cfg::CompilationUnitEndResponseHelper cuerh;
  char local_buffer[128];
  memset(local_buffer, 0, 128);
  cuerh.serialize(local_buffer);    
  EXPECT_TRUE(memcmp(buffer, local_buffer, 128) == 0);
}

TEST_F(CompilationUnitEndResponseTests, DumpMethod)
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
