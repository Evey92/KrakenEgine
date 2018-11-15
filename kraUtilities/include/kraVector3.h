#pragma once

#include "kraPrerequisitesUtil.h"
#include "kraMath.h"
#include "kraVector2.h"

namespace kraEngineSDK {

  class KRA_UTILITY_EXPORT Vector3
  {
    /**
     * @brief Constructors.
     */
   public:

    /**
     * @brief Default constructor, no initialization.
     */
    Vector3() = default;

    /**
     * @brief Constructor with initialized X & Y values.
     */
    Vector3(float X, float Y, float Z);


    /**
     * @brief Construct a Vector3 from the X & Y components from a Vector4.
     */     
    explicit inline Vector3(const Vector3& V, float w);
    
    /**
    * @brief Operator Overloads.
    */

   public:

    /**
    * @brief Obtiene el resultado de sumar los componentes de 2 vectores.
    * @param Vec es el segundo vector que se le suma a este vector.
    * @return Regresa el resultado de la suma.
    */
    Vector3
    operator+(const Vector3& Vec) const;

    /**
     * @brief Obtiene el resultado de restar los componentes de 2 vectores.
     * @param Vec es el segundo vector que se le resta a este vector.
     * @return Regresa el resultado de la resta.
     */

    Vector3 
    operator-(const Vector3& Vec) const;

    /**
     * @brief Obtiene el resultado de escalar los componentes de un vector.
     * @param Scale es por cuanto se va a escalar el vector.
     * @return Regresa el resultado de escalar este vector.
     */
    Vector3
    operator*(float Scale) const;

    /**
     * @brief Obtiene el resultado de dividir los componentes un vector por un valor.
     * @param Scale es el valor que se le resta a este vector.
     * @return Regresa el resultado de la division.
     */
    Vector3
    operator/(float Scale) const;

    /**
     * @brief Obtiene el resultado de sumarle un valor a los componentes del vector.
     * @param Val es el valor que se le suma a los componentes de este vector.
     * @return Regresa el resultado de la suma.
     */
    Vector3
    operator+(float Val) const;

    /**
     * @brief Obtiene el resultado de restar un valor a los componentes del vector.
     * @param Val es el valor que se le resta a los componentes de este vector.
     * @return Regresa el resultado de la resta.
     */
    Vector3
    operator-(float Val) const;

    /**
     * @brief Obtiene el resultado de multiplicar los componentes de dos vectores.
     * @param Vec es el segundo vector por el cuál sde va multiplicar.
     * @return Regresa el resultado de la multiplicación de los vectores.
     */
    Vector3
    operator*(const Vector3& Vec) const;

    /**
     * @brief Obtiene el resultado de dividir los componentes de dos vectores.
     * @param Vec es el segundo vector por el cuál de va dividir.
     * @return Regresa el resultado de la división de los vectores.
     */
    Vector3
    operator/(const Vector3& Vec) const;

    /**
     * @brief Obtiene el producto punto de este vector y otro.
     * @param Vec es el segundo vector para calcuilar el producto punto.
     * @return Regresa el producto punto.
     */
    float
    operator|(const Vector3& Vec) const;

    /**
     * @brief Obtiene el producto cruz de este vector y otro.
     * @param Vec es el segundo vector para calcuilar el producto cruz.
     * @return Regresa el producto cruz.
     */
    Vector3
    operator^(const Vector3 Vec)const;

    /**
     * @brief Overload de operadores booleanos.
     */
   public:

    /**
     * @brief Compara 2 vectores para ver si sus componentes son iguales.
     * @param Vec es el segundo vector contra el que se va a comparar.
     * @return Regresa true si son iguales, y false si no lo son.
     */
    bool
    operator==(const Vector3& Vec) const;

    /**
     * @brief Compara 2 vectores para ver si sus componentes son diferentes.
     * @param Vec es el segundo vector contra el que se va a comparar.
     * @return Regresa true si son diferentes, y false si no lo son.
     */
    bool
    operator!=(const Vector3& Vec) const;

    /**
     * @brief Compara 2 vectores para ver si los componentes de uno son menores que el otro.
     * @param Vec es el segundo vector contra el que se va a comparar.
     * @return Regresa true si este vector es menor, y false si no lo es.
     */
    bool
    operator<(const Vector3& Vec) const;

