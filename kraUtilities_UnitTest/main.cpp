#include <gtest/gtest.h>
#include <kraMath.h>
#include <kraPrerequisitesUtil.h>
#include "kraVector2.h"
#include "kraVector3.h"
#include "kraVector4.h"
//#include <conio.h>

using namespace kraEngineSDK;

int main(int argc, char **argv)
{
  Vector4 myVec(3,2, 2, 3);
  ::testing::InitGoogleTest(&argc, argv);
  std::cout << RUN_ALL_TESTS();
  std::cout <<"x: " << myVec.x << " Y: " << myVec.y << std::endl;
  //_getch();
	return 0;
  
}

TEST(Utilities, Basic_Test)
{
  Vector2 vec1(2, 3);
  Vector2 vec2(2, 4);
  EXPECT_EQ(kraMath::cos(0), 1);
  EXPECT_EQ((vec1 + vec2), Vector2(4, 7));

}