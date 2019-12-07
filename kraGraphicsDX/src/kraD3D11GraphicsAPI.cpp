#include "kraD3D11GraphicsAPI.h"



namespace kraEngineSDK {
  
  bool
  GraphicsAPIDX::initializeAPI(void* g_hWnd) {
        
    m_device = make_shared<DeviceDX>();

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
    
  }

  void
  GraphicsAPIDX::Cleanup() {
    
    m_device->cleanContextState();
    m_device->cleanSwapChain();
    m_device->cleanContext();
    m_device->cleanDevice();
  }

  void 
  GraphicsAPIDX::onStartUp()
  {
    
  }

  void 
  GraphicsAPIDX::onShutdown()
  {
    
  }

  ShrdPtr<Device>
  GraphicsAPIDX::getDevice()
  {
    return m_device;
  }

}