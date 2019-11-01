#pragma once
#include "kraPrerequisitesGFX.h"
#include <kraFrameBuffer.h>

namespace kraEngineSDK {

  class Texture;
  class RenderTargetView;
  class DepthStencilView;

  class KRA_UTILGFX_EXPORT FrameBufferDX : 
   public FrameBuffer {

   public:

    FrameBufferDX() = default;
    ~FrameBufferDX() = default;
    
    bool
    initFramebuffer(uint32 width,
                    uint32 height,
                    uint32 samples,
                    GFX_FORMAT::E colorFormat,
                    GFX_FORMAT::E depthFormat) override;

  };
}