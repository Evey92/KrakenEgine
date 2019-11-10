#pragma once

#include "kraPrerequisitesUtil.h"
#include "kraVector4.h"

namespace kraEngineSDK {
class Vector2;
class Vector3;

  class KRA_UTILITY_EXPORT Matrix4
  {
   public:
    
    Matrix4();
    
    /**
      * @brief All docs are on english at least!!!
      */

    Matrix4(float m00, float m10, float m20, float m30,
            float m01, float m11, float m21, float m31,
            float m02, float m12, float m22, float m32,
            float m03, float m13, float m23, float m33);

    Matrix4(const Matrix4& mat);


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

    static Matrix4
    MatrixLookAtLH(const Vector3& Eye, const Vector3& At, const Vector3& Up);

    static Matrix4
    MatrixLookAtRH(const Vector3& Eye, const Vector3& At, const Vector3& Up);

    void 
    MatrixPerspectiveFOVLH(float FOV, float width, float height, float nearZ, float farZ);

    void
    MatrixPerspectiveFOVRH(float FOV, float width, float height, float nearZ, float farZ);

    void
    MatrixRotX(float angle);

    void
    MatrixRotY(float angle);

    void
    MatrixRotZ(float angle);

    static Matrix4
    eulerAngleXY(float angleX, float angleY);

    /**
      * @brief Transpose *this
      */
    void
    transpose();

    /**
      * @brief Return a new transposed matrix from a source matirx
      */
    static Matrix4
    transposed(const Matrix4& mat);

   
    void 
    tranlsate();
    
   public:

    bool
    operator==(const Matrix4& Mat);

    bool
    operator!=(const Matrix4& Mat);

   public:
    static  Matrix4 IDENTITY;
    static  Matrix4 ZERO;

    union {

      struct {
        float m00, m10, m20, m30;
        float m01, m11, m21, m31;
        float m02, m12, m22, m32;
        float m03, m13, m23, m33;
      }_m;
      float matVec[16];
      float m[4][4];
      Vector4 row[4]; 
    };
  };
}
