#include <iostream>     // std::cout, std::ostream, std::hex
#include <sstream>      // std::stringbuf
#include <string>       // std::string

#include <gtest/gtest.h>

#include "BuildMngtMsg.h"

class EndCfgCollectionResponseTests : public ::testing::Test
{
public:
  char *buffer;
  ::cpad::build_mngt::EndCfgCollectionResponseHelper *eccrh1;
  std::stringbuf strbuf;
  std::ostream *osb;
  std::string dumpval = "[EndCfgCollectionResponse]\n"       \
    "apex allocation status: 1\n"                             \
    "apex allocation message: APEX allocated successfully!\n";
  
  EndCfgCollectionResponseTests()
  {
    buffer = new char[128];
    memset(buffer, 0, 128);
    eccrh1 = new ::cpad::build_mngt::EndCfgCollectionResponseHelper(cpad::build_mngt::EndCfgCollectionResponse::APEX_ALLOCATION_OK,
                                                                    std::string("APEX allocated successfully!"));
    osb = new std::ostream(&strbuf);
  }

  virtual ~EndCfgCollectionResponseTests()
  {
    delete buffer;
    delete eccrh1;
  }

  virtual void SetUp(void)
  {
    eccrh1->serialize(buffer);    
  }

  virtual void TearDown(void)
  {
  }
};

TEST_F(EndCfgCollectionResponseTests, DefaultConstructor)
{
  ::cpad::build_mngt::EndCfgCollectionResponseHelper eccrh(cpad::build_mngt::EndCfgCollectionResponse::APEX_ALLOCATION_OK,
                                                           std::string("APEX allocated successfully!"));
  EXPECT_EQ(eccrh.apex_allocation_status(), cpad::build_mngt::EndCfgCollectionResponse::APEX_ALLOCATION_OK);
  EXPECT_STREQ(eccrh.apex_allocation_message().c_str(), "APEX allocated successfully!");
}

TEST_F(EndCfgCollectionResponseTests, DeserializeConstructor)
{
  ::cpad::build_mngt::EndCfgCollectionResponseHelper eccrh2(buffer);
  EXPECT_EQ(eccrh2.apex_allocation_status(), cpad::build_mngt::EndCfgCollectionResponse::APEX_ALLOCATION_OK);
  EXPECT_STREQ(eccrh2.apex_allocation_message().c_str(), "APEX allocated successfully!");
}

TEST_F(EndCfgCollectionResponseTests, DeserializeConstructorFromEmptyString)
{
  ::cpad::build_mngt::EndCfgCollectionResponseHelper eccrh2("");
  EXPECT_EQ(eccrh2.apex_allocation_status(), cpad::build_mngt::EndCfgCollectionResponse::APEX_ALLOCATION_ERROR);
  EXPECT_TRUE(cpad::build_mngt::EndCfgCollectionResponse::ApexAllocationStatus_IsValid(eccrh2.apex_allocation_status()));
  EXPECT_STREQ(eccrh2.apex_allocation_message().c_str(), "");
}

TEST_F(EndCfgCollectionResponseTests, CopyConstructor)
{
  ::cpad::build_mngt::EndCfgCollectionResponseHelper eccrh2(*eccrh1);
  EXPECT_EQ(eccrh2.apex_allocation_status(), eccrh1->apex_allocation_status());
  EXPECT_STREQ(eccrh2.apex_allocation_message().c_str(), eccrh1->apex_allocation_message().c_str());
}

TEST_F(EndCfgCollectionResponseTests, SerializeMethod)
{
  ::cpad::build_mngt::EndCfgCollectionResponseHelper eccrh(cpad::build_mngt::EndCfgCollectionResponse::APEX_ALLOCATION_OK,
                                                           std::string("APEX allocated successfully!"));
  char local_buffer[128];
  memset(local_buffer, 0, 128);
  eccrh.serialize(local_buffer);    
  EXPECT_TRUE(memcmp(buffer, local_buffer, 128) == 0);
}

TEST_F(EndCfgCollectionResponseTests, DumpMethod)
{
  eccrh1->dump(*osb);
  EXPECT_STREQ(dumpval.c_str(), strbuf.str().c_str());
}

#ifndef SINGLE_TEST_EXE
int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
#endif
