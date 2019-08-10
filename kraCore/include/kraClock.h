#pragma once

#include <chrono>
#include "kraPrerequisitesCore.h"
#include "kraModule.h"

namespace kraEngineSDK {
  using namespace std::chrono;

  class KRA_CORE_EXPORT Clock :
  public Module<Clock> {
   public:

     Clock() = default;
     ~Clock() = default;

     float
     deltaTime(); 
     void
     initialize();

    high_resolution_clock::time_point m_clock;
  };
}