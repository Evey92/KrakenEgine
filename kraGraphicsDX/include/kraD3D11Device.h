#pragma once
#include <windows.h>

#include "kraPrerequisitesGFX.h"
#include "kraD3D11SwapChain.h"



namespace kraEngineSDK {

  class Device;
  class RenderTargetView;
  class InputLayout;
  class Viewport;
  class DepthStencil;
  class DepthStencylView;
  class VertexShader;
  class PixelShader;
  class VertexBuffer;
  class IndexBuffer;
  class SamplerState;
  class Texture;
  class ShaderResourceView;

  template<typename CONSVERTEX> class ConstantBuffer;

  class KRA_UTILGFX_EXPORT DeviceDX : public Device
  {

  public:
    DeviceDX() = default;
    ~DeviceDX() {}

    bool
    initializeDevice(void* g_hWnd);
    void
    setRenderTarget(RenderTargetView* pRTV, void* pDSV);
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
    DrawIndexed(uint32 count, uint32 start, int32 baseLoc);
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
    DepthStencylView*
    createDepthStencilViewInstance();
    VertexShader*
    createVertexShaderInstance();
    PixelShader*
    createPixelShaderInstance();
    VertexBuffer*
    createVertexBufferInstance();
    IndexBuffer*
    createIndexBufferInstance();
    ConstantBuffer<CBNeverChanges>*
    createConstantBufferNever();
    ConstantBuffer<CBChangeOnResize>*
    createConstantBufferResize();
    ConstantBuffer<CBChangesEveryFrame>*
    createConstantBufferEveryFrame();
    SamplerState*
    createSamplerStateInstance(); 
    Texture*
    createTextureInstance();
    ShaderResourceView*
    createShaderRVInstance();

    SwapChainDX m_pSwapChain;
    uint32 m_height;
    uint32 m_width;
    ID3D11Device* m_pd3dDevice = nullptr;
    ID3D11DeviceContext* m_pImmediateContext = nullptr;
   
  };
}

