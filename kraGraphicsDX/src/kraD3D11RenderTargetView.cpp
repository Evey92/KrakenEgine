#include "kraD3D11RenderTargetView.h"


namespace kraEngineSDK {

  bool
  RenderTargetViewDX::createRenderTargetView(void* pDevice,
      void* pSwapChain) {

    ID3D11Device* m_pDevice = reinterpret_cast<ID3D11Device*>(pDevice);
    IDXGISwapChain* m_pSwapChain = reinterpret_cast<IDXGISwapChain*>(pSwapChain);

    ID3D11Texture2D* pBackBuffer = NULL;
    HRESULT hr = S_OK;
    hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

    if (FAILED(hr))
      return hr;

    m_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);
    pBackBuffer->Release();

    return hr;
  }

  void
  RenderTargetViewDX::cleanRTV() {
    m_pRenderTargetView->Release();
  }

}