    /**
     * @brief Compara 2 vectores para ver si los componentes de uno son mayores que el otro.
     * @param Vec es el segundo vector contra el que se va a comparar.
     * @return Regresa true si este vector es mayor que el otro, y false si no lo es.
     */
    bool
    operator>(const Vector3& Vec) const;

    /**
     * @brief Compara 2 vectores para ver si los componentes de uno son menores o iguales que el otro.
     * @param Vec es el segundo vector contra el que se va a comparar.
     * @return Regresa true si este vector es menor o igual que el otro, y false si no lo es.
     */
    bool
    operator<=(const Vector3& Vec) const;

    /**
     * @brief Compara 2 vectores para ver si los componentes de uno son mayores o iguales que el otro.
     * @param Vec es el segundo vector contra el que se va a comparar.
     * @return Regresa true si este vector es mayor o igual que el otro, y false si no lo es.
     */
    bool
    operator>=(const Vector3& Vec) const;

    /**
     * @brief Vuelve los componentes de este vector negativos.
     * @param el mismo vector.
     * @return Regresa una copia de vector resultado.
     */
    Vector3
    operator-() const;

    /**
     * @brief Le suma un vetor secundario a este mismo vetcor.
     * @param Vec es el segundo vector que se va a sumar.
     * @return Regresa una copia de vector resultado.
     */
    Vector3
    operator+=(const Vector3& Vec);

    /**
     * @brief Le resta un vetor secundario a este mismo vetcor.
     * @param Vec es el segundo vector que se va a restar.
     * @return Regresa una copia del vector resultado.
     */
    Vector3
    operator-=(const Vector3& Vec);

    /**
     * @brief Multiplica los componentes de este mismo vector por un valor
     * @param Val es el valor a multiplicar el vector.
     * @return Regresa una copia del vector resultado.
     */
    Vector3
    operator*=(float Val);

    /**
     * @brief Multiplica los componentes de este mismo vector por otro vector
     * @param Vec es el vector que multiplica este vector.
     * @return Regresa una copia del vector resultado.
     */
    Vector3
    operator*=(const Vector3& Vec);

    /**
     * @brief Divide los componentes de este mismo vector por un valor
     * @param Val es el valor a dividir el vector.
     * @return Regresa una copia del vector resultado.
     */
    Vector3
    operator/=(float Val);

    /**
     * @brief Divide los componentes de este mismo vector por otro vector
     * @param Vec es el otro vector para dividir este vector.
     * @return Regresa una copia del vector resultado.
     */
    Vector3
    operator/=(const Vector3& Vec);

    /**
    * Funciones para accesar a los componentes individuales del vector
    */

    /**
     * @brief Obtiene uno de los componentes del vector basado en un índice.
     * @param Index el indice del componente a obtener.
     * @return referencia al componente.
     */
    float&
    operator[](uint32 Index);

    /**
     * @brief Obtiene uno de los componentes del vector basado en un índice.
     * @param Index el indice del componente a obtener.
     * @return Copia del valor del componente.
     */
    float
    operator[](uint32 Index) const;

    /**
     * @brief Obtiene uno de los componentes del vector basado en un índice.
     * @param  Index el indice del componente a obtener.
     * @return referencia al componente.
     */
    float&
    component(uint32 Index);

    /**
     * @brief Obtiene uno de los componentes del vector basado en un índice.
     * @param  Index el indice del componente a obtener.
     * @return Copia del valor del componente.
     */
    float
    component(uint32 Index) const;



    /**
     * @brief Obtiene el tamaño o magnitud de un vector.
     * @return Regresa el tamaño del vector.
     */
    float
    lenght() const;

    /**
     * @brief Obtiene el cuadrado del tamaño o magnitud de un vector.
     * @return Regresa el tamaño del vector.
     */
    float
    lenghtSquared() const;

    /**
     * @brief Obtiene el cuadrado del tamaño o magnitud de un vector.
     * @return Regresa el tamaño del vector.
     */
    static float
    dot(Vector3& V1, Vector3& V2);

