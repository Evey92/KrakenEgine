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
  class Material;
  class RasterizerState;

  template<typename CONSVERTEX> class ConstantBuffer;

  class KRA_UTILGFX_EXPORT DeviceDX 
  : public Device
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

    virtual void* 
    getDevice() override;

    virtual void* 
    getContext() override;
    
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
    
    ConstantBuffer<Matrix4>*
    createConstantBufferInstance();
    
    ConstantBuffer<Vector4>*
    createConstantBufferInstanceVec3();
    
    SamplerState*
    createSamplerStateInstance(); 
    
    ShrdPtr<Texture>
    createTextureInstance();
    
    ShaderResourceView*
    createShaderRVInstance();
    
    Material*
    createMaterialInstance();
    
    RasterizerState*
    creatreRasterizerStateInstance();
    
    ID3D11Device* m_pd3dDevice = nullptr;
    ID3D11DeviceContext* m_pImmediateContext = nullptr;
    SwapChainDX m_pSwapChain;
    uint32 m_height = 0;
    uint32 m_width = 0;

  };
}

