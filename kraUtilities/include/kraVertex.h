#pragma once
#include "kraVector4.h"

namespace kraEngineSDK {
  
  struct kraVertex {

    Vector4 m_position;
    Vector4 m_color;
    Vector4 m_normal;
    float m_u;
    float m_v;
  };

}