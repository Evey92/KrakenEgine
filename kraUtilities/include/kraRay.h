#pragma once
#include "kraVector3.h"

namespace kraEngineSDK {
  class ray {
   
   public:
    Vector3
    t(float _t) {
      return m_p0 + (m_p1 - m_p0) * _t;
    }

    Vector3 m_p0;
    Vector3 m_p1;
  };
}
