#include "WinAppTest.h"

bool
WinAppTest::startUp(void* m_hWnd, int nCmdShow) {

  typedef GraphicsAPI* (*initGFXFunc)();
  typedef InputAPI* (*initInptFunc)();

  HINSTANCE GFXDLL;
  HINSTANCE INPUTDLL;

  std::string GFXpath = "kraGraphicsDXd.dll";
  std::string Inputpath = "kraInputManagerd.dll";

  GFXDLL = LoadLibraryExA(GFXpath.c_str(), nullptr, LOAD_WITH_ALTERED_SEARCH_PATH);
  if (!GFXDLL) {
    DWORD err = GetLastError();
    MessageBox(NULL, "Could not find specified graphics DLL. Error: " + err, "Error", MB_OK);

    FreeLibrary(GFXDLL);
    return false;
  }

  INPUTDLL = LoadLibraryExA(Inputpath.c_str(), nullptr, LOAD_WITH_ALTERED_SEARCH_PATH);
  if (!INPUTDLL) {
    DWORD err = GetLastError();
    MessageBox(NULL, "Could not find specified input DLL. Error: " + err, "Error", MB_OK);

    FreeLibrary(INPUTDLL);
    return false;
  }

  initGFXFunc initAPIFunc = (initGFXFunc)GetProcAddress(GFXDLL, "createGraphicsAPI");
    if (!initAPIFunc) {
      MessageBox(NULL, "Could not find specified graphics function. Error: ", "Error", MB_OK);

      FreeLibrary(GFXDLL);
      return false;
    }

    initInptFunc initInputAPIFunc = (initInptFunc)GetProcAddress(INPUTDLL, "createInputAPI");
    if (!initAPIFunc) {
      MessageBox(NULL, "Could not find specified input function. Error: ", "Error", MB_OK);

      FreeLibrary(INPUTDLL);
      return false;
    }

    m_gfxAPIInstance = initAPIFunc();
    if (!m_gfxAPIInstance) {
      MessageBox(NULL, "Failed to create Graphics API", "Error", MB_OK);

      return false;
    }

    m_inputAPIInstance = initInputAPIFunc();
    if (!m_inputAPIInstance) {
      MessageBox(NULL, "Failed to create Input API", "Error", MB_OK);

      return false;
    }

    m_window = new Win32Window(1600, 1000, "Kraken Engine Test Application", Vector2(0, 0));
    if (!m_window->initWindow(nCmdShow))
    {
      std::cout << "Window couldn't be initialized.\n";
    }

    Initialize(m_hWnd);
    return true;
}

void 
WinAppTest::preInitialice()
{

}

bool
WinAppTest::Initialize(void* m_hWnd)
{

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;
  ImGui::StyleColorsDark();
  ImGui_ImplWin32_Init(m_hWnd);
  ImGui_ImplDX11_Init(m_device->getDevice(), m_device->getContext());



  //Initializing App systems
  m_device = m_gfxAPIInstance->initializeAPI(reinterpret_cast<void*>(m_window->m_hWnd));
  if (!m_device)
  {
    MessageBox(NULL, "Failed to create Initialize API Device", "Error", MB_OK);
    return false;
  }

  m_inputManager = m_inputAPIInstance->initializeAPI(m_device->getWidth(), m_device->getHeight());
  if (!m_device)
  {
    MessageBox(NULL, "Failed to create Initialize Input Manager", "Error", MB_OK);
    return false;
  }

  //defaultScene->initialize();
  m_sceneManager;
  SceneNode* root = new SceneNode(0);
  GameObject* camera = new GameObject();
  
  Camera* mainCam = new Camera();
  mainCam->setFOV(kraMath::DEG2RAD(90.0f));
  mainCam->setNearPlane(0.01f);
  mainCam->setFarPlane(10000.0f);

  setActiveCamera(mainCam);

  camera->addComponet(mainCam);

  root->initialize(camera);

  //m_defaultScene->addNode(newNode);


  return true;
}

void 
WinAppTest::postInitialice()
{

}

void 
WinAppTest::run()
{
  MSG msg = { 0 };
  while (m_window->m_isOpen)
  {
    m_window->handleMSG(static_cast<void*>(&msg), *m_inputManager);
    update();
   
  }

  destroy();
}

void 
WinAppTest::preUpdate()
{

}

void 
WinAppTest::update()
{
  // Start the Dear ImGui frame
  ImGui_ImplDX11_NewFrame();
  ImGui_ImplWin32_NewFrame();
}

void 
WinAppTest::update(float deltaTime)
{

}

void 
WinAppTest::postUpdate()
{

}

void 
WinAppTest::render()
{

}

void 
WinAppTest::postRender()
{

}

void 
WinAppTest::preDestroy()
{

}

void 
WinAppTest::destroy()
{
  ImGui_ImplDX11_Shutdown();
  ImGui_ImplWin32_Shutdown();
  ImGui::DestroyContext();
  ::DestroyWindow(m_window->m_hWnd);
}

Camera* 
WinAppTest::getActiveCamera()
{
  return m_activeCam;
}

void
WinAppTest::setActiveCamera(Camera* newCam)
{
  m_activeCam = newCam;
}
