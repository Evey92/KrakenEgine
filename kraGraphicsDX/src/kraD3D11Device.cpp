#include <kraDevice.h>
#include <kraDepthStencil.h>
#include <kraDepthStencilView.h>
#include <kraRenderTargetView.h>
#include <kraViewport.h>
#include <kraInputLayout.h>
#include <kraVertexShader.h>
#include <kraPixelShader.h>
#include <kraComputeShader.h>
#include <kraVertexBuffer.h>
#include <kraIndexBuffer.h>
#include <kraConstantBuffer.h>
#include <kraSampler.h>
#include <kraTexture.h>
#include <kraShaderResourceView.h>
#include <kraMaterial.h>
#include <kraRasterizerState.h>
#include <kraFrameBuffer.h>

#include "kraD3D11Device.h"
#include "kraD3D11RenderTargetView.h"
#include "kraD3D11DepthStencil.h"
#include "kraD3D11DepthStencylView.h"
#include "kraD3D11Viewport.h"
#include "kraD3D11InputLayout.h"
#include "kraD3D11VertexShader.h"
#include "kraD3D11PixelShader.h"
#include "kraD3D11ComputeShader.h"
#include "kraD3D11VertexBuffer.h"
#include "kraD3D11IndexBuffer.h"
#include "kraD3D11ConstantBuffer.h"
#include "kraD3D11Sampler.h"
#include "kraD3D11Texture.h"
#include "kraD3D11ShaderResourceView.h"
#include "kraD3D11RasterizerState.h"
#include "kraD3D11FrameBuffer.h"

namespace kraEngineSDK {

