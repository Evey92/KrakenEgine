#pragma once
#include "kraPrerequisitesCore.h"
#include "kraWindow.h"
#include <windows.h>

namespace kraEngineSDK {
  class KRA_CORE_EXPORT Win32Window :
  public Window {

   public:

    Win32Window(uint32 width, uint32 height, String name, Vector2 position);

    ~Win32Window();

    bool
    initWindow(int nCmdShow) override;

    void
    handleMSG(void* msg, kraInputManager& inputManager) override;

    void
    release() override;

    HWND m_hWnd;
    HINSTANCE m_hInstance;
    //InputManager* m_inputManager;
  };
}
