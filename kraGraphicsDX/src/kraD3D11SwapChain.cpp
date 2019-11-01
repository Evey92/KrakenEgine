#include "kraD3D11SwapChain.h"

namespace kraEngineSDK {

  void
  SwapChainDX::setSwapChainDescriptor(void* g_hWnd, int width, int height) {
    
    HWND m_hWnd = reinterpret_cast<HWND>(g_hWnd);

    DXGI_SWAP_CHAIN_DESC sd;
    
    memset(&sd, 0, sizeof(sd));
    sd.BufferCount = 1;
    sd.BufferDesc.Width = width;
    sd.BufferDesc.Height = height;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = m_hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = true;
  }

  void
  SwapChainDX::present(uint32 interval, uint32 flags) {
    m_pd3dSwapChain->Present(interval, flags);
  }

}