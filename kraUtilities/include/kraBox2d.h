#pragma once

#include "kraPrerequisitesUtil.h"
#include "kraVector2.h"

namespace kraEngineSDK {

  class KRA_UTILITY_EXPORT Box2D final
  {
   public:
    Box2D();
    Box2D(const Box2D& otherBox);
    Box2D(Vector2 min, Vector2 max);

   private:
    Vector2 m_min;
    Vector2 m_max;
  };

}
