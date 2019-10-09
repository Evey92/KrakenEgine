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

  //TODO: I REALLY NEED TO FIX THIS BULLSHIT. I need to make something to handle dynamic library loading. 

  GFXDLL = LoadLibraryEx(GFXpath.c_str(), nullptr, LOAD_WITH_ALTERED_SEARCH_PATH);
  if (!GFXDLL) {
    DWORD err = GetLastError();
    MessageBox(NULL, "Could not find specified graphics DLL. Error: " + err, "Error", MB_OK);

    FreeLibrary(GFXDLL);
    return false;
  }

  INPUTDLL = LoadLibraryEx(Inputpath.c_str(), nullptr, LOAD_WITH_ALTERED_SEARCH_PATH);
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
  if (!initInputAPIFunc) {
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

  String name = "Kraken Engine";

  m_window = new Win32Window(1600, 1040, name, Vector2(0, 0));
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

  m_textureManager = m_gfxAPIInstance->getDevice()->createTextureInstance();
  if (!m_textureManager)
  {
    MessageBox(NULL, "Failed to create Texture Manager", "Error", MB_OK);
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

  CameraManager::StartUp<CameraManager>();
  SceneManager::StartUp<SceneManager>();
  


  if(!UIManager::instance().initUI(reinterpret_cast<void*>(m_window->m_hWnd),
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
  while (m_window->isOpen())
  {
    m_window->handleMSG(static_cast<void*>(&msg), *m_inputManager);
    update();
    render();
  }

  destroy();
  return;
}

void 
WinApp::preUpdate()
{

}

void 
WinApp::update()
{
  UIManager::instance().updateUI(SceneManager::instance().getActiveScene());
}

void 
WinApp::update(float deltaTime)
{
  deltaTime;
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

  UIManager::instance().renderUI();

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


void 
WinApp::MapBoolDevice(uint32 userBtn, uint32 deviceID, uint32 key)
{
  userBtn;
  deviceID;
  key;
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

bool WinApp::loadModel()
{
  String filename = loadFile();

  if (filename != "") {

    int strPos = filename.find_last_of('\\');
    String name = filename.substr(strPos + 1);

    GameObject* newGO = SceneManager::instance().createGameObject(name);
    newGO->addComponent<Model>(newGO);
    newGO->getComponent<Model>().loadModelFromFile(filename, *m_gfxAPIInstance->getDevice());
    SceneManager::instance().getActiveScene()->addNewNode(newGO);
  }

  return true;
}

bool 
WinApp::loadTexture()
{
  //TODO: Texture loading
  String filename = loadFile();
  //m_textureManager->createTexture2D();
  return true;
}

String 
WinApp::loadFile()
{
  char filename[MAX_PATH];
  memset(&filename, 0, sizeof(filename));

  OPENFILENAME ofn;
  memset(&ofn, 0, sizeof(ofn));

  ofn.lStructSize = sizeof(ofn);
  ofn.hwndOwner = m_window->m_hWnd;
  ofn.lpstrFilter = "FBX Files\0*.fbx\0OBJ Files\0*.obj\0Any File\0*.*\0";
  ofn.lpstrFile = filename;
  ofn.nMaxFile = MAX_PATH;
  ofn.lpstrTitle = "Choose a File!";
  ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

  if (GetOpenFileName(&ofn))
  {
    std::cout << "You chose the file \"" << filename << "\"\n";
    return filename;
  }
  else
  {
    std::cout << "There was an error and the file couldn't be opened";
    return "";
  }

}

//HINSTANCE 
//WinApp::loadDLL()
//{
//  HINSTANCE hinstance
//  //do dll loading
//}

void 
WinApp::CleanupDevice()
{
  //do cleanup
}


