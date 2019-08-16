#pragma once
#include <windows.h>

#include "kraPrerequisitesCore.h"
#include "kraInputManager.h"

namespace kraEngineSDK {
  class KRA_CORE_EXPORT Window
  {
   public:

     Window(uint32 width, uint32 height, String name, Vector2 position) : m_width(width), 
                                                        m_height(height),
                                                        m_nameW(std::move(name)),
                                                        m_position(position),
                                                        m_isOpen(true)
     {}

     virtual ~Window() {}

     virtual bool
     initWindow(int nCmdShow) = 0;

     virtual void
     handleMSG(void* msg, kraInputManager& inputManager) = 0;
      
     virtual void
     release() = 0;

     uint32
     getWidth();

     uint32
     getHeight();

     bool
     isOpen();

     bool
     isWindowed();

   protected:
     
     Vector2 m_position = Vector2::ZERO;
     String m_nameW;
     uint32 m_width;
     uint32 m_height;
     bool m_isOpen = false;
     bool m_isWindowed = true;

  };
}