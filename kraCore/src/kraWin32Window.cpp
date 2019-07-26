#include "kraWin32Window.h"

namespace kraEngineSDK {
  LRESULT CALLBACK
  WndProc(HWND, UINT, WPARAM, LPARAM);

  Win32Window::Win32Window(uint32 width, uint32 height, String name, Vector2 position)
  : Window(width, height, name, position) {

  }

  Win32Window::~Win32Window() {
    release();
  }

  bool
  Win32Window::initWindow(int nCmdShow) {
    WNDCLASSEX wcex;
    
    m_hInstance = GetModuleHandle(nullptr);

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = m_hInstance;
    wcex.hIcon = LoadIcon(m_hInstance, IDI_WINLOGO);
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = m_name.c_str();
    wcex.hIconSm = LoadIcon(m_hInstance, IDI_WINLOGO);

    if (!RegisterClassEx(&wcex))
    {
      return false;
    }

    int style = WS_OVERLAPPEDWINDOW;
    m_hWnd = CreateWindowEx(WS_EX_APPWINDOW, m_name.c_str(), m_name.c_str(),
                            style, m_position.x, m_position.y, m_width, m_height, nullptr,
                            nullptr, m_hInstance, nullptr);

    if (m_hWnd == nullptr)
    {
      return false;
    }

    ShowWindow(m_hWnd, SW_SHOWDEFAULT);
    SetForegroundWindow(m_hWnd);
    SetFocus(m_hWnd);
    UpdateWindow(m_hWnd);

    m_isOpen = true;
    
    return true;

  }

  void
  Win32Window::handleMSG(void* msg, kraInputManager& inputManager) {
    //MSG msg;
    MSG* m_msg = static_cast<MSG*>(msg);

    while (PeekMessage(m_msg, m_hWnd, 0, 0, PM_REMOVE)) {
      TranslateMessage(m_msg);
      DispatchMessage(m_msg);
      continue;
      //inputManager.handleMessage(static_cast<void*>(&m_msg));

      if (m_msg->message == WM_QUIT) {
        m_isOpen = false;
      }
    }
  }

  LRESULT CALLBACK
  WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    
    PAINTSTRUCT ps;
    HDC hdc;

    switch (message)
    {
    case WM_PAINT:
      hdc = BeginPaint(hWnd, &ps);
      EndPaint(hWnd, &ps);
      break;

    case WM_DESTROY:
      PostQuitMessage(0);
      break;

    default:
      return DefWindowProc(hWnd, message, wParam, lParam);

    }

    return 0;
  }


  void
  Win32Window::release()
  {
    //Dealloc Window
  }

}
