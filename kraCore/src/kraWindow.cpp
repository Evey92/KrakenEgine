#include "kraWindow.h"

namespace kraEngineSDK {
  
  uint32 
  Window::getWidth() {
    return m_width;
  }

  uint32
  Window::getHeight()
  {
    return m_height;
  }

  bool Window::isOpen()
  {
    return m_isOpen;
  }

  bool
  Window::isWindowed()
  {
    return m_isWindowed;
  }

}


