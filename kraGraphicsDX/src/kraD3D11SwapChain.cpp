#include "kraD3D11SwapChain.h"

namespace kraEngineSDK {

  void
  SwapChainDX::setSwapChainDescriptor(void* g_hWnd, int width, int height, void* swapDescriptor) {
    
    HWND m_hWnd = reinterpret_cast<HWND>(g_hWnd);
    DXGI_SWAP_CHAIN_DESC* sd = reinterpret_cast<DXGI_SWAP_CHAIN_DESC*>(swapDescriptor);

    memset(&sd, 0, sizeof(sd));
    sd->BufferCount = 1;
    sd->BufferDesc.Width = width;
    sd->BufferDesc.Height = height;
    sd->BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd->BufferDesc.RefreshRate.Numerator = 60;
    sd->BufferDesc.RefreshRate.Denominator = 1;
    sd->BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd->OutputWindow = m_hWnd;
    sd->SampleDesc.Count = 1;
    sd->SampleDesc.Quality = 0;
    sd->Windowed = TRUE;
  }

}