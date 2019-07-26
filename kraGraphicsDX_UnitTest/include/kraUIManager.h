#pragma once
#include <windows.h>
#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>

//using namespace kraEngineSDK;

class UIManager {
 
 public:

  bool 
  initUI(void* hWnd, void* device, void* ctx);

  void
  updateUI();

  void
  renderUI();

  void
  shutDown();

  void
  showHelloWindow();

};