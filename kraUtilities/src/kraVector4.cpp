#include "kraVector4.h"

namespace kraEngineSDK {

  /***************************************************************************/
  /**
   * Funciones de Vector4
   */
   /***************************************************************************/

  Vector4::Vector4(float X, float Y, float Z, float W) : x(X), y(Y), z(Z), w(W) {}

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

    float escalar = (x * Vec.x) + (y * Vec.y) + (z * Vec.z) + (w * Vec.w);

    return escalar;
  }

  Vector4
  Vector4::operator^(const Vector4 Vec)const {

    return Vector4((y * Vec.z - z * Vec.y), (z * Vec.x - x * Vec.z), (x * Vec.y - y * Vec.x), 0.0f);

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

  /*Vector4
    Vector4::operator-() const {

    return Vector4(-x, -y, -z, -w);

  }*/

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

    return kraMath::sqrt(x*x + y * y + z * z + w * w);

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

  void
    Vector4::normalize() {
    float vec = kraMath::sqrt(x*x + y * y + z * z + w * w);
    x /= vec;
    y /= vec;
    z /= vec;
    w /= vec;
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
  }

}
