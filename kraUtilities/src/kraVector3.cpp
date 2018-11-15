#include "kraVector3.h"


/***************************************************************************/
/**
 * Funciones de Vector3
 */
 /***************************************************************************/
namespace kraEngineSDK {
  Vector3::Vector3(float X, float Y, float Z) : x(X), y(Y), z(Z) {}

  Vector3
    Vector3::operator+(const Vector3& Vec)const {

    Vector3 newVec;
    newVec.x = x + Vec.x;
    newVec.y = y + Vec.y;
    newVec.z = z + Vec.z;

    return newVec;
  }

  Vector3
    Vector3::operator-(const Vector3& Vec)const {

    Vector3 newVec;
    newVec.x = x - Vec.x;
    newVec.y = y - Vec.y;
    newVec.z = z - Vec.z;

    return newVec;
  }

  Vector3
    Vector3::operator*(float Val)const {

    Vector3 newVec;
    newVec.x = x * Val;
    newVec.y = y * Val;
    newVec.z = z * Val;

    return newVec;
  }

  Vector3
    Vector3::operator/(float Val)const {

    Vector3 newVec;
    newVec.x = x / Val;
    newVec.y = y / Val;
    newVec.z = z / Val;

    return newVec;
  }

  Vector3
    Vector3::operator+(float Val)const {

    Vector3 newVec;
    newVec.x = x + Val;
    newVec.y = y + Val;
    newVec.z = z + Val;

    return newVec;
  }

  Vector3
    Vector3::operator-(float Val)const {

    Vector3 newVec;
    newVec.x = x - Val;
    newVec.y = y - Val;
    newVec.z = z - Val;

    return newVec;
  }

  Vector3
    Vector3::operator*(const Vector3& Vec)const {

    Vector3 newVec;
    newVec.x = x * Vec.x;
    newVec.y = y * Vec.y;
    newVec.z = z * Vec.z;

    return newVec;
  }

  Vector3
    Vector3::operator/(const Vector3& Vec)const {

    Vector3 newVec;
    newVec.x = x / Vec.x;
    newVec.y = y / Vec.y;
    newVec.z = z / Vec.z;

    return newVec;
  }

  float
    Vector3::operator|(const Vector3& Vec)const {

    float escalar = (x * Vec.x) + (y * Vec.y) + (z * Vec.z);

    return escalar;
  }

  Vector3
    Vector3::operator^(const Vector3 Vec)const {

    return Vector3((y * Vec.z - z * Vec.y), (z * Vec.x - x * Vec.z), (x * Vec.y - y * Vec.x));

  }

  bool
    Vector3::operator==(const Vector3& Vec) const {

    return x == Vec.x && y == Vec.y && z == Vec.z;

  }

  bool
    Vector3::operator!=(const Vector3& Vec) const {
    return x != Vec.x || y != Vec.y || z != Vec.z;
  }

  bool
    Vector3::operator<(const Vector3& Vec) const {

    return x < Vec.x && y < Vec.y && z < Vec.z;

  }

  bool
    Vector3::operator>(const Vector3& Vec) const {
    return x > Vec.x && y > Vec.y && z > Vec.z;
  }

  bool
    Vector3::operator<=(const Vector3& Vec) const {

    return x <= Vec.x && y <= Vec.y && z <= Vec.z;

  }

  bool
    Vector3::operator>=(const Vector3& Vec) const {

    return x >= Vec.x && y >= Vec.y && z >= Vec.z;

  }

  Vector3
    Vector3::operator-() const {

    return Vector3(-x, -y, -z);

  }

  Vector3
    Vector3::operator+=(const Vector3& Vec) {
    x += Vec.x;
    y += Vec.y;
    z += Vec.z;

    return *this;
  }

  Vector3
    Vector3::operator-=(const Vector3& Vec) {
    x -= Vec.x;
    y -= Vec.y;
    z -= Vec.z;

    return *this;
  }

  Vector3
    Vector3::operator*=(float Val) {
    x *= Val;
    y *= Val;
    z *= Val;

    return *this;
  }

  Vector3
    Vector3::operator*=(const Vector3& Vec) {
    x *= Vec.x;
    y *= Vec.y;
    z *= Vec.z;

    return *this;
  }

  Vector3
    Vector3::operator/=(float Val) {
    x /= Val;
    y /= Val;
    z /= Val;

    return *this;
  }

  Vector3
    Vector3::operator/=(const Vector3& Vec) {
    x /= Vec.x;
    y /= Vec.y;
    z /= Vec.z;

    return *this;
  }

  float
    Vector3::lenght() const {

    return kraMath::sqrt(x*x + y * y + z * z);

  }

  float
    Vector3::lenghtSquared() const {

    return kraMath::powf(kraMath::sqrt(x*x + y * y + z * z), 2.0f);

  }

  float
    Vector3::dot(Vector3& V1, Vector3& V2) {
    return V1 | V2;
  }

  Vector3
    Vector3::cross(Vector3& V1, Vector3& V2) {
    return V1 ^ V2;
  }

  float
    Vector3::distance(const Vector3& V1, const Vector3& V2) {

    return kraMath::sqrt(kraMath::pow((V1.x - V2.x), 2.0f) + kraMath::pow((V1.y - V2.y), 2.0f) + kraMath::pow((V1.z - V2.z), 2.0f));

  }

  void
    Vector3::normalize() {
    float vec = kraMath::sqrt(x*x + y * y + z * z);
    x /= vec;
    y /= vec;
    z /= vec;
  }

  void
    Vector3::floor() {
    kraMath::floor(x);
    kraMath::floor(y);
    kraMath::floor(z);
  }

  void
    Vector3::ceil() {
    kraMath::ceil(x);
    kraMath::ceil(y);
    kraMath::ceil(z);
  }

  float&
    Vector3::operator[](uint32 Index) {

    if (Index == 0) {
      return x;
    }
    else if (Index == 1) {
      return y;
    }
    else if (Index == 2) {
      return z;
    }
  }

  float
    Vector3::operator[](uint32 Index) const {

    if (Index == 0) {
      return x;
    }
    else if (Index == 1) {
      return y;
    }
    else if (Index == 2) {
      return z;
    }
  }

  float&
    Vector3::component(uint32 Index) {

    if (Index == 0) {
      return x;
    }
    else if (Index == 1) {
      return y;
    }
    else if (Index == 2) {
      return z;
    }
  }

  float
    Vector3::component(uint32 Index) const {

    if (Index == 0) {
      return x;
    }
    else if (Index == 1) {
      return y;
    }
    else if (Index == 2) {
      return z;
    }
  }
}