    /**
     * @brief Obtiene el cuadrado del tamaño o magnitud de un vector.
     * @return Regresa el tamaño del vector.
     */
    static Vector3
    cross(Vector3& V1, Vector3& V2);

    /**
     * @brief Obtiene la distancia enrtre 2 vectores.
     * @param Los dos vectores.
     * @return Regresa la distancia entre esos dos vectores.
     */
    float
      distance(const Vector3& V1, const Vector3& V2);

    /**
     * @brief Normaliza el vector.
     * @return Regresa el vector normalizado.
     */
    void
      normalize();

    void
      floor();

    void
      ceil();

   public:
    /**
     * @brief Componente X.
     */
    float x;
    /**
     * @brief Componente Y.
     */
    float y;
    /**
     * @brief Componente Z.
     */
    float z;

  };

  ///***************************************************************************/
  ///**
  // * Funciones de Vector3
  // */
  // /***************************************************************************/

  //Vector3::Vector3(float X, float Y, float Z) : x(X), y(Y), z(Z) {}

  //Vector3
  //  Vector3::operator+(const Vector3& Vec)const {
  //  Vector3 newVec;
  //  newVec.x = x + Vec.x;
  //  newVec.y = y + Vec.y;
  //  newVec.z = z + Vec.z;

  //  return newVec;
  //}

  //Vector3
  //  Vector3::operator-(const Vector3& Vec)const {
  //  Vector3 newVec;
  //  newVec.x = x - Vec.x;
  //  newVec.y = y - Vec.y;
  //  newVec.z = z - Vec.z;

  //  return newVec;
  //}

  //Vector3
  //  Vector3::operator*(float Val)const {
  //  Vector3 newVec;
  //  newVec.x = x * Val;
  //  newVec.y = y * Val;
  //  newVec.z = z * Val;

  //  return newVec;
  //}

  //Vector3
  //  Vector3::operator/(float Val)const {
  //  Vector3 newVec;
  //  newVec.x = x / Val;
  //  newVec.y = y / Val;
  //  newVec.z = z / Val;

  //  return newVec;
  //}

  //Vector3
  //  Vector3::operator+(float Val)const {
  //  Vector3 newVec;
  //  newVec.x = x + Val;
  //  newVec.y = y + Val;
  //  newVec.z = z + Val;

  //  return newVec;
  //}

  //Vector3
  //  Vector3::operator-(float Val)const {
  //  Vector3 newVec;
  //  newVec.x = x - Val;
  //  newVec.y = y - Val;
  //  newVec.z = z - Val;

  //  return newVec;
  //}

  //Vector3
  //  Vector3::operator*(const Vector3& Vec)const {
  //  Vector3 newVec;
  //  newVec.x = x * Vec.x;
  //  newVec.y = y * Vec.y;
  //  newVec.z = z * Vec.z;

  //  return newVec;
  //}

  //Vector3
  //Vector3::operator/(const Vector3& Vec)const {
  //  Vector3 newVec;
  //  newVec.x = x / Vec.x;
  //  newVec.y = y / Vec.y;
  //  newVec.z = z / Vec.z;

  //  return newVec;
  //}

  //float
  //Vector3::operator|(const Vector3& Vec)const {

  //  float escalar = (x * Vec.x) + (y * Vec.y) + (z * Vec.z);

  //  return escalar;
  //}

  //Vector3
  //Vector3::operator^(const Vector3& Vec)const {

  //  return Vector3((y * Vec.z - z * Vec.y), (z * Vec.x - x * Vec.z), (x * Vec.y - y * Vec.x));

  //}

  //bool
  //Vector3::operator==(const Vector3& Vec) const {

  //  return x == Vec.x && y == Vec.y && z == Vec.z;

  //}

  //bool
  //  Vector3::operator!=(const Vector3& Vec) const {
  //  return x != Vec.x || y != Vec.y || z != Vec.z;
  //}

  //bool
  //  Vector3::operator<(const Vector3& Vec) const {

  //  return x < Vec.x && y < Vec.y && z < Vec.z;

  //}

  //bool
  //  Vector3::operator>(const Vector3& Vec) const {
  //  return x > Vec.x && y > Vec.y && z > Vec.z;
  //}

