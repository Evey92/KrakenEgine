#pragma once
#include "kraPrerequisitesUtil.h"
#include "kraVector2.h"
#include "kraVector3.h"
#include "kraVector4.h"

namespace kraEngineSDK {

  class Vector4;
  class Vector3;
  class Vector2;


  class Vertex
  {
  public:

    //Vertex() = default;

    Vertex() {
      Pos.w = 1.0f;
    }

    Vertex(const Vertex& copyVert)
    {
      Pos.x = copyVert.Pos.x;
      Pos.y = copyVert.Pos.y;
      Pos.z = copyVert.Pos.z;
      Pos.w = 1.0f;
    }
    Vertex(Vector3 vert)
    {
      Pos.x = vert.x;
      Pos.y = vert.y;
      Pos.z = vert.z;
      Pos.w = 1.0f;
    }

    Vertex(float x, float y, float z) {
      Pos.x = x;
      Pos.y = y;
      Pos.z = z;
      Pos.w = 1.0f;
    }

    Vertex(float x, float y, float z, float w) {
      Pos.x = x;
      Pos.y = y;
      Pos.z = z;
      Pos.w = w;
    }

    Vector4 Pos;
    //Vector2 Tex;
    /*Vector3 m_normal;
    Vector4 m_color;
    float m_u;
    float m_v;*/
  };
}