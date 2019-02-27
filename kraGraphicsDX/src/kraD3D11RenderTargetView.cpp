#include <kraDevice.h>
#include <kraSwapChain.h>

#include "kraPrerequisitesGFX.h"
#include "kraD3D11RenderTargetView.h"
#include "kraD3D11Device.h"
#include "kraD3D11SwapChain.h"

namespace kraEngineSDK {

  bool
  RenderTargetViewDX::createRenderTargetView(Device* pDevice) {

    DeviceDX* m_pDevice = reinterpret_cast<DeviceDX*>(pDevice);
    //SwapChainDX* m_pSwapChain = reinterpret_cast<SwapChainDX*>(pSwapChain);

    ID3D11Texture2D* pBackBuffer = NULL;
    HRESULT hr = S_OK;
    
    hr = m_pDevice->m_pSwapChain.m_pd3dSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

    if (FAILED(hr))
      return hr;

    m_pDevice->m_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);
    pBackBuffer->Release();

    return hr;
  }

  void
  RenderTargetViewDX::cleanRTV() {
    m_pRenderTargetView->Release();
  }

  void
  RenderTargetViewDX::clearRenderTargetView(Device* pDevice, Vector4 clearColor) {
    DeviceDX* m_pDevice = reinterpret_cast<DeviceDX*>(pDevice);

    m_pDevice->m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView,
                                                          &clearColor[0]);
  }

}
