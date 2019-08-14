#include <kraDevice.h>
#include <kraTexture.h>
#include <kraSwapChain.h>
#include <kraD3D11DepthStencylView.h>

#include "kraPrerequisitesGFX.h"
#include "kraD3D11RenderTargetView.h"
#include "kraD3D11Device.h"
#include "kraD3D11SwapChain.h"
#include "kraD3D11Texture.h"

namespace kraEngineSDK {

  bool
  RenderTargetViewDX::createRenderTargetView(const Device& pDevice) {

    const DeviceDX& m_pDevice = static_cast<const DeviceDX&>(pDevice);
    //SwapChainDX* m_pSwapChain = reinterpret_cast<SwapChainDX*>(pSwapChain);

    ID3D11Texture2D* pBackBuffer = nullptr;
    HRESULT hr = S_OK;
    
    //ID3D11RenderTargetView* m_pRenderTargetView;

    hr = m_pDevice.m_pSwapChain.m_pd3dSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&pBackBuffer));

    if (FAILED(hr)) {
      pBackBuffer->Release();
      return false;
    }


    m_pDevice.m_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &m_pRenderTargetView);
    
    //m_viewsVec.push_back(m_pRenderTargetView);

    pBackBuffer->Release();

    return true;
  }

  bool
  RenderTargetViewDX::createRenderTargetView(const Device& pDevice, Texture* pTexture) {
    
const DeviceDX& m_pDevice = static_cast<const DeviceDX&>(pDevice);
    TextureDX* m_pTexture = reinterpret_cast<TextureDX*>(pTexture);
    HRESULT hr = S_OK;

   
    //ID3D11RenderTargetView* m_pRenderTargetView;
    D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;

    renderTargetViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
    renderTargetViewDesc.Texture2D.MipSlice = 0;


    hr = m_pDevice.m_pd3dDevice->CreateRenderTargetView(m_pTexture->m_pd3dTexture2D, &renderTargetViewDesc, &m_pRenderTargetView);
    if (FAILED(hr)) {
      m_pTexture->m_pd3dTexture2D->Release();
      return false;
    }

    //m_viewsVec.push_back(m_pRenderTargetView);

    m_pTexture->m_pd3dTexture2D->Release();    
    return true;
  }

  void
  RenderTargetViewDX::setRenderTarget(const Device& pDevice, uint32 numViews) {

    const DeviceDX& m_device = static_cast<const DeviceDX&>(pDevice);

    //m_device.m_pImmediateContext->OMSetRenderTargets(1, &m_viewsVec[0], nullptr);
    m_device.m_pImmediateContext->OMSetRenderTargets(1, &m_pRenderTargetView, nullptr);
  }

  void
  RenderTargetViewDX::setRenderTarget(const Device& pDevice, const DepthStencylView& pDSV) {

    const DeviceDX& m_device = static_cast<const DeviceDX&>(pDevice);
    const DepthStencylViewDX& m_DSV = static_cast<const DepthStencylViewDX&>(pDSV);


    //m_device.m_pImmediateContext->OMSetRenderTargets(m_viewsVec.size(), &m_viewsVec[0], m_DSV.m_pDepthStencilView);
    m_device.m_pImmediateContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_DSV.m_pDepthStencilView);


  }

  void
  RenderTargetViewDX::cleanRTV() {
      m_pRenderTargetView->Release();
    
  }

  void
  RenderTargetViewDX::clearRenderTarget(Device* pDevice, Vector4 clearColor) {

    DeviceDX* m_pDevice = static_cast<DeviceDX*>(pDevice);
    
    m_pDevice->m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView,
                                                          &clearColor[0]);
  }

  void
  RenderTargetViewDX::clearRenderTargets(Device* pDevice, Vector4 clearColor) {

    DeviceDX* m_pDevice = static_cast<DeviceDX*>(pDevice);

    for (auto& rt : m_viewsVec)
    {
      m_pDevice->m_pImmediateContext->ClearRenderTargetView(rt, &clearColor[0]);
    }
  }

}
