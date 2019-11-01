#pragma once
#include "kraPrerequisitesCore.h"

namespace kraEngineSDK {

  class Texture;
  class RenderTargetView;
  class DepthStencilView;

  class FrameBuffer
  {
   
   public:
    FrameBuffer() = default;
    ~FrameBuffer() = default;

    virtual bool
    initFramebuffer(uint32 width,
                    uint32 height, 
                    uint32 samples, 
                    GFX_FORMAT::E colorFormat,
                    GFX_FORMAT::E depthFormat) = 0;

    ShrdPtr<Texture> m_colorTex = nullptr;
    ShrdPtr<Texture> m_depthTex = nullptr;
    ShrdPtr<RenderTargetView> m_frameRTV = nullptr;
    ShrdPtr<DepthStencilView> m_frameDSV = nullptr;
    uint32 m_width = 0;
    uint32 m_height = 0;
    uint32 m_samples = 0;
  };
}
