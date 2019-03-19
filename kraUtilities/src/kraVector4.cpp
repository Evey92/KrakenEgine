#include "kraVector2.h"
#include "kraVector3.h"
#include "kraVector4.h"

namespace kraEngineSDK {

  /***************************************************************************/
  /**
   * Funciones de Vector4
   */
   /***************************************************************************/
  Vector4::Vector4(const Vector4& copyVec) {
    x = copyVec.x;
    y = copyVec.y;
    z = copyVec.z;
    w = copyVec.w;
  }


  Vector4::Vector4(float X, float Y, float Z, float W) : x(X), y(Y), z(Z), w(W) {}

  Vector4::Vector4(Vector3 vecXYZ, float w) {
    x = vecXYZ.x;
    y = vecXYZ.y;
    z = vecXYZ.z;
    w = w;
  }

  Vector4::Vector4(Vector3 vecXYZ) {
    x = vecXYZ.x;
    y = vecXYZ.y;
    z = vecXYZ.z;
    w = 0.0f;
  }

  Vector4::Vector4(Vector2 vecXY) {
    x = vecXY.x;
    y = vecXY.y;
    z = 0.0f;
    w = 0.0f;
  }

  Vector4
    Vector4::operator+(const Vector4& Vec)const {
    Vector4 newVec;
    newVec.x = x + Vec.x;
    newVec.y = y + Vec.y;
    newVec.z = z + Vec.z;
    newVec.w = w + Vec.w;

    return newVec;
  }

  Vector4
    Vector4::operator-(const Vector4& Vec)const {
    Vector4 newVec;
    newVec.x = x - Vec.x;
    newVec.y = y - Vec.y;
    newVec.z = z - Vec.z;
    newVec.w = w - Vec.w;

    return newVec;
  }

  Vector4
    Vector4::operator*(float Val)const {
    Vector4 newVec;
    newVec.x = x * Val;
    newVec.y = y * Val;
    newVec.z = z * Val;
    newVec.w = w * Val;

    return newVec;
  }

  Vector4
    Vector4::operator/(float Val)const {
    Vector4 newVec;
    newVec.x = x / Val;
    newVec.y = y / Val;
    newVec.z = z / Val;
    newVec.w = w / Val;

    return newVec;
  }

  Vector4
    Vector4::operator+(float Val)const {
    Vector4 newVec;
    newVec.x = x + Val;
    newVec.y = y + Val;
    newVec.z = z + Val;
    newVec.w = w + Val;

    return newVec;
  }

  Vector4
    Vector4::operator-(float Val)const {
    Vector4 newVec;
    newVec.x = x - Val;
    newVec.y = y - Val;
    newVec.z = z - Val;
    newVec.w = w - Val;


    return newVec;
  }

  Vector4
    Vector4::operator*(const Vector4& Vec)const {
    Vector4 newVec;
    newVec.x = x * Vec.x;
    newVec.y = y * Vec.y;
    newVec.z = z * Vec.z;
    newVec.w = w * Vec.z;

    return newVec;
  }

  Vector4
    Vector4::operator/(const Vector4& Vec)const {
    Vector4 newVec;
    newVec.x = x / Vec.x;
    newVec.y = y / Vec.y;
    newVec.z = z / Vec.z;
    newVec.w = w / Vec.w;

    return newVec;
  }

  float
  Vector4::operator|(const Vector4& Vec)const {

    return (x * Vec.x) + (y * Vec.y) + (z * Vec.z) + (w * Vec.w);

  }

  Vector4
  Vector4::operator^(const Vector4 Vec)const {
    Vector4 newVec;

    newVec.x = (y * Vec.z) - (z * Vec.y);
    newVec.y = (z * Vec.x) - (x * Vec.z);
    newVec.z = (x * Vec.y) - (y * Vec.x);
    
    return newVec;

  }

  bool
    Vector4::operator==(const Vector4& Vec) const {

    return x == Vec.x && y == Vec.y && z == Vec.z && w == Vec.w;

  }

  bool
    Vector4::operator!=(const Vector4& Vec) const {
    return x != Vec.x || y != Vec.y || z != Vec.z || w != Vec.w;
  }

  bool
    Vector4::operator<(const Vector4& Vec) const {

    return x < Vec.x && y < Vec.y && z < Vec.z && w < Vec.w;

  }

  bool
    Vector4::operator>(const Vector4& Vec) const {
    return x > Vec.x && y > Vec.y && z > Vec.z && w > Vec.w;
  }

  bool
    Vector4::operator<=(const Vector4& Vec) const {

    return x <= Vec.x && y <= Vec.y && z <= Vec.z && w <= Vec.w;

  }

