#pragma once
#include "kraPrerequisitesCore.h"
#include "kraComponent.h"

namespace kraEngineSDK {
  class GameObject;

  class KRA_CORE_EXPORT Transform 
  : public Component{

    CLASS_DECLARATION(Transform)

   public:
     Transform(GameObject* owner)
     : Component(owner) {}

     ~Transform() = default;

     void
     setPosition(Vector3 newPosition);

     Vector3
     getPosition();

     void
     setRotation(Vector3 newPosition);

     Vector3
     getRotation();

     void
     setScale(Vector3 newPosition);

     Vector3
     getScale();

#pragma region PUBLIC_MEMBERS
     Vector3 Position = Vector3(0.0f, 0.0f, 0.0f);
     Vector3 Rotation = Vector3(0.0f, 0.0f, 0.0f);
     Vector3 Scale = Vector3(1.0f, 1.0f, 1.0f);
#pragma endregion PUBLIC_MEMBERS
  };
}