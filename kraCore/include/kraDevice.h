#pragma once
#include "kraPrerequisitesCore.h"

namespace kraEngineSDK {
  class Device
  {
  public:
    Device() = default;
    virtual ~Device()  {}

    virtual bool
    initializeDevice(void* g_hWnd) = 0;
    virtual void
    setRenderTarget(void* pRTV, void* pDSV) = 0;
    virtual void
    cleanContext() = 0;
    virtual void
    cleanDevice() = 0;
    virtual void
    cleanSwapChain() = 0;
    virtual void
    cleanContextState() = 0;
  };
}