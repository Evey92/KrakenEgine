#include "kraMatrix4.h"
#include "kraVector2.h"
#include "kraVector3.h"

namespace kraEngineSDK {
  class Vector4;

  Matrix4::Matrix4() {
    for (uint32 i = 0; i < 4; ++i) {
      for (uint32 j = 0; j < 4; ++j) {
        m[i][j] =0;
      }
    }
  }

  Matrix4::Matrix4(float m00, float m10, float m20, float m30,
                   float m01, float m11, float m21, float m31,
                   float m02, float m12, float m22, float m32,
                   float m03, float m13, float m23, float m33) {

    m[0][0] = m00; m[1][0] = m10; m[2][0] = m20; m[3][0] = m30;
    m[0][1] = m01; m[1][1] = m11; m[2][1] = m21; m[3][1] = m31;
    m[0][2] = m02; m[1][2] = m12; m[2][2] = m22; m[3][2] = m32;
    m[0][3] = m03; m[1][3] = m13; m[2][3] = m23; m[3][3] = m33;
  }

  Matrix4::Matrix4(const Matrix4& mat) {
    _m = mat._m;
  }

  Matrix4
  Matrix4::operator+(const float& val) {
    Matrix4 newMat;

    for (uint32 i = 0; i < 4; ++i) {
      for (uint32 j = 0; j < 4; ++j) {
        newMat.m[i][j] = m[i][j] + val;
      }
    }

    return newMat;
  }

  Matrix4
    Matrix4::operator-(const float& val) {
    Matrix4 newMat;

    for (uint32 i = 0; i < 4; ++i) {
      for (uint32 j = 0; j < 4; ++j) {
        newMat.m[i][j] = m[i][j] - val;
      }
    }

    return newMat;
  }

  Matrix4
    Matrix4::operator*(const float& val) {
    Matrix4 newMat;

    for (uint32 i = 0; i < 4; ++i) {
      for (uint32 j = 0; j < 4; ++j) {
        newMat.m[i][j] = m[i][j] * val;
      }
    }

    return newMat;
  }

  Matrix4
  Matrix4::operator*(const Matrix4& Mat) {
    Matrix4 newMat;

    for (uint32 i = 0; i < 4; ++i) {
      for (uint32 j = 0; j < 4; ++j) {
        for (uint32 k = 0; k < 4; ++k) {

          newMat.m[i][j] += m[i][k] * Mat.m[k][j];

        }
      }
    }

    return newMat;
  }

  //Matrix4
  //Matrix4::operator*(const Vector4& Vec) {
  //  Matrix4 newMat;
  //  for (uint32 i = 0; i < 4; ++i) {
  //    for (uint32 j = 0; j < 4; ++j) {
  //      //newMat.m[i][j] = m[i][j] * Vec;
  //    }
  //  }
  //  return newMat;
  //}

  Matrix4
  Matrix4::operator+=(const Matrix4& Mat) {

    for (uint32 i = 0; i < 4; ++i) {
      for (uint32 j = 0; j < 4; ++j) {
        m[i][j] += Mat.m[i][j];
      }
    }

    return *this;
  }

  Matrix4
  Matrix4::operator-=(const Matrix4& Mat) {

    for (uint32 i = 0; i < 4; ++i) {
      for (uint32 j = 0; j < 4; ++j) {
        m[i][j] -= Mat.m[i][j];
      }
    }

    return *this;
  }

  Matrix4
  Matrix4::operator*=(const Matrix4& Mat) {

    for (uint32 i = 0; i < 4; ++i) {
      for (uint32 j = 0; j < 4; ++j) {
        m[i][j] *= Mat.m[i][j];
      }
    }

    return *this;
  }

  Matrix4
  Matrix4:: operator+=(float val) {

    for (uint32 i = 0; i < 4; ++i) {
      for (uint32 j = 0; j < 4; ++j) {
        m[i][j] += val;
      }
    }

    return *this;
  }

  Matrix4
  Matrix4::operator-=(float val) {


    for (uint32 i = 0; i < 4; ++i) {
      for (uint32 j = 0; j < 4; ++j) {
        m[i][j] -= val;
      }
    }

    return *this;
  }

  Matrix4
  Matrix4::operator*=(float val) {

    for (uint32 i = 0; i < 4; ++i) {
      for (uint32 j = 0; j < 4; ++j) {
        m[i][j] *= val;
      }
    }

    return *this;
  }

  Matrix4
  Matrix4::operator/=(float val) {

    for (uint32 i = 0; i < 4; ++i) {
      for (uint32 j = 0; j < 4; ++j) {
        m[i][j] /= val;
      }
    }

    return *this;
  }

