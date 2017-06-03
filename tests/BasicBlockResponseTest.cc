#include <iostream>     // std::cout, std::ostream, std::hex
#include <sstream>      // std::stringbuf
#include <string>       // std::string

#include <gtest/gtest.h>

#include "BasicBlockMsg.h"

class BasicBlockResponseTests : public ::testing::Test
{
public:
  char *buffer;
  ::cpad::cfg::BasicBlockResponseHelper *bbrh1;
  std::stringbuf strbuf;
  std::ostream *osb;
  std::string dumpval = "[BasicBlockResponse]\n";

  BasicBlockResponseTests()
  {
    buffer = new char[128];
    memset(buffer, 0, 128);
    bbrh1 = new ::cpad::cfg::BasicBlockResponseHelper();
    osb = new std::ostream(&strbuf);
  }

  virtual ~BasicBlockResponseTests()
  {
    delete buffer;
    delete bbrh1;
  }

  virtual void SetUp(void)
  {
    bbrh1->serialize(buffer);    
  }

  virtual void TearDown(void)
  {
  }
};

TEST_F(BasicBlockResponseTests, DefaultConstructor)
{
  ::cpad::cfg::BasicBlockResponseHelper bbrh();
}

TEST_F(BasicBlockResponseTests, DeserializeConstructor)
{
  ::cpad::cfg::BasicBlockResponseHelper bbrh2(buffer);
}

TEST_F(BasicBlockResponseTests, DeserializeConstructorFromEmptyString)
{
  ::cpad::cfg::BasicBlockResponseHelper bbrh2("");
}

TEST_F(BasicBlockResponseTests, CopyConstructor)
{
  ::cpad::cfg::BasicBlockResponseHelper bbrh2(*bbrh1);
}

TEST_F(BasicBlockResponseTests, SerializeMethod)
{
  ::cpad::cfg::BasicBlockResponseHelper bbrh("");
  char local_buffer[128];
  memset(local_buffer, 0, 128);
  bbrh.serialize(local_buffer);    
  EXPECT_TRUE(memcmp(buffer, local_buffer, 128) == 0);
}

TEST_F(BasicBlockResponseTests, DumpMethod)
{
  bbrh1->dump(*osb);
  EXPECT_STREQ(dumpval.c_str(), strbuf.str().c_str());
}

#ifndef SINGLE_TEST_EXE
int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
#endif
