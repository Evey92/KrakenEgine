#include <iostream>
#include <gtest/gtest.h>

int main(int argc, char **argv)
{
  //Vector4 myVec(3, 2, 2, 3);
  ::testing::InitGoogleTest(&argc, argv);
  std::cout << RUN_ALL_TESTS();
  //std::cout << "x: " << myVec.x << " Y: " << myVec.y << std::endl;
  //_getch();
  return 0;

}