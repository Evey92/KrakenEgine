#pragma once
#include "kraPrerequisitesCore.h"


namespace kraEngineSDK {
  class Device;

  class Texture
  {
   public:
     Texture() = default;
     virtual 
     ~Texture() {}

    virtual void
    createTexture2D(const Device& pDevice, int height, int width) = 0;
    virtual void
      createTexture2D(void* pDevice, int height, int width,
                      void* format, void* bindFlag, void* desc) = 0;
    virtual bool
    createTexture2DFromFile(const Device&, std::string filename) = 0;
    virtual void
    setTextureShaderResource(const Device* pDevice,
                               uint32 startSlot,
                               uint32 numViews) = 0;
    virtual void
    releaseTexture() = 0;

  };
}
