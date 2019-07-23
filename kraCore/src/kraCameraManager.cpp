#include "kraCameraManager.h"

namespace kraEngineSDK {
  void 
  CameraManager::Transition(Camera* A, Camera* B, float time)
  {
    kraMath::lerp(A->getPosition(), B->getPosition(), time);
  }
}