  Matrix4
  Matrix4::operator=(const Matrix4& Mat) {

    for (uint32 i = 0; i < 4; ++i) {
      for (uint32 j = 0; j < 4; ++j) {
        m[i][j] = Mat.m[i][j];
      }
    }

    return *this;
  }

  bool
  Matrix4::operator==(const Matrix4& Mat) {

    for (uint32 i = 0; i < 4; ++i) {
      for (uint32 j = 0; j < 4; ++j) {
        if (m[i][j] == Mat.m[i][j]) {
          return true;
        }
      }
    }
    return false;
  }

  bool
    Matrix4::operator!=(const Matrix4& Mat) {
    return !(*this == Mat);
  }

  void
  Matrix4::identity() {
    m[0][0] = 1; m[0][1] = 0; m[0][2] = 0; m[0][3] = 0;
    m[1][0] = 0; m[1][1] = 1; m[1][2] = 0; m[1][3] = 0;
    m[2][0] = 0; m[2][1] = 0; m[2][2] = 1; m[2][3] = 0;
    m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;
  }

  Matrix4
  Matrix4::MatrixLookAtLH(const Vector3& Eye, 
                          const Vector3& At,
                          const Vector3& Up) {
    Vector3 zAxis = At - Eye;
    zAxis.normalized();
    Vector3 xAxis = Up ^ zAxis;
    xAxis.normalized();
    Vector3 yAxis = zAxis ^ xAxis;


    Matrix4 Mat;
    Mat.m[0][0] = xAxis.x; 
    Mat.m[0][1] = yAxis.x;
    Mat.m[0][2] = zAxis.x;
    Mat.m[0][3] = 0.0f;

    Mat.m[1][0] = xAxis.y;
    Mat.m[1][1] = yAxis.y;
    Mat.m[1][2] = zAxis.y;
    Mat.m[1][3] = 0.0f;

    Mat.m[2][0] = xAxis.z;
    Mat.m[2][1] = yAxis.z;
    Mat.m[2][2] = zAxis.z;
    Mat.m[2][3] = 0.0f;

    Mat.m[3][0] = -(xAxis | Eye);
    Mat.m[3][1] = -(yAxis | Eye);
    Mat.m[3][2] = -(zAxis | Eye);
    Mat.m[3][3] = 1.0f;

    return Mat;
  }

  Matrix4 
  Matrix4::MatrixLookAtRH(const Vector3& Eye, const Vector3& At, const Vector3& Up)
  {
    Vector3 zAxis = Eye - At;
    zAxis.normalized();
    Vector3 xAxis = Up ^ zAxis;
    xAxis.normalized();
    Vector3 yAxis = zAxis ^ xAxis;


    Matrix4 Mat;
    Mat.m[0][0] = xAxis.x;
    Mat.m[0][1] = yAxis.x;
    Mat.m[0][2] = zAxis.x;
    Mat.m[0][3] = 0.0f;

    Mat.m[1][0] = xAxis.y;
    Mat.m[1][1] = yAxis.y;
    Mat.m[1][2] = zAxis.y;
    Mat.m[1][3] = 0.0f;

    Mat.m[2][0] = xAxis.z;
    Mat.m[2][1] = yAxis.z;
    Mat.m[2][2] = zAxis.z;
    Mat.m[2][3] = 0.0f;

    Mat.m[3][0] = (xAxis | Eye);
    Mat.m[3][1] = (yAxis | Eye);
    Mat.m[3][2] = (zAxis | Eye);
    Mat.m[3][3] = 1.0f;

    return Mat;
  }

  void
  Matrix4::MatrixPerspectiveFOVLH(float FOV, float width, float height, float nearZ, float farZ) {

    /*ASSERT(width > 0);
    ASSERT(height > 0);
    ASSERT(FOV > 0);*/

    //based on the formula from OpenGL
    float hfov = FOV *0.5f;
    float aspectRatio = width / height;
    float farMnear = farZ - nearZ;

    float yScale = 1.0 / kraMath::tan(hfov);
    float xScale = yScale / aspectRatio;

    //float aspectRatio = static_cast<float>(width / height);


    m[0][0] = xScale;
    m[1][1] = yScale;
    m[2][2] = farZ / farMnear;
    m[2][3] = 1.0;
    m[3][2] = -nearZ * farZ / farMnear;
    m[3][3] = 0.0;
  }

