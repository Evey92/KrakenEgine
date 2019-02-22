#pragma once

#include "kraPrerequisitesCore.h" 
#include <vector>

namespace kraEngineSDK {
  class GraphicsBuffer
  {
   public:

    GraphicsBuffer() = default;
    
    virtual 
    ~GraphicsBuffer() {}

    virtual void
    reserve(size_t numObjects) {
      KRA_UNDEFINED_PARAMETER(numObjects);
    }

    virtual void
    clear() = 0;
  };

}


