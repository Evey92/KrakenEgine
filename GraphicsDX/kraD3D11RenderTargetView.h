#pragma once
#include "kraPrerequisitesGFX.h"


namespace kraEngineSDK {
  class kraD3D11RenderTargetView
  {
  public:
    kraD3D11RenderTargetView();
    ~kraD3D11RenderTargetView();

    HRESULT
    createRenderTargetView(ID3D11Device* pDevice,
                           ID3D11Texture2D* pBackBuffer,
                           IDXGISwapChain* pSwapChain);

    ID3D11RenderTargetView* m_pRenderTargetView;
  };

  HRESULT
  kraD3D11RenderTargetView::createRenderTargetView(ID3D11Device* pDevice,
                                                   ID3D11Texture2D* pBackBuffer,
                                                   IDXGISwapChain* pSwapChain) {
    HRESULT hr = S_OK;
    hr = pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

    if (FAILED(hr))
      return hr;

    pDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);
    pBackBuffer->Release();

    return hr;
  }

}
