#include <iostream>     // std::cout, std::ostream, std::hex
#include <sstream>      // std::stringbuf
#include <string>       // std::string

#include <gtest/gtest.h>

#include "FunctionMsg.h"

class FunctionResponseTests : public ::testing::Test
{
public:
  char *buffer;
  ::cpad::cfg::FunctionResponseHelper *frh1;
  std::stringbuf strbuf;
  std::ostream *osb;
  std::string dumpval = "[FunctionResponse]\n";

  FunctionResponseTests()
  {
    buffer = new char[128];
    memset(buffer, 0, 128);
    frh1 = new ::cpad::cfg::FunctionResponseHelper();
    osb = new std::ostream(&strbuf);
  }

  virtual ~FunctionResponseTests()
  {
    delete buffer;
    delete frh1;
  }

  virtual void SetUp(void)
  {
    frh1->serialize(buffer);    
  }

  virtual void TearDown(void)
  {
  }
};

TEST_F(FunctionResponseTests, DefaultConstructor)
{
  ::cpad::cfg::FunctionResponseHelper frh();
}

TEST_F(FunctionResponseTests, DeserializeConstructor)
{
  ::cpad::cfg::FunctionResponseHelper frh2(buffer);
}

TEST_F(FunctionResponseTests, DeserializeConstructorFromEmptyString)
{
  ::cpad::cfg::FunctionResponseHelper frh2("");
}

TEST_F(FunctionResponseTests, CopyConstructor)
{
  ::cpad::cfg::FunctionResponseHelper frh2(*frh1);
}

TEST_F(FunctionResponseTests, SerializeMethod)
{
  ::cpad::cfg::FunctionResponseHelper frh;
  char local_buffer[128];
  memset(local_buffer, 0, 128);
  frh.serialize(local_buffer);    
  EXPECT_TRUE(memcmp(buffer, local_buffer, 128) == 0);
}

TEST_F(FunctionResponseTests, DumpMethod)
{
  frh1->dump(*osb);
  EXPECT_STREQ(dumpval.c_str(), strbuf.str().c_str());
}

#ifndef SINGLE_TEST_EXE
int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
#endif
