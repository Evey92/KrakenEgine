#include "kraTransform.h"

namespace kraEngineSDK {

  CLASS_DEFINITION(Component, Transform)

  void 
  Transform::setPosition(Vector3 newPosition)
  {
    Position = newPosition;
  }

  Vector3 
  Transform::getPosition()
  {
    return Position;
  }

  void
  Transform::setRotation(Vector3 newRot)
  {
    Rotation = newRot;
  }

  Vector3
  Transform::getRotation()
  {
    return Rotation;
  }

  void
  Transform::setScale(Vector3 newScale)
  {
    Position = newScale;
  }

  Vector3
  Transform::getScale()
  {
    return Scale;
  }

}
