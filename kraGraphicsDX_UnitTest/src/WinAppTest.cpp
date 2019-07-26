#include "WinAppTest.h"

bool
WinApp::startUp(int nCmdShow) {

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
    if (!m_window->initWindow(nCmdShow))
    {
      std::cout << "Window couldn't be initialized.\n";
    }

    if (!m_gfxAPIInstance->initializeAPI(reinterpret_cast<void*>(m_window->m_hWnd)))
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

    Initialize();
    return true;
}

void 
WinApp::preInitialice()
{

}

//Initializing App systems
bool
WinApp::Initialize()
{

  

  m_mainRenderTarget->createRenderTargetView(*m_gfxAPIInstance->getDevice());

  m_depthStencil->setDepthStencil(*m_gfxAPIInstance->getDevice(), m_gfxAPIInstance->getDevice()->getHeight(), m_gfxAPIInstance->getDevice()->getWidth());

  m_depthStencil->createDepthStencilState(*m_gfxAPIInstance->getDevice());

  m_depthStencil->setDepthStencilState(*m_gfxAPIInstance->getDevice());

  m_depthStencilView->createDepthStencilView(*m_gfxAPIInstance->getDevice(), *m_depthStencil);

  m_mainRenderTarget->setRenderTarget(*m_gfxAPIInstance->getDevice(), *m_depthStencilView, 1);

  

  m_viewport->createViewport(m_gfxAPIInstance->getDevice()->getWidth(), m_gfxAPIInstance->getDevice()->getHeight(), 0.0f, 0.0f);

  m_viewport->setViewport(m_gfxAPIInstance->getDevice());

  //defaultScene->initialize();
  //m_sceneManager;
  //SceneNode* root = new SceneNode(0);
  /*GameObject camera;
  
  camera.addComponent<Camera*>(camera, Vector3(0.0f, 50.0f, 0.0f));*/

  //root->initialize(&camera);

  //m_defaultScene->addNode(newNode);


  if(!m_UIManager.initUI(reinterpret_cast<void*>(m_window->m_hWnd),
                     m_gfxAPIInstance->getDevice()->getDevice(),
                     m_gfxAPIInstance->getDevice()->getContext())) {
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
  while (m_window->m_isOpen)
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
  m_UIManager.updateUI();
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
  m_mainRenderTarget->setRenderTarget(*m_gfxAPIInstance->getDevice(), *m_depthStencilView, 1);

  ClearColor = { 0.329f, 0.050f, 0.431f, 1.0f };
  m_mainRenderTarget->clearRenderTargetView(m_gfxAPIInstance->getDevice(), ClearColor);

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
  ::DestroyWindow(m_window->m_hWnd);
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
