#include <iostream>
#include <windows.h>
#include <gtest/gtest.h>

#include "kraGraphicsDX_UnitTest.h"
#include "OIS.h"

using namespace kraEngineSDK;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                      _In_opt_ HINSTANCE hPrevInstance,
                      _In_ LPWSTR    lpCmdLine,
                      _In_ int       nCmdShow){
  AllocConsole();
  if (!freopen("CONOUT$", "w", stdout)) {
    return 0;
  }

  if (!freopen("CONOUT$", "w", stderr)) {
    return 0;
  }

  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);
  SetConsoleTitle("Kraken Engine Debug Console");


  UIManager::StartUp<UIManager>();
  BaseApplication::StartUp<WinApp>(nCmdShow);

  BaseApplication::instance().run();
  
 
  return 0;
}
