#pragma once
#include "kraPrerequisitesCore.h"

namespace kraEngineSDK {
  class KRA_CORE_EXPORT Transform {

   public:

#pragma region PUBLIC_MEMBERS
     Vector3 Position = Vector3(0.0f, 0.0f, 0.0f);
     Vector3 Rotation = Vector3(0.0f, 0.0f, 0.0f);
     Vector3 Scale = Vector3(0.0f, 0.0f, 0.0f);
#pragma endregion PUBLIC_MEMBERS
  };
}