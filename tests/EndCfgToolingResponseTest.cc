#include <iostream>     // std::cout, std::ostream, std::hex
#include <sstream>      // std::stringbuf
#include <string>       // std::string

#include <gtest/gtest.h>

#include "BuildMngtMsg.h"

#define SERIALIZE_BUFFER_SIZE 1024

class EndCfgToolingResponseTests : public ::testing::Test
{
public:
  ::google::protobuf::Map<::std::string, ::cpad::build_mngt::EndCfgToolingResponse_BbStat> stat;
  char *buffer;
  ::cpad::build_mngt::EndCfgToolingResponseHelper *ectrh1;
  std::stringbuf strbuf;
  std::ostream *osb;
  std::string dumpval = "[EndCfgToolingResponse]\n"	\
    "statistics for BB 'BB1' is: \n"			\
    "   original length: 10\n"				\
    "   modified length: 15\n"				\
    "statistics for BB 'BB2' is: \n"			\
    "   original length: 12\n"				\
    "   modified length: 19\n"				\
    "statistics for BB 'BB3' is: \n"			\
    "   original length: 14\n"				\
    "   modified length: 17\n"				\
    "statistics for BB 'BB4' is: \n"			\
    "   original length: 34\n"				\
    "   modified length: 65\n"                          \
    ;
  
  EndCfgToolingResponseTests()
  {
    ::cpad::build_mngt::EndCfgToolingResponse_BbStat bb1stat;
    bb1stat.set_bb_original_length(10);
    bb1stat.set_bb_modified_length(15);
    stat[std::string("BB1")] = bb1stat;
    ::cpad::build_mngt::EndCfgToolingResponse_BbStat bb2stat;
    bb2stat.set_bb_original_length(12);
    bb2stat.set_bb_modified_length(19);
    stat[std::string("BB2")] = bb2stat;
    ::cpad::build_mngt::EndCfgToolingResponse_BbStat bb3stat;
    bb3stat.set_bb_original_length(14);
    bb3stat.set_bb_modified_length(17);
    stat[std::string("BB3")] = bb3stat;
    ::cpad::build_mngt::EndCfgToolingResponse_BbStat bb4stat;
    bb4stat.set_bb_original_length(34);
    bb4stat.set_bb_modified_length(65);
    stat[std::string("BB4")] = bb4stat;
    buffer = new char[SERIALIZE_BUFFER_SIZE];
    memset(buffer, 0, SERIALIZE_BUFFER_SIZE);
    ectrh1 = new ::cpad::build_mngt::EndCfgToolingResponseHelper(stat);
    osb = new std::ostream(&strbuf);
  }

  virtual ~EndCfgToolingResponseTests()
  {
    delete buffer;
    delete ectrh1;
  }

  virtual void SetUp(void)
  {
    ectrh1->serialize(buffer);    
  }

  virtual void TearDown(void)
  {
  }
};

TEST_F(EndCfgToolingResponseTests, DefaultConstructor)
{
  ::cpad::build_mngt::EndCfgToolingResponseHelper ectrh(stat);
  auto lstat = ectrh.statistics();
  EXPECT_EQ(lstat["BB1"].bb_original_length(), 10);
  EXPECT_EQ(lstat["BB1"].bb_modified_length(), 15);
  EXPECT_EQ(lstat["BB2"].bb_original_length(), 12);
  EXPECT_EQ(lstat["BB2"].bb_modified_length(), 19);
  EXPECT_EQ(lstat["BB3"].bb_original_length(), 14);
  EXPECT_EQ(lstat["BB3"].bb_modified_length(), 17);
  EXPECT_EQ(lstat["BB4"].bb_original_length(), 34);
  EXPECT_EQ(lstat["BB4"].bb_modified_length(), 65);
}

