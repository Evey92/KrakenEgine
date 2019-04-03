#pragma once
#include "kraModule.h"
#include <chrono>

namespace kraEngineSDK {
  using namespace std::chrono;

  class Clock : public Module<Clock>
  {
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