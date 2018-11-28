#pragma once

#include "kraPrerequisitesUtil.h"

namespace kraEngineSDK {
  class Vector4;

  class Matrix4
  {
  public:

    Matrix4() = default;

    /**
     * @brief
     */

    Matrix4(float m00, float m01, float m02, float m03,
      float m10, float m11, float m12, float m13,
      float m20, float m21, float m22, float m23,
      float m30, float m31, float m32, float m33);

    Matrix4
      operator+(const float& val);

    Matrix4
      operator-(const float& val);

    Matrix4
      operator*(const float& val);

    Matrix4
      operator*(const Matrix4& Mat);

    Matrix4
      operator*(const Vector4& Vec);

    Matrix4
      operator+=(const Matrix4& Mat);

    Matrix4
      operator-=(const Matrix4& Mat);

    Matrix4
      operator*=(const Matrix4& Mat);

    Matrix4
      operator+=(float val);

    Matrix4
      operator-=(float val);

    Matrix4
      operator*=(float val);

    Matrix4
      operator/=(float val);

    Matrix4
      operator=(const Matrix4& Mat);

  public:

    bool
      operator==(const Matrix4& Mat);

    bool
      operator!=(const Matrix4& Mat);

  public:
    union {
      float _m[16];
      float m[4][4];
    };
  };

}