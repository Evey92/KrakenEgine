#include "WinAppTest.h"

void 
WinApp::preInitialice()
{

}

//Initializing App systems
bool
WinApp::Initialize()
{
  std::ostringstream stream;
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
  if (!m_window->initWindow(m_nCmdShow))
  {
    std::cout << "Window couldn't be initialized.\n";
  }

  if (!m_gfxAPIInstance->initializeAPI(m_window->m_hWnd))
  {
    MessageBox(NULL, "Failed to Initialize Graphics API Device", "Error", MB_OK);
    return false;
  }
  m_inputManager = m_inputAPIInstance->initializeAPI(m_gfxAPIInstance->getDevice()->getWidth(), m_gfxAPIInstance->getDevice()->getHeight());
  if (!m_inputManager)
  {
    MessageBox(NULL, "Failed to create Initialize Input Manager", "Error", MB_OK);
    return false;
  }

  m_mainRenderTarget = m_gfxAPIInstance->getDevice()->createRenderTargetInsttance();
  if (!m_mainRenderTarget)
  {
    MessageBox(NULL, "Failed to create Render Target", "Error", MB_OK);
    return false;
  }

  m_depthStencil = m_gfxAPIInstance->getDevice()->createDepthStencilInstance();
  if (!m_depthStencil)
  {
    MessageBox(NULL, "Failed to create Depth Stencil", "Error", MB_OK);
    return false;
  }

  m_depthStencilView = m_gfxAPIInstance->getDevice()->createDepthStencilViewInstance();
  if (!m_depthStencilView)
  {
    MessageBox(NULL, "Failed to create Depth Stencil View", "Error", MB_OK);
    return false;
  }


  m_viewport = m_gfxAPIInstance->getDevice()->createViewportInstance();
  if (!m_viewport)
  {
    MessageBox(NULL, "Failed to create Viewport", "Error", MB_OK);
    return false;
  }

  m_mainRenderTarget->createRenderTargetView(*m_gfxAPIInstance->getDevice());

  m_depthStencil->setDepthStencil(*m_gfxAPIInstance->getDevice(), m_gfxAPIInstance->getDevice()->getHeight(), m_gfxAPIInstance->getDevice()->getWidth());

  m_depthStencil->createDepthStencilState(*m_gfxAPIInstance->getDevice());

  m_depthStencil->setDepthStencilState(*m_gfxAPIInstance->getDevice());

  m_depthStencilView->createDepthStencilView(*m_gfxAPIInstance->getDevice(), *m_depthStencil);

  m_mainRenderTarget->setRenderTarget(*m_gfxAPIInstance->getDevice(), *m_depthStencilView);

  

  m_viewport->createViewport(m_gfxAPIInstance->getDevice()->getWidth(), m_gfxAPIInstance->getDevice()->getHeight(), 0.0f, 0.0f);

  m_viewport->setViewport(m_gfxAPIInstance->getDevice());

  m_sceneManager = new SceneManager();

  m_sceneManager->createDefaultScene();

  

  if(!m_UIManager.initUI(reinterpret_cast<void*>(m_window->m_hWnd),
                     m_gfxAPIInstance->getDevice()->getDevice(),
                     m_gfxAPIInstance->getDevice()->getContext(), this)) {
    Log("Couldn't initiate UI");
  }

  return true;
}

void 
WinApp::postInitialice()
{

}

void 
WinApp::run()
{
  MSG msg = { 0 };
  while (m_window->isOpen())
  {
    m_window->handleMSG(static_cast<void*>(&msg), *m_inputManager);
    update();
    render();
  }

  destroy();
}

void 
WinApp::preUpdate()
{

}

void 
WinApp::update()
{
  m_UIManager.updateUI(m_sceneManager->getActiveScene());
}

void 
WinApp::update(float deltaTime)
{

}

void 
WinApp::postUpdate()
{

}

void 
WinApp::render()
{
  m_mainRenderTarget->setRenderTarget(*m_gfxAPIInstance->getDevice(), *m_depthStencilView);

  m_mainRenderTarget->clearRenderTarget(m_gfxAPIInstance->getDevice(), ClearColor);

  m_UIManager.renderUI();

  m_gfxAPIInstance->getDevice()->PresentSwapChain();

}

void 
WinApp::postRender()
{

}

void 
WinApp::preDestroy()
{

}

void 
WinApp::destroy()
{
  ::DestroyWindow(reinterpret_cast<HWND>(m_window->m_hWnd));
}

kraInputManager* 
WinApp::getInputManager()
{
  return m_inputManager;
}


void WinApp::MapBoolDevice(uint32 userBtn, uint32 deviceID, uint32 key)
{

}

Camera* 
WinApp::getActiveCamera()
{
  return m_activeCam;
}

void
WinApp::setActiveCamera(Camera* newCam)
{
  m_activeCam = newCam;
}

bool WinApp::LoadModel()
{
  std::cout << "Load Model\n";
  return true;
}
