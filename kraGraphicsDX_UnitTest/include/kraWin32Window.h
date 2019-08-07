#pragma once
#include <kraWindow.h>
#include <windows.h>

using namespace kraEngineSDK;

  class Win32Window :
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

    HWND m_hWnd = nullptr;
    HINSTANCE m_hInstance = nullptr;
  };
