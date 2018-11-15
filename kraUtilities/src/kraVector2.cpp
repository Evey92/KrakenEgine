#include "kraVector2.h"
#include "kraVector3.h"

namespace kraEngineSDK {
  /***************************************************************************/
  /**
   * Funciones de Vector2
   */
   /***************************************************************************/

  Vector2::Vector2(float X, float Y) : x(X), y(Y) {}

  Vector2
    Vector2::operator+(const Vector2& Vec)const {
    Vector2 newVec;
    newVec.x = x + Vec.x;
    newVec.y = y + Vec.y;

    return newVec;
  }

  Vector2
    Vector2::operator-(const Vector2& Vec)const {
    Vector2 newVec;
    newVec.x = x - Vec.x;
    newVec.y = y - Vec.y;

    return newVec;
  }

  Vector2
    Vector2::operator*(float Val)const {
    Vector2 newVec;
    newVec.x = x * Val;
    newVec.y = y * Val;

    return newVec;
  }

  Vector2
    Vector2::operator/(float Val)const {
    Vector2 newVec;
    newVec.x = x / Val;
    newVec.y = y / Val;

    return newVec;
  }

  Vector2
    Vector2::operator+(float Val)const {
    Vector2 newVec;
    newVec.x = x + Val;
    newVec.y = y + Val;

    return newVec;
  }

  Vector2
    Vector2::operator-(float Val)const {
    Vector2 newVec;
    newVec.x = x - Val;
    newVec.y = y - Val;

    return newVec;
  }

  Vector2
    Vector2::operator*(const Vector2& Vec)const {
    Vector2 newVec;
    newVec.x = x * Vec.x;
    newVec.y = y * Vec.y;

    return newVec;
  }

  Vector2
    Vector2::operator/(const Vector2& Vec)const {
    Vector2 newVec;
    newVec.x = x / Vec.x;
    newVec.y = y / Vec.y;

    return newVec;
  }

  float
    Vector2::operator|(const Vector2& Vec)const {

    float escalar = (x * Vec.x) + (y * Vec.y);

    return escalar;
  }

  float
    Vector2::operator^(const Vector2 Vec)const {

    //Sacando eje de rotación 2D en un espacio 3D http://allenchou.net/2013/07/cross-product-of-2d-vectors/
    float escalar = (x * Vec.y) - (y * Vec.x);

    return escalar;

  }

  bool
    Vector2::operator==(const Vector2& Vec) const {

    return x == Vec.x && y == Vec.y;

  }

  bool
    Vector2::operator!=(const Vector2& Vec) const {
    return x != Vec.x || y != Vec.y;
  }

  bool
    Vector2::operator<(const Vector2& Vec) const {

    return x < Vec.x && y < Vec.y;

  }

  bool
    Vector2::operator>(const Vector2& Vec) const {
    return x > Vec.x && y > Vec.y;
  }

  bool
    Vector2::operator<=(const Vector2& Vec) const {

    return x <= Vec.x && y <= Vec.y;

  }

  bool
    Vector2::operator>=(const Vector2& Vec) const {

    return x >= Vec.x && y >= Vec.y;

  }

  Vector2
    Vector2::operator-() const {

    return Vector2(-x, -y);

  }

  Vector2&
    Vector2::operator+=(const Vector2& Vec) {
    x += Vec.x;
    y += Vec.y;
    return *this;
  }

  Vector2&
    Vector2::operator-=(const Vector2& Vec) {
    x -= Vec.x;
    y -= Vec.y;
    return *this;
  }

  Vector2&
    Vector2::operator*=(float Val) {
    x *= Val;
    y *= Val;
    return *this;
  }

  Vector2&
    Vector2::operator*=(const Vector2& Vec) {
    x *= Vec.x;
    y *= Vec.y;
    return *this;
  }

  Vector2&
    Vector2::operator/=(float Val) {
    x /= Val;
    y /= Val;
    return *this;
  }

  Vector2
    Vector2::operator/=(const Vector2& Vec) {
    x /= Vec.x;
    y /= Vec.y;
    return *this;
  }

  float
    Vector2::lenght() const {

    return kraMath::sqrt(x*x + y * y);

  }

  float
    Vector2::lenghtSquared() const {

    return kraMath::powf(kraMath::sqrt(x*x + y * y), 2.0f);

  }

  float
    Vector2::dot(Vector2& V1, Vector2& V2) {
    return V1 | V2;
  }

  float
    Vector2::cross(Vector2& V1, Vector2& V2) {
    return V1 ^ V2;
  }

  float
    Vector2::distance(const Vector2& V1, const Vector2& V2) {
    return kraMath::sqrt(kraMath::pow((V1.x - V2.x), 2.0f) + kraMath::pow((V1.y - V2.y), 2.0f));
  }

  void
    Vector2::normalize() {
    float vec = kraMath::sqrt(x*x + y * y);
    x /= vec;
    y /= vec;
  }

  void
    Vector2::floor() {
    kraMath::floor(x);
    kraMath::floor(y);
  }

  void
    Vector2::ceil() {
    kraMath::ceil(x);
    kraMath::ceil(y);
  }

  float&
    Vector2::operator[](uint32 Index) {

    if (Index == 0) {
      return x;
    }
    else if (Index == 1) {
      return y;
    }
  }

  float
    Vector2::operator[](uint32 Index) const {

    if (Index == 0) {
      return x;
    }
    else if (Index == 1) {
      return y;
    }
  }

  float&
    Vector2::component(uint32 Index) {

    if (Index == 0) {
      return x;
    }
    else if (Index == 1) {
      return y;
    }
  }

  float
    Vector2::component(uint32 Index) const {

    if (Index == 0) {
      return x;
    }
    else if (Index == 1) {
      return y;
    }
  }
}

