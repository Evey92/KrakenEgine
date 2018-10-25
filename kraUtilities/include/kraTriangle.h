#pragma once

#include "kraPrerequisitesUtil.h"
#include "kraMath.h"
#include "kraVector3.h"

namespace kraEngineSDK {

  class KRA_UTILITY_EXPORT Triangle
  {
   public:

    Triangle() = default;

    Triangle(const Triangle& triangle);

    Triangle(Vector3 vert1, Vector3 vert2, Vector3 vert3);

   public:

    Vector3 m_vert1;
    Vector3 m_vert2;
    Vector3 m_vert3;

  };

  Triangle::Triangle(Vector3 vert1, Vector3 vert2, Vector3 vert3)
    : m_vert1(vert1),
      m_vert2(vert2),
      m_vert3(vert3)
  {}

  Triangle::Triangle(const Triangle& triangle)
    : m_vert1(triangle.m_vert1),
      m_vert2(triangle.m_vert2),
      m_vert3(triangle.m_vert3)
  {}
}
