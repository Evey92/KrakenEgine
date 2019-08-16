#pragma once
#include "kraPrerequisitesCore.h"
#include "kraModule.h"
#include "kraCamera.h"

namespace kraEngineSDK {
  class KRA_CORE_EXPORT CameraManager : public Module<CameraManager> {

  public:

    CameraManager() = default;
    
    void 
    registerCamera(Camera* cam);
    
    void 
    Transition(Camera* A, Camera* B, float time);

    void
    setActiveCamera(Camera* cam);

    std::vector<Camera*> m_camList;
    Camera* m_activeCamera = nullptr;
    Camera* m_objectiveCamera = nullptr;

  };
}