TEST_F(EndCfgToolingResponseTests, DeserializeConstructor)
{
  ::cpad::build_mngt::EndCfgToolingResponseHelper ectrh2(buffer);
  auto lstat = ectrh2.statistics();
  EXPECT_EQ(lstat["BB1"].bb_original_length(), 10);
  EXPECT_EQ(lstat["BB1"].bb_modified_length(), 15);
  EXPECT_EQ(lstat["BB2"].bb_original_length(), 12);
  EXPECT_EQ(lstat["BB2"].bb_modified_length(), 19);
  EXPECT_EQ(lstat["BB3"].bb_original_length(), 14);
  EXPECT_EQ(lstat["BB3"].bb_modified_length(), 17);
  EXPECT_EQ(lstat["BB4"].bb_original_length(), 34);
  EXPECT_EQ(lstat["BB4"].bb_modified_length(), 65);
}

TEST_F(EndCfgToolingResponseTests, DeserializeConstructorFromEmptyString)
{
  ::cpad::build_mngt::EndCfgToolingResponseHelper ectrh2("");
  auto lstat = ectrh2.statistics();
  EXPECT_TRUE(lstat.empty());
}

TEST_F(EndCfgToolingResponseTests, CopyConstructor)
{
  ::cpad::build_mngt::EndCfgToolingResponseHelper ectrh2(*ectrh1);
  auto lstat1 = ectrh2.statistics();
  auto lstat2 = ectrh1->statistics();
  EXPECT_EQ(lstat1["BB1"].bb_original_length(), lstat2["BB1"].bb_original_length());
  EXPECT_EQ(lstat1["BB1"].bb_modified_length(), lstat2["BB1"].bb_modified_length());
  EXPECT_EQ(lstat1["BB2"].bb_original_length(), lstat2["BB2"].bb_original_length());
  EXPECT_EQ(lstat1["BB2"].bb_modified_length(), lstat2["BB2"].bb_modified_length());
  EXPECT_EQ(lstat1["BB3"].bb_original_length(), lstat2["BB3"].bb_original_length());
  EXPECT_EQ(lstat1["BB3"].bb_modified_length(), lstat2["BB3"].bb_modified_length());
  EXPECT_EQ(lstat1["BB4"].bb_original_length(), lstat2["BB4"].bb_original_length());
  EXPECT_EQ(lstat1["BB4"].bb_modified_length(), lstat2["BB4"].bb_modified_length());
}

TEST_F(EndCfgToolingResponseTests, SerializeMethod)
{
  ::cpad::build_mngt::EndCfgToolingResponseHelper ectrh(stat);
  char local_buffer[SERIALIZE_BUFFER_SIZE];
  bzero(local_buffer, SERIALIZE_BUFFER_SIZE);
  ectrh.serialize(local_buffer);    
  ::cpad::build_mngt::EndCfgToolingResponseHelper ectrh2(buffer);
  auto lstat = ectrh2.statistics();
  EXPECT_EQ(stat["BB1"].bb_original_length(), lstat["BB1"].bb_original_length());
  EXPECT_EQ(stat["BB1"].bb_modified_length(), lstat["BB1"].bb_modified_length());
  EXPECT_EQ(stat["BB2"].bb_original_length(), lstat["BB2"].bb_original_length());
  EXPECT_EQ(stat["BB2"].bb_modified_length(), lstat["BB2"].bb_modified_length());
  EXPECT_EQ(stat["BB3"].bb_original_length(), lstat["BB3"].bb_original_length());
  EXPECT_EQ(stat["BB3"].bb_modified_length(), lstat["BB3"].bb_modified_length());
  EXPECT_EQ(stat["BB4"].bb_original_length(), lstat["BB4"].bb_original_length());
  EXPECT_EQ(stat["BB4"].bb_modified_length(), lstat["BB4"].bb_modified_length());

}

TEST_F(EndCfgToolingResponseTests, DumpMethod)
{
  ectrh1->dump(*osb);
  EXPECT_STREQ(dumpval.c_str(), strbuf.str().c_str());
}

#ifndef SINGLE_TEST_EXE
int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
#endif
