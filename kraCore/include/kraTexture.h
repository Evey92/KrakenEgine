#pragma once
#include "kraPrerequisitesCore.h"
#include "kraGFXMappings.h"

namespace kraEngineSDK {
  class Device;

  class Texture
  {
   public:
     Texture() = default;
     virtual 
     ~Texture() {}

    virtual void
    createCubeTexture(void* pDevice,
                        uint32 height,
                        uint32 width,
                        GFX_FORMAT::E format,
                        GFX_USAGE::E usage,
                        uint32 levels = 0U) = 0;

    virtual void
    createTexture2D(void* pDevice,
                    uint32 height,
                    uint32 width,
                    GFX_FORMAT::E format,
                    GFX_USAGE::E usage,
                    uint32 levels = 0U) = 0;

    virtual bool
    createTexture2DFromFile(const Device& device,
                            String filename,
                            GFX_FORMAT::E format,
                            GFX_USAGE::E usage,
                            CPU_USAGE::E  cpuUsage,
                            int channels = 4,
                            uint32 levels = 0U) = 0;

    virtual void
    createTextureUAV(const Device& device,
                     uint32 mipSlice) = 0;

    virtual void
    generateMips() = 0;

    virtual uint32
    getHeight() = 0;

    virtual uint32
    getWidth() = 0;

    virtual uint32
    getLevels() = 0;

    virtual void*
    getShaderResourceView() = 0;

    //TODO: Move all of this bullshit either to an abstraction of device context, or to the device itself... Maybe.
    virtual void
    setTextureShaderResource(const Device* pDevice,
                               uint32 startSlot,
                               uint32 numViews) = 0;

    virtual void
    setPSTextureShaderResources(const Device* pDevice,
                             uint32 startSlot,
                             uint32 numViews, 
                             Vector<ShrdPtr<Texture>> shaderResources) = 0;

    virtual void
    setTextureComputeShaderResource(const Device* pDevice,
                                    uint32 startSlot,
                                    uint32 numViews) = 0;
    virtual void
    setTextureUnorderedAccesVews(const Device* pDevice,
                                    uint32 startSlot,
                                    uint32 numViews) = 0;

    virtual void
    setComputeNullUAV(const Device& pDevice) = 0;

    virtual bool
    isHDR() = 0;
    
    virtual void
    releaseTexture() = 0;

  };

}
