// kraGraphicsDX_UnitTest.cpp : Defines the entry point for the application.
//


#include <iostream>
#include <windows.h>
#include <gtest/gtest.h>

#include "kraGraphicsDX_UnitTest.h"
#include "kraApp.h"
#include "OIS.h"

#define MAX_LOADSTRING 100

enum Button
{
  Dkey,
  AKey,
  WKey,
  SKey,
  SPACEKey,
  CTRLKey,
  QKey,
  EKey,
  MouseX,
  MouseY
};

enum Device {
  Mouse,
  Keyboard,
  Gamepad,
};

//using namespace kraEngineSDK;

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND g_hWnd;
//typedef GraphicsAPI*( *initFunc)();
//
//std::string GFXPath = "$(SolutionDir)lib/$(PlatformTarget)/kraGraphicsDXd.dll";
App appInstance;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
  _In_opt_ HINSTANCE hPrevInstance,
  _In_ LPWSTR    lpCmdLine,
  _In_ int       nCmdShow)
{
  AllocConsole();
  freopen("CONOUT$", "w", stdout);
  freopen("CONOUT$", "w", stderr);

  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  // Initialize global strings
  //LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
  wcscpy(szTitle, L"Kraken Engine Test App"); ;
  LoadStringW(hInstance, IDC_KRAGRAPHICSDXUNITTEST, szWindowClass, MAX_LOADSTRING);
  MyRegisterClass(hInstance);


  // Perform application initialization:
  if (!InitInstance(hInstance, nCmdShow))
  {

    return FALSE;
  }

  if (!appInstance.startUp(reinterpret_cast<void*>(g_hWnd))) {
    return FALSE;
  }

  if (!appInstance.LoadModel())
  {
    std::cout << "There was an error while initiating graphics pipeline\n";
    return FALSE;
  }

  uint32 KeyDValue = 68;
  uint32 keyAValue = 65;
  uint32 keyWValue = 87;
  uint32 keySValue = 83;
  uint32 keyQValue = 81;
  uint32 keyEValue = 69;
  uint32 keySPACEValue = 32;
  uint32 keyCTRLValue = 130;
  uint32 mouseXvalue = 21;
  uint32 mouseyvalue = 22;
  uint32 keyboardID;
  uint32 mouseID;

  keyboardID = appInstance.createBoolDevice(Keyboard);
  mouseID = appInstance.createBoolDevice(Mouse);

  appInstance.getInputManager()->setInputMap();
  appInstance.MapBoolDevice(Dkey, keyboardID, KeyDValue);
  appInstance.MapBoolDevice(AKey, keyboardID, keyAValue);
  appInstance.MapBoolDevice(WKey, keyboardID, keyWValue);
  appInstance.MapBoolDevice(SKey, keyboardID, keySValue);
  appInstance.MapBoolDevice(QKey, keyboardID, keyQValue);
  appInstance.MapBoolDevice(EKey, keyboardID, keyEValue);
  appInstance.MapBoolDevice(SPACEKey, keyboardID, keySPACEValue);
  appInstance.MapBoolDevice(CTRLKey, keyboardID, keyCTRLValue);

  appInstance.getInputManager()->mapFloatDevice(MouseX, mouseID, mouseXvalue);
  appInstance.getInputManager()->mapFloatDevice(MouseY, mouseID, mouseyvalue);

  HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_KRAGRAPHICSDXUNITTEST));

  MSG msg = { 0 };

  


  // Main message loop:
  while (WM_QUIT != msg.message)
  {
    appInstance.getInputManager()->managerUpdate();

    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);

      appInstance.getInputManager()->handleMessage(static_cast<void*>(&msg));
    }
    else
    {
      appInstance.render();

      if (appInstance.getInputManager()->boolWasDown(Dkey)) {
        appInstance.getActiveCamera()->MoveRight(10.0f);
        //MessageBox(NULL, "Presionaste la tecla D", "Event", MB_OK);

      }
      else if (appInstance.getInputManager()->boolWasDown(AKey))
      {
        //MessageBox(NULL, "Presionaste la tecla A", "Event", MB_OK);
        appInstance.getActiveCamera()->MoveRight(-10.0f);
      }
      else if (appInstance.getInputManager()->boolWasDown(WKey))
      {
        //MessageBox(NULL, "Presionaste la tecla W", "Event", MB_OK);
        appInstance.getActiveCamera()->MoveForward(10.0f);
      }
      else if (appInstance.getInputManager()->boolWasDown(SKey))
      {
        //MessageBox(NULL, "Presionaste la tecla S", "Event", MB_OK);
        appInstance.getActiveCamera()->MoveForward(-10.0f);
      }
      else if (appInstance.getInputManager()->boolWasDown(SPACEKey))
      {
        //MessageBox(NULL, "Presionaste la tecla W", "Event", MB_OK);
        appInstance.getActiveCamera()->MoveUP(10.0f);
      }
      else if (appInstance.getInputManager()->boolWasDown(CTRLKey))
      {
        //MessageBox(NULL, "Presionaste la tecla S", "Event", MB_OK);
        appInstance.getActiveCamera()->MoveUP(-10.0f);
      }
      else if (appInstance.getInputManager()->boolWasDown(QKey))
      {
        appInstance.rotateCamera(10);
      }
      else if (appInstance.getInputManager()->boolWasDown(EKey))
      {
        appInstance.rotateCamera(-10);

      }
    }
    //appInstance.update();

  }

  appInstance.CleanupDevice();

  return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
  WNDCLASSEXW wcex;

  wcex.cbSize = sizeof(WNDCLASSEX);

  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc = WndProc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = hInstance;
  wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_KRAGRAPHICSDXUNITTEST));
  wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_KRAGRAPHICSDXUNITTEST);
  wcex.lpszClassName = szWindowClass;
  wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

  return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
  hInst = hInstance; // Store instance handle in our global variable

  g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

  if (!g_hWnd)
  {
    return FALSE;
  }

  ShowWindow(g_hWnd, nCmdShow);
  UpdateWindow(g_hWnd);

  return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message)
  {
  case WM_COMMAND:
  {
    int wmId = LOWORD(wParam);
    // Parse the menu selections:
    switch (wmId)
    {
    case IDM_ABOUT:
      DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
      break;
    case IDM_EXIT:
      DestroyWindow(hWnd);
      break;
    default:
      return DefWindowProc(hWnd, message, wParam, lParam);
    }
  }
  break;
  case WM_PAINT:
  {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);
    EndPaint(hWnd, &ps);
  }
  break;
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  default:
    return DefWindowProcW(hWnd, message, wParam, lParam);
  }
  return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
  UNREFERENCED_PARAMETER(lParam);
  switch (message)
  {
  case WM_INITDIALOG:
    return (INT_PTR)TRUE;

  case WM_COMMAND:
    if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
    {
      EndDialog(hDlg, LOWORD(wParam));
      return (INT_PTR)TRUE;
    }
    break;
  }
  return (INT_PTR)FALSE;
}
