#pragma once
#include "kraPrerequisitesCore.h"
#include "kraConstantBufferMatrices.h"

namespace kraEngineSDK {
  class RenderTargetView;
  class InputLayout;
  class Viewport;
  class DepthStencil;
  class DepthStencilView;
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

  class Device
  {
  public:
    Device() = default;
    virtual ~Device()  {}

    virtual bool
    initializeDevice(void* g_hWnd) = 0;
   
    virtual void
    setRenderTarget(RenderTargetView* pRTV, void* pDSV) = 0;
    
    /*virtual DepthStencil*
    createDepthStencil(int height, int width) = 0;*/
    
    /*virtual void cleanDepthStencil(DepthStencil* depthStencil) = 0;*/
    
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
    
    virtual void*
    getDevice() = 0;

    virtual void*
    getContext() = 0;

    virtual void
    resolveSubreresource(const Texture& source, const Texture& result) = 0;
    
    virtual uint32
    checkMaxSupportedMSAALevel() = 0;

    virtual void
    generateMips(ShrdPtr<Texture> tex) = 0;

    
    virtual void
    copySubresourceRegion(ShrdPtr<Texture> destTex, 
                          uint32 destIndex,
                          uint32 dstX,
                          uint32 dstY,
                          uint32 dstZ, 
                          ShrdPtr<Texture> sourceTex,
                          uint32 srcIndex,
                          void* box) = 0;

    virtual void
    Draw(uint32 numVertex, uint32 startIndex) = 0;
    
    virtual void
    DrawIndexed(uint32 count, uint32 start, int32 baseLoc) = 0;
    
    virtual void
    PresentSwapChain() = 0;
    
    virtual ShrdPtr<RenderTargetView>
    createRenderTargetInsttance() = 0;
    
    virtual Viewport*
    createViewportInstance() = 0;
    
    virtual ShrdPtr<InputLayout>
    createInputLayoutInstance() = 0;
    
    virtual ShrdPtr<DepthStencil>
    createDepthStencilInstance() = 0;
    
    virtual ShrdPtr<DepthStencilView>
    createDepthStencilViewInstance() = 0;
    
    virtual ShrdPtr<VertexShader>
    createVertexShaderInstance() = 0;
    
    virtual ShrdPtr<PixelShader>
    createPixelShaderInstance() = 0;

    virtual ShrdPtr<ComputeShader>
    createComputeShaderInstance() = 0;
    
    virtual VertexBuffer*
    createVertexBufferInstance() = 0;
    
    virtual IndexBuffer*
    createIndexBufferInstance() = 0;
    
    virtual ConstantBuffer<CBNeverChanges>*
    createConstantBufferNever() = 0;
    
    virtual ConstantBuffer<CBChangeOnResize>*
    createConstantBufferResize() = 0;
    
    virtual ConstantBuffer<CBChangesEveryFrame>*
    createConstantBufferEveryFrame() = 0;
    
    virtual ShrdPtr<ConstantBuffer<Matrix4>>
    createConstantBufferInstance() = 0;
    
    virtual ShrdPtr<ConstantBuffer<Vector4>>
    createConstantBufferInstanceVec4() = 0;

    virtual ShrdPtr<ConstantBuffer<float>>
    createConstantBufferInstanceFloat() = 0;
    
    virtual ShrdPtr<SamplerState>
    createSamplerStateInstance() = 0;
    
    virtual ShrdPtr<Texture>
    createTextureInstance() = 0;
    
    virtual ShaderResourceView*
    createShaderRVInstance() = 0;
    
    /*virtual Material*
    createMaterialInstance() = 0;*/
    
    virtual ShrdPtr<RasterizerState>
    creatreRasterizerStateInstance() = 0;
    
    virtual ShrdPtr<FrameBuffer>
    createFrameBufferInstance() = 0;

  };


}
