#include <gtest/gtest.h>
#include <kraMath.h>
#include <kraPrerequisitesUtil.h>
#include <kraVector2.h>
#include <kraVector3.h>
#include <kraVector4.h>
#include <kraMatrix4.h>
#include <d3d11.h>
#include <xnamath.h>


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

TEST_F(Testing, Vector_Test)
{
  Vector2 vec2(2, 3);
  Vector3 eye(0.0f, 3.0f, -6.0f);
  Vector3 at(0.0f, 1.0f, 0.0f);

  Vector3 eyePosition = at - eye;
  EXPECT_EQ(kraMath::cos(0), 1);
  EXPECT_EQ((eyePosition), Vector3(0.0f, -2.0f, 6.0f));

  //EXPECT_EQ((eyePositio.normalized(eyePositio)), (-0.31622776601683793319988935444327185337195551393252168268f));

  eyePosition.normalized();

  std::cout << "Normalized vector: (" << eyePosition.x <<", " << eyePosition.y <<", " << eyePosition.z <<")" << std::endl;

  fails += ::testing::Test::HasFailure();
}

TEST_F(Testing, Matrix_Test)
{
  
  Vector3 eye(0.0f, 3.0f, -6.0f);
  Vector3 at(0.0f, 1.0f, 0.0f);
  Vector3 up(0.0f, 1.0f, 0.0f);
  Matrix4 viewMat = Matrix4::MatrixLookAtLH(eye, at, up);

  XMVECTOR Eye = XMVectorSet(0.0f, 3.0f, -6.0f, 0.0f);
  XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
  XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
  XMMATRIX m_view;

  m_view = XMMatrixLookAtLH(Eye, At, Up);
  //Vector3 eyePositio = at - eye;
  EXPECT_EQ(kraMath::cos(0), 1);
  //EXPECT_EQ(viewMat, m_view);

  //EXPECT_EQ((eyePositio.normalized(eyePositio)), (-0.31622776601683793319988935444327185337195551393252168268f));
  m_view = XMMatrixTranspose(m_view);

  std::cout << "My Mat: " << std::endl;
  for(int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      std::cout<<", "<<viewMat.m[i][j];
    }
    std::cout<<std::endl;
  }


  std::cout << "\nDX Mat: " << std::endl;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      std::cout << ", " << m_view.m[i][j];
    }
    std::cout << std::endl;
  }

  float m_fov = kraMath::DEG2RAD(90.0f);
  float m_nearZ = 0.01f;
  float m_farZ = 1000.0f;
  float width = 1400;
  float height = 700;


  Matrix4 projection;
  projection.MatrixPerspectiveFOVLH(m_fov, width, height, m_nearZ, m_farZ);

  XMMATRIX g_Projection;
  g_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV2, width / (FLOAT)height, 0.01f, 1000.0f);

  g_Projection = XMMatrixTranspose(g_Projection);


  std::cout << "My proj Mat: " << std::endl;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      std::cout << ", " << projection.m[i][j];
    }
    std::cout << std::endl;
  }


  std::cout << "\nDX proj Mat: " << std::endl;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      std::cout << ", " << g_Projection.m[i][j];
    }
    std::cout << std::endl;
  }

  //eyePositio.normalize();

  //std::cout << "Normalized vector: (" << eyePositio.x << ", " << eyePositio.y << ", " << eyePositio.z << ")" << std::endl;

  fails += ::testing::Test::HasFailure();
}