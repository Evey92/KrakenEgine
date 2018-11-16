#pragma once
#include "kraVector4.h"

namespace kraEngineSDK {
  
  struct Vertex {

    Vector3 m_position;
    Vector2 m_texcoord;
    Vector3 m_normal;
    Vector4 m_color;
    float m_u;
    float m_v;
  };

}