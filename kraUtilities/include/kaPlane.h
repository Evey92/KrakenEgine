#pragma once

#include "kraPrerequisitesUtil.h"
#include "kraVector3.h"
#include "kraVector4.h"

namespace kraEngineSDK {

  class Plane : public Vector3
  {
   public:
    Plane() = default;
    Plane(const Vector4& Vec);
    Plane(const Vector3& Norm, float d);
    Plane(float x, float y, float z, float w);

   public:
    
     float d; 
     float n; 
  };

  //Plane::Plane(float X, float Y, float Z, float W) : x(X), y(Y), z(Z), w(W) {}
}
