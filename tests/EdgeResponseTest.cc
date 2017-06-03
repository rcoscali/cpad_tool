#include <iostream>     // std::cout, std::ostream, std::hex
#include <sstream>      // std::stringbuf
#include <string>       // std::string

#include <gtest/gtest.h>

#include "EdgeMsg.h"

class EdgeResponseTests : public ::testing::Test
{
public:
  char *buffer;
  ::cpad::cfg::EdgeResponseHelper *erh1;
  std::stringbuf strbuf;
  std::ostream *osb;
  std::string dumpval = "[EdgeResponse]\n";

  EdgeResponseTests()
  {
    buffer = new char[128];
    memset(buffer, 0, 128);
    erh1 = new ::cpad::cfg::EdgeResponseHelper();
    osb = new std::ostream(&strbuf);
  }

  virtual ~EdgeResponseTests()
  {
    delete buffer;
    delete erh1;
  }

  virtual void SetUp(void)
  {
    erh1->serialize(buffer);    
  }

  virtual void TearDown(void)
  {
  }
};

TEST_F(EdgeResponseTests, DefaultConstructor)
{
  ::cpad::cfg::EdgeResponseHelper erh();
}

TEST_F(EdgeResponseTests, DeserializeConstructor)
{
  ::cpad::cfg::EdgeResponseHelper erh2(buffer);
}

TEST_F(EdgeResponseTests, DeserializeConstructorFromEmptyString)
{
  ::cpad::cfg::EdgeResponseHelper erh2("");
}

TEST_F(EdgeResponseTests, CopyConstructor)
{
  ::cpad::cfg::EdgeResponseHelper erh2(*erh1);
}

TEST_F(EdgeResponseTests, SerializeMethod)
{
  ::cpad::cfg::EdgeResponseHelper erh;
  char local_buffer[128];
  memset(local_buffer, 0, 128);
  erh.serialize(local_buffer);    
  EXPECT_TRUE(memcmp(buffer, local_buffer, 128) == 0);
}

TEST_F(EdgeResponseTests, DumpMethod)
{
  erh1->dump(*osb);
  EXPECT_STREQ(dumpval.c_str(), strbuf.str().c_str());
}

#ifndef SINGLE_TEST_EXE
int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
#endif
