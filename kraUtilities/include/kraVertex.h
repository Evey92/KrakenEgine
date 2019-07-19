#pragma once
#include "kraPrerequisitesUtil.h"
#include "kraVector2.h"
#include "kraVector3.h"
#include "kraVector4.h"

namespace kraEngineSDK {

  class Vertex
  {
  public:

    Vertex() = default;


    Vertex(const Vertex& copyVert)
    {
      Pos = copyVert.Pos;
      Pos.w = 1.0f;
      Tex = copyVert.Tex;
      m_normal = copyVert.m_normal;
      m_tangent = copyVert.m_tangent;
      m_binormal = copyVert.m_binormal;
      m_color = copyVert.m_color;
    }

    Vertex(Vector3 vert)
    {
      Pos.x = vert.x;
      Pos.y = vert.y;
      Pos.z = vert.z;
      Pos.w = 1.0f;
    }

    Vertex(Vector3 vert, Vector2 tex)
    {
      Pos.x = vert.x;
      Pos.y = vert.y;
      Pos.z = vert.z;
      Pos.w = 1.0f;

      Tex.x = tex.x;
      Tex.y = tex.y;
    }

    Vertex(float x, float y, float z) {
      Pos.x = x;
      Pos.y = y;
      Pos.z = z;
      Pos.w = 1.0f;
    }

    Vertex(float x, float y, float z, float texX, float texY) {
      Pos.x = x;
      Pos.y = y;
      Pos.z = z;
      Pos.w = 1.0f;

      Tex.x = texX;
      Tex.y = texY;
    }

    Vector4 Pos = Vector3(0.0f, 0.0f, 0.0f);
    Vector2 Tex = Vector2(0.0f, 0.0f);
    Vector3 m_normal = Vector3(0.0f, 0.0f, 0.0f);
    Vector3 m_tangent = Vector3(0.0f, 0.0f, 0.0f);
    Vector3 m_binormal = Vector3(0.0f, 0.0f, 0.0f);
    Vector4 m_color = Vector3(0.0f, 0.0f, 0.0f);
  };
}