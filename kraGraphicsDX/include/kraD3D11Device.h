#pragma once
#include <windows.h>
#include <kraDevice.h>

#include "kraD3D11SwapChain.h"
#include "kraPrerequisitesGFX.h"



namespace kraEngineSDK {

  class RenderTargetView;
  class InputLayout;
  class Viewport;
  class DepthStencil;
  class VertexShader;
  class PixelShader;
  class VertexBuffer;

  class KRA_UTILGFX_EXPORT DeviceDX : public Device
  {

  public:
    DeviceDX() = default;
    ~DeviceDX() {}

    bool
    initializeDevice(void* g_hWnd);
    void
    setRenderTarget(RenderTargetView* pRTV, void* pDSV);

    DepthStencil*
    createDepthStencil(int height, int width);
    void
    cleanDepthStencil(DepthStencil* depthStencil);
    void
    cleanContext();
    void
    cleanDevice();
    void
    cleanSwapChain();
    void
    cleanContextState();
    void
    setPrimitiveTopology();
    uint32
    getHeight();
    uint32
    getWidth();
    void
    Draw(uint32 numVertex, uint32 startIndex);
    void
    DrawIndexed();
    void
    PresentSwapChain();
    RenderTargetView*
    createRenderTargetInsttance();
    Viewport*
    createViewportInstance();
    InputLayout*
    createInputLayoutInstance();
    DepthStencil*
    createDepthStencilInstance();
    VertexShader*
    createVertexShaderInstance();
    Shader*
    createPixelShaderInstance();
    GraphicsBuffer*
    createVertexBufferInstance();

    SwapChainDX m_pSwapChain;
    uint32 m_height;
    uint32 m_width;
    ID3D11Device* m_pd3dDevice = nullptr;
    ID3D11DeviceContext* m_pImmediateContext = nullptr;
   
  };
}