  bool
    DeviceDX::initializeDevice(void* g_hWnd) {

    HWND m_hWnd = reinterpret_cast<HWND>(g_hWnd);
    HRESULT hr = S_OK;
    RECT rc;

    GetClientRect(m_hWnd, &rc);

    m_width = rc.right - rc.left;
    m_height = rc.bottom - rc.top;

    uint32 createDeviceFlags = 0;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    std::vector<D3D_DRIVER_TYPE> driverTypes;
    driverTypes.push_back(D3D_DRIVER_TYPE_HARDWARE);
    driverTypes.push_back(D3D_DRIVER_TYPE_WARP);
    driverTypes.push_back(D3D_DRIVER_TYPE_REFERENCE);

    std::vector<D3D_FEATURE_LEVEL> featureLevels;
    featureLevels.push_back(D3D_FEATURE_LEVEL_11_0);
    featureLevels.push_back(D3D_FEATURE_LEVEL_10_1);
    featureLevels.push_back(D3D_FEATURE_LEVEL_10_0);


    DXGI_SWAP_CHAIN_DESC sd;
    memset(&sd, 0, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = m_width;
    sd.BufferDesc.Height = m_height;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = m_hWnd;
    sd.SampleDesc.Count = 1;
    sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    sd.Windowed = true;

    D3D_FEATURE_LEVEL selectedFL;

    for (size_t driverTypeIndex = 0;
      driverTypeIndex < driverTypes.size();
      ++driverTypeIndex)
    {
      D3D_DRIVER_TYPE& dt = driverTypes[driverTypeIndex];

      hr = D3D11CreateDeviceAndSwapChain(nullptr,
                                         dt,
                                         nullptr,
                                         createDeviceFlags,
                                         &featureLevels[0],
                                         static_cast<UINT>(featureLevels.size()),
                                         D3D11_SDK_VERSION,
                                         &sd,
                                         &m_pSwapChain.m_pd3dSwapChain,
                                         &m_pd3dDevice,
                                         &selectedFL,
                                         &m_pImmediateContext);

      if (SUCCEEDED(hr)) {
        break;
      }
    }
    if (FAILED(hr)) {
      return false;
    }

    return true;
  }

  void
    DeviceDX::setRenderTarget(RenderTargetView* pRTV, void* pDSV) {

    RenderTargetViewDX* m_pRTV = static_cast<RenderTargetViewDX*>(pRTV);
    ID3D11DepthStencilView* m_pDSV = static_cast<ID3D11DepthStencilView*>(pDSV);

    m_pImmediateContext->OMSetRenderTargets(1, &m_pRTV->m_pRenderTargetView, m_pDSV);
  }

  void
    DeviceDX::cleanContext() {
    m_pImmediateContext->Release();
  }

  void
    DeviceDX::cleanDevice() {
    m_pd3dDevice->Release();
  }

  void
    DeviceDX::cleanSwapChain() {
    m_pSwapChain.m_pd3dSwapChain->Release();
  }

  void
    DeviceDX::cleanContextState() {
    m_pImmediateContext->ClearState();
  }

  void
    DeviceDX::setPrimitiveTopology() {
    m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
  }

  uint32
    DeviceDX::getHeight() {
    return m_height;
  }

  uint32
    DeviceDX::getWidth() {
    return m_width;
  }

  void*
    DeviceDX::getDevice()
  {
    return reinterpret_cast<void*>(m_pd3dDevice);
  }

  void*
    DeviceDX::getContext()
  {
    return reinterpret_cast<void*>(m_pImmediateContext);
  }

  void
    DeviceDX::Draw(uint32 numVertex, uint32 startIndex) {
    m_pImmediateContext->Draw(numVertex, startIndex);
  }

  void
    DeviceDX::DrawIndexed(uint32 count, uint32 start, int32 baseLoc) {
    m_pImmediateContext->DrawIndexed(count, start, baseLoc);
  }

  //TODO fix this bullshit with a factory.
  void
  DeviceDX::PresentSwapChain() {
    m_pSwapChain.m_pd3dSwapChain->Present(1, 0);
  }

  ShrdPtr<RenderTargetView>
    DeviceDX::createRenderTargetInsttance() {
    return std::make_shared<RenderTargetViewDX>();
  }

  Viewport*
    DeviceDX::createViewportInstance() {
    return new ViewportDX();
  }

  ShrdPtr<InputLayout>
    DeviceDX::createInputLayoutInstance() {
    return make_shared<InputLayoutDX>();
  }

  ShrdPtr<DepthStencil>
    DeviceDX::createDepthStencilInstance() {
    return std::make_shared<DepthStencilDX>();
  }

  ShrdPtr<DepthStencilView>
    DeviceDX::createDepthStencilViewInstance() {
    return std::make_shared<DepthStencilViewDX>();
  }

  ShrdPtr<VertexShader>
    DeviceDX::createVertexShaderInstance() {
    return std::make_shared<VertexShaderDX>();
  }

  ShrdPtr<PixelShader>
    DeviceDX::createPixelShaderInstance() {
    return std::make_shared<PixelShaderDX>();
  }

  ShrdPtr<ComputeShader>
    DeviceDX::createComputeShaderInstance() {
    return std::make_shared<ComputeShaderDX>();

  }

  VertexBuffer*
    DeviceDX::createVertexBufferInstance() {
    return new VertexBufferDX();
  }
  IndexBuffer*
    DeviceDX::createIndexBufferInstance() {
    return new IndexBufferDX();
  }
  ConstantBuffer<CBNeverChanges>*
    DeviceDX::createConstantBufferNever() {

    return new ConstantBufferDX<CBNeverChanges>();

  }
  ConstantBuffer<CBChangeOnResize>*
    DeviceDX::createConstantBufferResize() {
    return new ConstantBufferDX<CBChangeOnResize>();
  }
  ConstantBuffer<CBChangesEveryFrame>*
    DeviceDX::createConstantBufferEveryFrame() {
    return new ConstantBufferDX<CBChangesEveryFrame>();
  }
  ShrdPtr<ConstantBuffer<Matrix4>>
    DeviceDX::createConstantBufferInstance() {
    return  make_shared<ConstantBufferDX<Matrix4>>();
  }

  ShrdPtr<ConstantBuffer<Vector4>>
    DeviceDX::createConstantBufferInstanceVec3() {
    return make_shared<ConstantBufferDX<Vector4>>();
  }
  ShrdPtr<SamplerState>
    DeviceDX::createSamplerStateInstance() {
    return std::make_shared<SamplerStateDX>();
  }

  ShrdPtr<Texture>
    DeviceDX::createTextureInstance() {

    ShrdPtr<TextureDX> newTex = make_shared<TextureDX>();
    return reinterpret_cast<ShrdPtr<Texture>&>(newTex);
  }

  ShaderResourceView*
    DeviceDX::createShaderRVInstance() {
    return new ShaderResourceViewDX();
  }

  /*Material*
  DeviceDX::createMaterialInstance() {
    return new Material();
  }*/

  ShrdPtr<RasterizerState>
    DeviceDX::creatreRasterizerStateInstance() {
    return std::make_shared<RasterizerStateDX>();
  }

  void
    DeviceDX::resolveSubreresource(const Texture& source, const Texture& destination)
  {
    const TextureDX& sourceText = static_cast<const TextureDX&>(source);
    const TextureDX& destText = static_cast<const TextureDX&>(destination);

    D3D11_TEXTURE2D_DESC descTexture;
    sourceText.m_pd3dTexture2D->GetDesc(&descTexture);

    if (sourceText.m_pd3dTexture2D != destText.m_pd3dTexture2D) {
      m_pImmediateContext->ResolveSubresource(destText.m_pd3dTexture2D, 0, sourceText.m_pd3dTexture2D, 0, descTexture.Format);
    }

  }

  uint32
  DeviceDX::checkMaxSupportedMSAALevel()
  {
    uint32 samples = 0;
    uint32 maxSamples = 16; 
    
    for (samples = maxSamples; samples > 1; samples /= 2) {
      uint32 colorQuality;
      uint32 depthQuality;
      m_pd3dDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R16G16B16A16_FLOAT, samples, &colorQuality);
      m_pd3dDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_D24_UNORM_S8_UINT, samples, &depthQuality);

      if (colorQuality > 0 && depthQuality > 0)
      {
        break;
      }
    }

    return samples;
  }

  void 
  DeviceDX::generateMips(ShrdPtr<Texture> tex)
  {
    TextureDX& pTexture = reinterpret_cast<TextureDX&>(*tex);

    m_pImmediateContext->GenerateMips(pTexture.m_pSRV);
  }

  ShrdPtr<FrameBuffer>
  DeviceDX::createFrameBufferInstance()
  {
    return make_shared<FrameBufferDX>();
  }

  void 
  DeviceDX::copySubresourceRegion(ShrdPtr<Texture> destTex, 
                                  uint32 destIndex, 
                                  uint32 dstX, 
                                  uint32 dstY, 
                                  uint32 dstZ, 
                                  ShrdPtr<Texture> sourceTex, 
                                  uint32 srcIndex, 
                                  void* box)
  {
    TextureDX& pdestTexture = reinterpret_cast<TextureDX&>(*destTex);
    TextureDX& psrcTexture = reinterpret_cast<TextureDX&>(*sourceTex);

    m_pImmediateContext->CopySubresourceRegion(pdestTexture.m_pd3dTexture2D,
                                               destIndex,
                                               dstX,
                                               dstY,
                                               dstZ,
                                               psrcTexture.m_pd3dTexture2D,
                                               srcIndex,
                                               reinterpret_cast<D3D11_BOX*>(box));
  }

}
