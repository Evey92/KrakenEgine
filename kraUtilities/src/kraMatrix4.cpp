#include "kraMatrix4.h"

namespace kraEngineSDK {
  class Vector4;

  Matrix4::Matrix4(float m00, float m01, float m02, float m03,
    float m10, float m11, float m12, float m13,
    float m20, float m21, float m22, float m23,
    float m30, float m31, float m32, float m33) {

    m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
    m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
    m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
    m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
  }

  Matrix4::Matrix4(const Matrix4& mat) {
    m[0][0] = mat.m[0][0]; m[0][1] = mat.m[0][1]; m[0][2] = mat.m[0][2]; m[0][3] = mat.m[0][3];
    m[1][0] = mat.m[1][0]; m[1][1] = mat.m[1][1]; m[1][2] = mat.m[1][2]; m[1][3] = mat.m[1][3];
    m[2][0] = mat.m[2][0]; m[2][1] = mat.m[2][1]; m[2][2] = mat.m[2][2]; m[2][3] = mat.m[2][3];
    m[3][0] = mat.m[3][0]; m[3][1] = mat.m[3][1]; m[3][2] = mat.m[3][2]; m[3][3] = mat.m[3][3];
  }

  Matrix4::Matrix4(float mat[4][4]) {
    m[0][0] = mat[0][0]; m[0][1] = mat[0][1]; m[0][2] = mat[0][2]; m[0][3] = mat[0][3];
    m[1][0] = mat[1][0]; m[1][1] = mat[1][1]; m[1][2] = mat[1][2]; m[1][3] = mat[1][3];
    m[2][0] = mat[2][0]; m[2][1] = mat[2][1]; m[2][2] = mat[2][2]; m[2][3] = mat[2][3];
    m[3][0] = mat[3][0]; m[3][1] = mat[3][1]; m[3][2] = mat[3][2]; m[3][3] = mat[3][3];
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
        newMat.m[i][j] = m[i][j] * Mat.m[i][j];
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
  Matrix4::MatrixLookAtLH(Vector4 Eye, Vector4 At, Vector4 Up) {
    
    Vector4 zAxis = (At - Eye).normalize();
    Vector4 xAxis = Vector4::cross(Up, zAxis).normalize();
    Vector4 yAxis = Vector4::cross(zAxis, xAxis).normalize();

    Matrix4 Mat;
    Mat.m[0][0] = xAxis.x; 
    Mat.m[1][0] = yAxis.x;
    Mat.m[2][0] = zAxis.x;
    Mat.m[3][0] = 0.0f;

    Mat.m[0][1] = xAxis.y;
    Mat.m[1][1] = yAxis.y;
    Mat.m[2][1] = zAxis.y;
    Mat.m[3][1] = 0.0f;

    Mat.m[0][2] = xAxis.z;
    Mat.m[1][2] = yAxis.z;
    Mat.m[2][2] = zAxis.z;
    Mat.m[3][2] = 0.0f;

    Mat.m[0][3] = Vector4::dot(xAxis, Eye);
    Mat.m[1][3] = Vector4::dot(yAxis, Eye);
    Mat.m[2][3] = Vector4::dot(zAxis, Eye);
    Mat.m[3][3] = 1.0f;

    return Mat;
  }

  void
  Matrix4::MatrixPerspectiveFOV(float FOV, float aspectRatio, float nearZ, float farZ) {
    Matrix4 tempMat;

    row[0] = Vector4(1.0f/(kraMath::tan(FOV/2.0f)), 0.0f, 0.0f, 0.0f);
    row[1] = Vector4(0.0f, aspectRatio * 1.0f/kraMath::tan(FOV/2.0f), 0.0f, 0.0f);
    row[2] = Vector4(0.0f, 0.0f, farZ /(farZ - nearZ), 1.0f);
    row[3] = Vector4(0.0f, 0.0f, (-nearZ * (farZ / (farZ - nearZ))), 0.0f);
  }

  void
  Matrix4::MatrixRotY(float angle) {
    float fSinAngle = kraMath::sin(angle);
    float fCosAngle = kraMath::cos(angle);

    m[0][0] = fCosAngle;
    m[0][1] = 0.0f;
    m[0][2] = -fSinAngle;
    m[0][3] = 0.0f;

    m[1][0] = 0.0f;
    m[1][1] = 1.0f;
    m[1][2] = 0.0f;
    m[1][3] = 0.0f;

    m[2][0] = fSinAngle;
    m[2][1] = 0.0f;
    m[2][2] = fCosAngle;
    m[2][3] = 0.0f;

    m[0][0] = 0;
    m[0][1] = 0.0f;
    m[0][2] = 0;
    m[0][3] = 1.0f;

  }

  void
  Matrix4::transpose() {
    Matrix4 tempMat = m;
    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j) {
        m[i][j] = tempMat.m[j][i];
      }
    }
    
  }
}