#include <kraDevice.h>
#include <kraSwapChain.h>
#include <kraD3D11DepthStencylView.h>

#include "kraPrerequisitesGFX.h"
#include "kraD3D11RenderTargetView.h"
#include "kraD3D11Device.h"
#include "kraD3D11SwapChain.h"

namespace kraEngineSDK {

  bool
  RenderTargetViewDX::createRenderTargetView(const Device& pDevice) {

    const DeviceDX& m_pDevice = static_cast<const DeviceDX&>(pDevice);
    //SwapChainDX* m_pSwapChain = reinterpret_cast<SwapChainDX*>(pSwapChain);

    ID3D11Texture2D* pBackBuffer = nullptr;
    HRESULT hr = S_OK;
    
    hr = m_pDevice.m_pSwapChain.m_pd3dSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&pBackBuffer));

    if (FAILED(hr))
      return false;

    m_pDevice.m_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &m_pRenderTargetView);
    pBackBuffer->Release();

    return true;
  }

  void
    RenderTargetViewDX::setRenderTarget(const Device& pDevice) {

    const DeviceDX& m_device = static_cast<const DeviceDX&>(pDevice);

    m_device.m_pImmediateContext->OMSetRenderTargets(1, &m_pRenderTargetView, nullptr);
  }

  void
  RenderTargetViewDX::setRenderTarget(const Device& pDevice, const DepthStencylView& pDSV) {

    const DeviceDX& m_device = static_cast<const DeviceDX&>(pDevice);
    const DepthStencylViewDX& m_DSV = static_cast<const DepthStencylViewDX&>(pDSV);


    m_device.m_pImmediateContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_DSV.m_pDepthStencilView);


  }

  void
  RenderTargetViewDX::cleanRTV() {
    m_pRenderTargetView->Release();
  }

  void
  RenderTargetViewDX::clearRenderTargetView(Device* pDevice, Vector4 clearColor) {
    DeviceDX* m_pDevice = static_cast<DeviceDX*>(pDevice);

    m_pDevice->m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView,
                                                          &clearColor[0]);
  }

}
