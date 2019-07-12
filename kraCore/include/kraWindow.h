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
                                                        m_name(name),
                                                        m_position(position)
     {}

     virtual ~Window() {}

     virtual bool
     initWindow(int nCmdShow) = 0;

     virtual void
     handleMSG(void* msg, kraInputManager& inputManager) = 0;
      
     virtual void
     release() = 0;

     bool m_isOpen;

   protected:

       uint32 m_width;
       uint32 m_height;
       String m_name;
       Vector2 m_position;

  };
}