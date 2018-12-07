#include <gtest/gtest.h>
#include <kraMath.h>
#include <kraPrerequisitesUtil.h>
#include <kraVector2.h>
#include <kraVector3.h>
#include <kraVector4.h>
//#include <conio.h>

using namespace kraEngineSDK;

struct Testing : public ::testing::Test {
  virtual void SetUp() {
    fails = 0;
  }

  virtual void TearDown() {
    if (fails > 0) {
      std::cerr << "Testing::TearDown sees failures" << std::endl;
    }
  }

  unsigned fails;
};

int main(int argc, char **argv)
{
  
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();

  
}

TEST_F(Testing, Basic_Test)
{
  Vector2 vec1(2, 3);
  Vector2 vec2(2, 4);
  EXPECT_EQ(kraMath::cos(0), 1);
  EXPECT_EQ((vec1 + vec2), Vector2(4, 7));
  fails += ::testing::Test::HasFailure();
}

TEST_F(Testing, Basic_Types)
{
  EXPECT_TRUE(sizeof(int8) == 1);
  EXPECT_TRUE(sizeof(int16) == 2);
  EXPECT_TRUE(sizeof(int32) == 4);
  EXPECT_TRUE(sizeof(int64) == 8);


  EXPECT_TRUE(sizeof(uint8) == 1);
  EXPECT_TRUE(sizeof(uint16) == 2);
  EXPECT_TRUE(sizeof(uint32) == 4);
  EXPECT_TRUE(sizeof(uint64) == 8);

  EXPECT_TRUE(sizeof(float) == 4);
  EXPECT_TRUE(sizeof(double) == 8);
  fails += ::testing::Test::HasFailure();
}