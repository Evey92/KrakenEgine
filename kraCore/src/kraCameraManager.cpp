#include "kraCameraManager.h"

namespace kraEngineSDK {

  void 
  CameraManager::registerCamera(Camera* cam)
  {
    m_camList.push_back(cam);
  }

  void
  CameraManager::Transition(Camera* A, Camera* B, float time)
  {
    kraMath::lerp(A->getPosition(), B->getPosition(), time);
  }

  void 
  CameraManager::setActiveCamera(Camera* cam)
  {
    m_activeCamera = cam;
  }

}