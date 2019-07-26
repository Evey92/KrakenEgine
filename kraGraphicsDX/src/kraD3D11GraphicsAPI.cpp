#include "kraD3D11GraphicsAPI.h"



namespace kraEngineSDK {
  
  bool
  GraphicsAPIDX::initializeAPI(void* g_hWnd) {
        
    m_device = new DeviceDX();

    bool hr = true;
    
    //Init device and Swap Chain        
    hr = m_device->initializeDevice(g_hWnd);
   
    if (!hr)
    {
      throw::std::exception("The Device could not be initialized.");
      return false;
    }
    
    return true;
  }

  void
  GraphicsAPIDX::Render() {
    
    DeviceDX* device = static_cast<DeviceDX*>(m_device);

    device->m_pImmediateContext->DrawIndexed(36, 0, 0);

    device->m_pSwapChain.m_pd3dSwapChain->Present(0, 0);

  }

  void
  GraphicsAPIDX::Cleanup() {
    
    m_device->cleanContextState();
    m_device->cleanSwapChain();
    m_device->cleanContext();
    m_device->cleanDevice();
  }

  Device* 
  GraphicsAPIDX::getDevice()
  {
    return m_device;
  }

}