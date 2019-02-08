#pragma once

#include "kraPrerequisitesCore.h" 
#include <vector>

namespace kraEngineSDK {
  class KRA_CORE_EXPORT GraphicsBuffer
  {
   public:

    GraphicsBuffer() = default;
    
    virtual 
    ~GraphicsBuffer() {}

    virtual void
      reserve(size_t numObjects) {};

    virtual void
    clear() = 0;
  };

}


