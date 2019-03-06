#include <kraDepthStencil.h>
#include <kraRenderTargetView.h>
#include <kraViewport.h>
#include <kraInputLayout.h>

#include "kraD3D11Device.h"
#include "kraD3D11RenderTargetView.h"
#include "kraD3D11DepthStencil.h"
#include "kraD3D11Viewport.h"
#include "kraD3D11InputLayout.h"
#include "kraD3D11VertexShader.h"
#include "kraD3D11PixelShader.h"
#include "kraD3D11VertexBuffer.h"

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
    sd.BufferCount = 1;
    sd.BufferDesc.Width = m_width;
    sd.BufferDesc.Height = m_height;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = m_hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;


    D3D_FEATURE_LEVEL selectedFL;

    for (size_t driverTypeIndex = 0;
      driverTypeIndex < driverTypes.size();
      ++driverTypeIndex)
    {
      D3D_DRIVER_TYPE& dt = driverTypes[driverTypeIndex];
      hr = D3D11CreateDeviceAndSwapChain(nullptr, dt, nullptr,
        createDeviceFlags, &featureLevels[0],
        static_cast<UINT>(featureLevels.size()),
        D3D11_SDK_VERSION,
        &sd, &m_pSwapChain.m_pd3dSwapChain,
        &m_pd3dDevice, &selectedFL,
        &m_pImmediateContext);

      if (SUCCEEDED(hr)) {
        break;
      }
    }
    if (FAILED(hr)) {
      return hr;
    }

    return hr;
  }

  void
  DeviceDX::setRenderTarget(RenderTargetView* pRTV, void* pDSV) {
    
    RenderTargetViewDX* m_pRTV = reinterpret_cast<RenderTargetViewDX*>(pRTV);
    ID3D11DepthStencilView* m_pDSV = reinterpret_cast<ID3D11DepthStencilView*>(pDSV);

    m_pImmediateContext->OMSetRenderTargets(1, &m_pRTV->m_pRenderTargetView, m_pDSV);
  }

  DepthStencil*
  DeviceDX::createDepthStencil(int height, int width) {
    
    DepthStencilDX m_depthText;

    D3D11_TEXTURE2D_DESC descTexture;
    memset(&descTexture, 0, sizeof(descTexture));
    descTexture.Height = height;
    descTexture.Width = width;
    descTexture.MipLevels = 1;
    descTexture.ArraySize = 1;
    descTexture.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    descTexture.SampleDesc.Count = 1;
    descTexture.SampleDesc.Quality = 0;
    descTexture.Usage = D3D11_USAGE_DEFAULT;
    descTexture.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    descTexture.CPUAccessFlags = 0;
    descTexture.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA initBuffer;
    memset(&initBuffer, 0, sizeof(initBuffer));

    if (!m_pd3dDevice->CreateTexture2D(&descTexture, &initBuffer, &m_depthText.m_pd3dDepthStencil))
    {
      std::cout << "No se pudo crear depth sctencil";

    }

    return &m_depthText;

  }

  void
  DeviceDX::cleanDepthStencil(DepthStencil* depthStencil)
  {
    DepthStencilDX* m_depthText = reinterpret_cast<DepthStencilDX*>(depthStencil);
    m_depthText->m_pd3dDepthStencil->Release();
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

  void
  DeviceDX::Draw(uint32 numVertex, uint32 startIndex) {
    m_pImmediateContext->Draw(numVertex, startIndex);
  }

  void
  DeviceDX::DrawIndexed() {

  }

  //TODO fix this bullshit.
  void
  DeviceDX::PresentSwapChain() {
    m_pSwapChain.present(0,0);
  }

  RenderTargetView*
  DeviceDX::createRenderTargetInsttance() {
    return new RenderTargetViewDX();
  }

  Viewport*
  DeviceDX::createViewportInstance() {
    return new ViewportDX();
  }

  InputLayout*
  DeviceDX::createInputLayoutInstance() {
    return new InputLayoutDX();
  }

  DepthStencil*
  DeviceDX::createDepthStencilInstance() {
    return new DepthStencilDX();
  }

  VertexShader*
  DeviceDX::createVertexShaderInstance() {
    return new VertexShaderDX();
  }
  PixelShader*
  DeviceDX::createPixelShaderInstance() {
    return new PixelShaderDX();
  }
  /*GraphicsBuffer*
  DeviceDX::createVertexBufferInstance() {
    return new VertexBufferDX<Vertex>();
  }*/

}
