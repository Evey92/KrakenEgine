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
  class ComputeShader;
  class VertexBuffer;
  class IndexBuffer;
  class SamplerState;
  class Texture;
  class ShaderResourceView;
  class Material;
  class RasterizerState;
  class FrameBuffer;

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
    resolveSubreresource(const Texture& source, const Texture& result) override;

    uint32 
    checkMaxSupportedMSAALevel() override;

    void 
    generateMips(ShrdPtr<Texture> tex) override;

    void 
    copySubresourceRegion(ShrdPtr<Texture> destTex, 
                          uint32 destIndex,
                          uint32 dstX, 
                          uint32 dstY, 
                          uint32 dstZ, 
                          ShrdPtr<Texture> sourceTex, 
                          uint32 srcIndex, 
                          void* box) override;

    //Stupid function to test something.
    uint32
    calcSubResource(uint32 mipSlice, uint32 arraySize, uint32 mipLevels) override;

    void
    Draw(uint32 numVertex, uint32 startIndex);
    
    void
    DrawIndexed(uint32 count, uint32 start, int32 baseLoc);
    
    void
    PresentSwapChain();
    
    ShrdPtr<RenderTargetView>
    createRenderTargetInsttance();
    
    Viewport*
    createViewportInstance();
    
    ShrdPtr<InputLayout>
    createInputLayoutInstance();
    
    ShrdPtr<DepthStencil>
    createDepthStencilInstance();
    
    ShrdPtr<DepthStencilView>
    createDepthStencilViewInstance();
    
    ShrdPtr<VertexShader>
    createVertexShaderInstance();
    
    ShrdPtr<PixelShader>
    createPixelShaderInstance();
    
    ShrdPtr<ComputeShader> 
    createComputeShaderInstance() override;
        
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
    
    ShrdPtr<ConstantBuffer<Matrix4>>
    createConstantBufferInstance();
    
    ShrdPtr<ConstantBuffer<Vector4>>
    createConstantBufferInstanceVec4();

    ShrdPtr<ConstantBuffer<float>>
    createConstantBufferInstanceFloat();
    
    ShrdPtr<SamplerState>
    createSamplerStateInstance(); 
    
    ShrdPtr<Texture>
    createTextureInstance();
    
    ShaderResourceView*
    createShaderRVInstance();
    
    /*Material*
    createMaterialInstance();*/
    
    ShrdPtr<RasterizerState>
    creatreRasterizerStateInstance();
    
    ID3D11Device* m_pd3dDevice = nullptr;
    ID3D11DeviceContext* m_pImmediateContext = nullptr;
    SwapChainDX m_pSwapChain;
    uint32 m_height = 0;
    uint32 m_width = 0;


    ShrdPtr<FrameBuffer>
    createFrameBufferInstance() override;



  };
}