  bool
    Vector4::operator>=(const Vector4& Vec) const {

    return x >= Vec.x && y >= Vec.y && z >= Vec.z && w >= Vec.w;

  }

  Vector4&
  Vector4::operator-() const {

    return Vector4(-x, -y, -z, -w);

  }

  Vector4&
    Vector4::operator+=(const Vector4& Vec) {
    x += Vec.x;
    y += Vec.y;
    z += Vec.z;
    w += Vec.w;
    return *this;
  }

  Vector4&
    Vector4::operator-=(const Vector4& Vec) {
    x -= Vec.x;
    y -= Vec.y;
    z -= Vec.z;
    w -= Vec.w;
    return *this;
  }

  Vector4&
    Vector4::operator*=(float Val) {
    x *= Val;
    y *= Val;
    z *= Val;
    w *= Val;
    return *this;
  }

  Vector4&
  Vector4::operator*=(const Vector4& Vec) {
    x *= Vec.x;
    y *= Vec.y;
    z *= Vec.z;
    w *= Vec.w;
    return *this;
  }

  Vector4&
    Vector4::operator/=(float Val) {
    x /= Val;
    y /= Val;
    z /= Val;
    w /= Val;
    return *this;
  }

  Vector4&
    Vector4::operator/=(const Vector4& Vec) {
    x /= Vec.x;
    y /= Vec.y;
    z /= Vec.z;
    w /= Vec.w;
    return *this;
  }

  float
  Vector4::lenght() const {

    return kraMath::sqrt((x * x) + (y * y) + (z * z) + (w * w));
  }

  float
    Vector4::lenghtSquared() const {

    return kraMath::powf(kraMath::sqrt(x*x + y * y + z * z + w * w), 2.0f);

  }

  float
  Vector4::dot(Vector4& V1, Vector4& V2) {
    return V1 | V2;
  }

  Vector4
  Vector4::cross(Vector4& V1, Vector4& V2) {
    return V1 ^ V2;
  }

  float
  Vector4::distance(const Vector4& V1, const Vector4& V2) {

    return kraMath::sqrt(kraMath::pow((V1.x - V2.x), 2.0f) + kraMath::pow((V1.y - V2.y), 2.0f) + kraMath::pow((V1.z - V2.z), 2.0f) + kraMath::pow((V1.w - V2.w), 2.0f));

  }

  Vector4
  Vector4::normalize(Vector4 newVec) {

    float m = newVec.lenght();
    newVec.x /= m;
    newVec.y /= m;
    newVec.z /= m;
    newVec.w /= m;

    return newVec;
  }

  void
  Vector4::normalized() {
    
    float m = lenght();

    float fisqrt = kraMath::invSqrt(m);

    x *= fisqrt;
    y *= fisqrt;
    z *= fisqrt;
    w *= fisqrt;
  }

  void
    Vector4::floor() {
    kraMath::floor(x);
    kraMath::floor(y);
    kraMath::floor(z);
    kraMath::floor(w);
  }

  void
    Vector4::ceil() {
    kraMath::ceil(x);
    kraMath::ceil(y);
    kraMath::ceil(z);
    kraMath::ceil(w);
  }

  float&
    Vector4::operator[](uint32 Index) {

    if (Index == 0) {
      return x;
    }
    else if (Index == 1) {
      return y;
    }
    else if (Index == 2) {
      return z;
    }
    else if (Index == 3) {
      return w;
    }
  }

  float
    Vector4::operator[](uint32 Index) const {

    if (Index == 0) {
      return x;
    }
    else if (Index == 1) {
      return y;
    }
    else if (Index == 2) {
      return z;
    }
    else if (Index == 3) {
      return w;
    }
  }

  float&
    Vector4::component(uint32 Index) {

    if (Index == 0) {
      return x;
    }
    else if (Index == 1) {
      return y;
    }
    else if (Index == 2) {
      return z;
    }
    else if (Index == 3) {
      return w;
    }
  }

  float
  Vector4::component(uint32 Index) const {

    if (Index == 0) {
      return x;
    }
    else if (Index == 1) {
      return y;
    }
    else if (Index == 2) {
      return z;
    }
    else if (Index == 3) {
      return w;
    }

    static const Vector4 ZERO = Vector3(0.0f, 0.0f, 0.0f);

    static const Vector4 ONE = Vector3(1.0f, 1.0f, 1.0f);

    static const Vector4 ONEX = Vector3(1.0f, 0.0f, 0.0f);

    static const Vector4 ONEY = Vector3(0.0f, 1.0f, 0.0f);

    static const Vector4 ONEZ = Vector3(0.0f, 0.0f, 1.0f);

    static const Vector4 UP = ONEY;

    static const Vector4 FRONT = ONEZ;

  }

}
