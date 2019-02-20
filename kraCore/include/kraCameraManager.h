#pragma once
#include "kraPrerequisitesCore.h"
#include "kraCamera.h"

namespace kraEngineSDK {
  class KRA_CORE_EXPORT CameraManager {

  public:

    CameraManager();
    void Transition(Camera* A, Camera* B, float time);


    std::vector<Camera> m_camList;
    Camera* m_activeCamera;
    Camera* m_initialCamera;
    Camera* m_objectiveCamera;

  };
}