#pragma once
#include "kraPrerequisitesCore.h"


namespace kraEngineSDK {
  class RenderTargetView;
  class InputLayout;
  class Viewport;
  class DepthStencil;
  class PixelShader;
  class VertexShader;
  class GraphicsBuffer;

  class Device
  {
  public:
    Device() = default;
    virtual ~Device()  {}

    virtual bool
    initializeDevice(void* g_hWnd) = 0;
   
    virtual void
    setRenderTarget(RenderTargetView* pRTV, void* pDSV) = 0;
    
    virtual DepthStencil*
    createDepthStencil(int height, int width) = 0;
    
    virtual void cleanDepthStencil(DepthStencil* depthStencil) = 0;
    
    virtual void
    cleanContext() = 0;
    
    virtual void
    cleanDevice() = 0;
    
    virtual void
    cleanSwapChain() = 0;
    
    virtual void
    cleanContextState() = 0;
    virtual void
    setPrimitiveTopology() = 0;
    virtual uint32
    getHeight() = 0;
    virtual uint32
    getWidth() = 0;
    virtual void
    Draw(uint32 numVertex, uint32 startIndex) = 0;
    virtual void
    DrawIndexed() = 0;
    virtual void
    PresentSwapChain() = 0;
    virtual RenderTargetView*
    createRenderTargetInsttance() = 0;
    virtual Viewport*
    createViewportInstance() = 0;
    virtual InputLayout*
    createInputLayoutInstance() = 0;
    virtual DepthStencil*
    createDepthStencilInstance() = 0;
    virtual VertexShader*
    createVertexShaderInstance() = 0;
    virtual PixelShader*
    createPixelShaderInstance() = 0;
    /*
    virtual GraphicsBuffer*
    createVertexBufferInstance() = 0;*/

  };
}