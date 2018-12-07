#pragma once

#include "kraPrerequisitesCore.h" 
#include <vector>

namespace kraEngineSDK {
  class kraGraphicsBuffer
  {
  public:

    kraGraphicsBuffer() = default;
    virtual ~kraGraphicsBuffer() { clearBuffer(); };
    virtual void clearBuffer() = 0;

  };

}


