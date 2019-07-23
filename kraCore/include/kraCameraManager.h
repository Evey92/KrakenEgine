#pragma once
#include "kraPrerequisitesCore.h"
#include "kraCamera.h"

namespace kraEngineSDK {
  class KRA_CORE_EXPORT CameraManager {

  public:

    CameraManager() = default;
    
    void 
    Transition(Camera* A, Camera* B, float time);

    std::vector<Camera> m_camList;
    Camera* m_activeCamera = nullptr;
    Camera* m_initialCamera = nullptr;
    Camera* m_objectiveCamera = nullptr;

  };
}