#pragma once

#include "kraPrerequisitesUtil.h"
#include "kraVector4.h"

namespace kraEngineSDK {
  class Vector4;

  class KRA_UTILITY_EXPORT Matrix4
  {
   public:
    
    Matrix4() = default;
    
    /**
     * @brief All docs are on english at least!!!
     */

    Matrix4(float m00, float m01, float m02, float m03,
            float m10, float m11, float m12, float m13,
            float m20, float m21, float m22, float m23,
            float m30, float m31, float m32, float m33);

    Matrix4(const Matrix4& mat);

    Matrix4(float mat[4][4]);

    Matrix4
    operator+(const float& val);

    Matrix4
    operator-(const float& val);

    Matrix4
    operator*(const float& val);

    Matrix4
    operator*(const Matrix4& Mat);

    /*Matrix4
    operator*(const Vector4& Vec);*/

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

    void
    identity();

    Matrix4
    MatrixLookAtLH(Vector4 Eye, Vector4 At, Vector4 Up);

    void
    transpose();

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