  void 
  Matrix4::MatrixPerspectiveFOVRH(float FOV, float width, float height, float nearZ, float farZ)
  {
    float hfov = FOV  * 0.5f;
    float aspectRatio = width / height;
    float farMnear = farZ - nearZ;

    float yScale = 1.0 / kraMath::tan(hfov);
    float xScale = yScale * height / width;
       
    m[0][0] = xScale;
    m[1][1] = yScale;
    m[2][2] = farZ / farMnear;
    m[2][3] = -1.0;
    m[3][2] = -(nearZ * farZ) / farMnear;
    m[3][3] = 0.0;
  }

  void 
  Matrix4::MatrixRotX(float angle)
  {
    float fSinAngle = kraMath::sin(angle);
    float fCosAngle = kraMath::cos(angle);

    m[0][0] = 1; m[0][1] = 0;         m[0][2] = 0;          m[0][3] = 0;
    m[1][0] = 0; m[1][1] = fCosAngle; m[1][2] = -fSinAngle; m[1][3] = 0;
    m[2][0] = 0; m[2][1] = fSinAngle; m[2][2] = fCosAngle;  m[2][3] = 0;
    m[3][0] = 0; m[3][1] = 0;         m[3][2] = 0;          m[3][3] = 1;
  }

  void
  Matrix4::MatrixRotY(float angle) {
    float fSinAngle = kraMath::sin(angle);
    float fCosAngle = kraMath::cos(angle);

    m[0][0] = fCosAngle ; m[0][1] = 0; m[0][2] = fSinAngle; m[0][3] = 0;
    m[1][0] =     0     ; m[1][1] = 1; m[1][2] =     0    ; m[1][3] = 0;
    m[2][0] = -fSinAngle; m[2][1] = 0; m[2][2] = fCosAngle; m[2][3] = 0;
    m[3][0] =     0     ; m[3][1] = 0; m[3][2] =     0    ; m[3][3] = 1;
  }

  void 
  Matrix4::MatrixRotZ(float angle)
  {
    float fSinAngle = kraMath::sin(angle);
    float fCosAngle = kraMath::cos(angle);

    m[0][0] = fCosAngle; m[0][1] = -fSinAngle;  m[0][2] = 0;  m[0][3] = 0;
    m[1][0] = fSinAngle; m[1][1] = fCosAngle;   m[1][2] = 0;  m[1][3] = 0;
    m[2][0] = 0;         m[2][1] = 0;           m[2][2] = 1;  m[2][3] = 0;
    m[3][0] = 0;         m[3][1] = 0;           m[3][2] = 0;  m[3][3] = 1;
  }

  Matrix4
  Matrix4::eulerAngleXY(float angleX, float angleY)
  {
    float cosX = kraMath::cos(angleX);
    float sinX = kraMath::sin(angleX);
    float cosY = kraMath::cos(angleY);
    float sinY = kraMath::sin(angleY);

    Matrix4 rotMatrix;

    rotMatrix.m[0][0] = cosY; rotMatrix.m[0][1] = -sinX * -sinY; rotMatrix.m[0][2] = cosX * -sinY; rotMatrix.m[0][3] = 0;
    rotMatrix.m[1][0] = 0;    rotMatrix.m[1][1] = cosX;          rotMatrix.m[1][2] = sinX;         rotMatrix.m[1][3] = 0;
    rotMatrix.m[2][0] = sinY; rotMatrix.m[2][1] = -sinX * cosY;  rotMatrix.m[2][2] = cosX * cosY;  rotMatrix.m[2][3] = 0;
    rotMatrix.m[3][0] = 0;    rotMatrix.m[3][1] = 0;             rotMatrix.m[3][2] = 0;            rotMatrix.m[3][3] = 1;

    return rotMatrix;
  }

  void
  Matrix4::transpose() {
    Matrix4 tempMat = *this;
    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j) {
        m[i][j] = tempMat.m[j][i];
      }
    }
  }

  Matrix4
  Matrix4::transposed(const Matrix4& mat) {
    Matrix4 tempMat = mat;
    Matrix4 transpMat;
    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j) {
        transpMat.m[i][j] = tempMat.m[j][i];
      }
    }

    return transpMat;
  }
  
  void
  Matrix4::tranlsate() {

  }

  Matrix4 
  Matrix4::ZERO = Matrix4(0.0f, 0.0f, 0.0f, 0.0f,
                          0.0f, 0.0f, 0.0f, 0.0f,
                          0.0f, 0.0f, 0.0f, 0.0f,
                          0.0f, 0.0f, 0.0f, 0.0f);

  Matrix4 
  Matrix4::IDENTITY = Matrix4(1.0f, 0.0f, 0.0f, 0.0f,
                              0.0f, 1.0f, 0.0f, 0.0f,
                              0.0f, 0.0f, 1.0f, 0.0f,
                              0.0f, 0.0f, 0.0f, 1.0f);
}