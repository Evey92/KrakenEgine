#include "kraClock.h"

namespace kraEngineSDK {
  
  float
  Clock::deltaTime() {

    auto now = high_resolution_clock::now();
    milliseconds ms = duration_cast<milliseconds>(now - m_clock);

    m_clock = now;

    return static_cast<float>(ms.count());
  }
  
  void
  Clock::initialize() {
    m_clock = high_resolution_clock::now();
  }
}