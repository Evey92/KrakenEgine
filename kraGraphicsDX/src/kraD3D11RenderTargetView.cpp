#include "kraD3D11RenderTargetView.h"


namespace kraEngineSDK {

  HRESULT
  RenderTargetView::createRenderTargetView(ID3D11Device* pDevice,
      IDXGISwapChain* pSwapChain) {
    ID3D11Texture2D* pBackBuffer = NULL;
    HRESULT hr = S_OK;
    hr = pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

    if (FAILED(hr))
      return hr;

    pDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);
    pBackBuffer->Release();

    return hr;
  }

  void
  RenderTargetView::cleanRTV() {
    m_pRenderTargetView->Release();
  }

}
