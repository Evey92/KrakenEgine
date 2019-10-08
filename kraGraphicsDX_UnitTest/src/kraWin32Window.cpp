#include "kraWin32Window.h"

  LRESULT CALLBACK
  WndProc(HWND, UINT, WPARAM, LPARAM);

  Win32Window::Win32Window(uint32 width, uint32 height, String name, Vector2 position)
  : Window(width, height, name, position) {
    m_name = name;
  }

  Win32Window::~Win32Window() {
    release();
  }

  bool
  Win32Window::initWindow(int nCmdShow) {
    
    WNDCLASSEXA wcex;
    
    m_hInstance = GetModuleHandle(nullptr);


    wcex.cbSize = sizeof(WNDCLASSEXA);
    wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wcex.lpfnWndProc = Win32Window::WndProcc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = m_hInstance;
    wcex.hIcon = LoadIconA(GetModuleHandle(nullptr), MAKEINTRESOURCE(IDI_ICON2));
	wcex.hIconSm = (HICON)LoadImageA(GetModuleHandle(nullptr), MAKEINTRESOURCE(IDI_ICON2), IMAGE_ICON, 16, 16, 0);
	wcex.cbSize = sizeof(WNDCLASSEXA);
    wcex.hCursor = LoadCursorA(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = m_name.c_str();

    if (!RegisterClassExA(&wcex))
    {
      return false;
    }

    int style = WS_OVERLAPPEDWINDOW;
    m_hWnd = CreateWindowExA(WS_EX_APPWINDOW,
                            m_name.c_str(),
                            m_name.c_str(),
                            style, 
                            m_position.x,
                            m_position.y,
                            m_width,
                            m_height,
                            nullptr,
                            nullptr,
                            m_hInstance,
                            nullptr);

    if (m_hWnd == nullptr)
    {
      return false;
    }

    ShowWindow(m_hWnd, SW_SHOWDEFAULT);
    SetForegroundWindow(m_hWnd);
    SetFocus(m_hWnd);
    SetWindowText(m_hWnd, m_name.c_str());
    UpdateWindow(m_hWnd);

    m_isOpen = true;
    
    return true;

  }

  void
  Win32Window::handleMSG(void* msg, kraInputManager& inputManager) {
    //MSG msg;
    MSG* m_msg = static_cast<MSG*>(msg);

    while (PeekMessageA(m_msg, m_hWnd, 0, 0, PM_REMOVE)) {
      TranslateMessage(m_msg);
      DispatchMessageA(m_msg);
      continue;

      if (m_msg->message == WM_QUIT) {
        m_isOpen = false;
      }
    }
  }

  void
  Win32Window::release()
  {
    //Dealloc Window
  }

  HWND& 
  Win32Window::gethWnd()
  {
    return m_hWnd;
  }

  extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
  LRESULT CALLBACK 
  Win32Window::WndProcc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
  {
    if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
    {
      return true;
    }
    PAINTSTRUCT ps;
    HDC hdc;

    switch (message)
    {
    case WM_COMMAND:
    {
      int wmId = LOWORD(wParam);
      // Parse the menu selections:
      switch (wmId)
      {
      case IDM_EXIT:
        DestroyWindow(hWnd);
        break;
      default:
        return DefWindowProcA(hWnd, message, wParam, lParam);
      }
    }
    break;
    case WM_PAINT:
      hdc = BeginPaint(hWnd, &ps);
      EndPaint(hWnd, &ps);
    break;

    case WM_DESTROY:
      PostQuitMessage(0);
      break;
    default:
      return DefWindowProcA(hWnd, message, wParam, lParam);
    }
    return 0;
  }

  // Message handler for about box.
  INT_PTR CALLBACK
  Win32Window::About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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

