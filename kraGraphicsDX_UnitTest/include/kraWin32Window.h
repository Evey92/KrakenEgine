#pragma once
#include <kraWindow.h>
#include <windows.h>
#include "Resource.h"

using namespace kraEngineSDK;

typedef LRESULT(*handlers)(HWND, UINT, WPARAM, LPARAM);
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

  HWND&
  gethWnd();
  
private:
  static LRESULT CALLBACK 
  WndProcc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
  
  INT_PTR CALLBACK 
  About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

public:
  HWND m_hWnd = nullptr;
  HINSTANCE m_hInstance = nullptr;
};
