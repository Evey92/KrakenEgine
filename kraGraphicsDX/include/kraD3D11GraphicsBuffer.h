#pragma once
#include <kraGraphicsBuffer.h>

#include "kraPrerequisitesGFX.h"

namespace kraEngineSDK {
  class KRA_UTILGFX_EXPORT GraphicsBufferDX : public GraphicsBuffer
  {
  public:
    GraphicsBufferDX() = default;
    
    virtual ~GraphicsBufferDX() {}

    virtual void
      reserve(size_t numObjects) = 0;

    virtual void
      clear() = 0;

    /*virtual void
    createHardwareBuffer(ID3D11Device* pd3dDevice, D3D11_USAGE usage = D3D11_USAGE_DEFAULT);*/



    
  };
}
