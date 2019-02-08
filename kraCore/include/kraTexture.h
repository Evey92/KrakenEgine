#pragma once
#include "kraPrerequisitesCore.h"

namespace kraEngineSDK {
  class KRA_CORE_EXPORT Texture
  {
   public:
     Texture() = default;
     virtual 
     ~Texture() {}

    virtual void
    createTexture2D(void* pDevice, int height, int width,
                    void* format, void* bindFlag) = 0;
    virtual void
      createTexture2D(void* pDevice, int height, int width,
                      void* format, void* bindFlag, void* desc) = 0;
    virtual bool
    createTexture2DFromFile(void* pDevice, const char*  filename,
                            void* format, void* bindFlag) = 0;

    virtual void
    releaseTexture() = 0;

  };
}
