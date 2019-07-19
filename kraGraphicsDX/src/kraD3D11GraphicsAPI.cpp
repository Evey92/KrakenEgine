#include "kraD3D11GraphicsAPI.h"



namespace kraEngineSDK {
  
  Device*
  GraphicsAPIDX::initializeAPI(void* g_hWnd) {
        
    bool hr = true;
    
    //Init device and Swap Chain        
    hr = m_device.initializeDevice(g_hWnd);
   
    if (!hr)
    {
      return nullptr;
      throw::std::exception("The Device could not be initialized.");
    }
    
    return &m_device;
  }

  void
  GraphicsAPIDX::Render() {
    
    m_device.m_pImmediateContext->DrawIndexed(36, 0, 0);

    m_device.m_pSwapChain.m_pd3dSwapChain->Present(0, 0);

  }

  void
  GraphicsAPIDX::Cleanup() {
    
    m_device.cleanContextState();
    m_device.cleanSwapChain();
    m_device.cleanContext();
    m_device.cleanDevice();
  }
}