  //bool
  //  Vector3::operator<=(const Vector3& Vec) const {

  //  return x <= Vec.x && y <= Vec.y && z <= Vec.z;

  //}

  //bool
  //  Vector3::operator>=(const Vector3& Vec) const {

  //  return x >= Vec.x && y >= Vec.y && z >= Vec.z;

  //}

  //Vector3
  //  Vector3::operator-() const {

  //  return Vector3(-x, -y, -z);

  //}

  //Vector3
  //  Vector3::operator+=(const Vector3& Vec) {
  //  x += Vec.x;
  //  y += Vec.y;
  //  z += Vec.z;
  //  return *this;
  //}

  //Vector3
  //  Vector3::operator-=(const Vector3& Vec) {
  //  x -= Vec.x;
  //  y -= Vec.y;
  //  z -= Vec.z;
  //  return *this;
  //}

  //Vector3
  //Vector3::operator*=(float Val) {
  //  x *= Val;
  //  y *= Val;
  //  z *= Val;
  //  return *this;
  //}

  //Vector3
  //Vector3::operator*=(const Vector3& Vec) {
  //  x *= Vec.x;
  //  y *= Vec.y;
  //  z *= Vec.z;
  //  return *this;
  //}

  //Vector3
  //Vector3::operator/=(float Val) {
  //  x /= Val;
  //  y /= Val;
  //  z /= Val;
  //  return *this;
  //}

  //Vector3
  //  Vector3::operator/=(const Vector3& Vec) {
  //  x /= Vec.x;
  //  y /= Vec.y;
  //  z /= Vec.z;
  //  return *this;
  //}

  //float
  //  Vector3::lenght() const {

  //  return kraMath::sqrt(x*x + y*y + z*z);

  //}

  //float
  //Vector3::lenghtSquared() const {

  //  return kraMath::powf(kraMath::sqrt(x*x + y*y + z*z), 2.0f);

  //}

  //float
  //Vector3::dot(Vector3& V1, Vector3& V2) {
  //  return V1 | V2;
  //}

  //Vector3
  //Vector3::cross(Vector3& V1, Vector3& V2) {
  //  return V1 ^ V2;
  //}

  //float
  //  Vector3::distance(const Vector3& V1, const Vector3& V2) {
  //  kraMath::sqrt(kraMath::pow((V1.x - V2.x), 2.0f) + kraMath::pow((V1.y - V2.y), 2.0f) + kraMath::pow((V1.z - V2.z), 2.0f));
  //}

  //void
  //  Vector3::normalize() {
  //  float vec = kraMath::sqrt(x*x + y*y + z*z);
  //  x /= vec;
  //  y /= vec;
  //  z /= vec;
  //}

  //void
  //  Vector3::floor() {
  //  kraMath::floor(x);
  //  kraMath::floor(y);
  //  kraMath::floor(z);
  //}

  //void
  //  Vector3::ceil() {
  //  kraMath::ceil(x);
  //  kraMath::ceil(y);
  //  kraMath::ceil(z);
  //}

  //float&
  //  Vector3::operator[](uint32 Index) {

  //  if (Index == 0) {
  //    return x;
  //  }
  //  else if (Index == 1) {
  //    return y;
  //  }
  //  else if (Index == 2) {
  //    return z;
  //  }
  //}

  //float
  //  Vector3::operator[](uint32 Index) const {

  //  if (Index == 0) {
  //    return x;
  //  }
  //  else if (Index == 1) {
  //    return y;
  //  }
  //  else if (Index == 2) {
  //    return z;
  //  }
  //}

  //float&
  //  Vector3::component(uint32 Index) {

  //  if (Index == 0) {
  //    return x;
  //  }
  //  else if (Index == 1) {
  //    return y;
  //  }
  //  else if (Index == 2) {
  //    return z;
  //  }
  //}

  //float
  //  Vector3::component(uint32 Index) const {

  //  if (Index == 0) {
  //    return x;
  //  }
  //  else if (Index == 1) {
  //    return y;
  //  }
  //  else if (Index == 2) {
  //    return z;
  //  }
  //}
}
