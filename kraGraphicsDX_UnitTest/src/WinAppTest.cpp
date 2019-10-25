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
  typedef RenderPipeline* (*initRenderFunc)();

  HINSTANCE GFXDLL;
  HINSTANCE INPUTDLL;
  HINSTANCE RENDERDLL;

  String GFXpath("kraGraphicsDXd.dll");
  String Inputpath("kraInputManagerd.dll");
  String Renderpath("kraDeferredPBRendererd.dll");

  //TODO: I REALLY NEED TO FIX THIS BULLSHIT. I need to make something to handle dynamic library loading. 

  //Load Graphics API DLL
  GFXDLL = LoadLibraryEx(GFXpath.c_str(), nullptr, LOAD_WITH_ALTERED_SEARCH_PATH);
  if (!GFXDLL) {
    DWORD err = GetLastError();
    MessageBox(NULL, "Could not find specified graphics DLL. Error: " + err, "Error", MB_OK);

    FreeLibrary(GFXDLL);
    return false;
  }

  //Get function to startup Graphics module with selected Graphics API
  initGFXFunc initAPIFunc = (initGFXFunc)GetProcAddress(GFXDLL, "createGraphicsAPI");
  if (!initAPIFunc) {
    MessageBox(NULL, "Could not find specified graphics function. Error: ", "Error", MB_OK);

    FreeLibrary(GFXDLL);
    return false;
  }

  //Startup the graphics module, and get the pointer to the instance
  m_gfxAPIInstance = initAPIFunc();
  if (!m_gfxAPIInstance) {
    MessageBox(NULL, "Failed to create Graphics API", "Error", MB_OK);

    return false;
  }

  // Load Input DLL
  INPUTDLL = LoadLibraryEx(Inputpath.c_str(), nullptr, LOAD_WITH_ALTERED_SEARCH_PATH);
  if (!INPUTDLL) {
    DWORD err = GetLastError();
    MessageBox(NULL, "Could not find specified input DLL. Error: " + err, "Error", MB_OK);

    FreeLibrary(INPUTDLL);
    return false;
  }

  //Get function to startup input module
  initInptFunc initInputAPIFunc = (initInptFunc)GetProcAddress(INPUTDLL, "createInputAPI");
  if (!initInputAPIFunc) {
    MessageBox(NULL, "Could not find specified input function. Error: ", "Error", MB_OK);

    FreeLibrary(INPUTDLL);
    return false;
  }

  //Startup the input module and get the pointer to the instance 
  m_inputAPIInstance = initInputAPIFunc();
  if (!m_inputAPIInstance) {
    MessageBox(NULL, "Failed to create Input API", "Error", MB_OK);

    return false;
  }



  //Create the main window
  String name("Kraken Engine");

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

  //Load Render pipeline DLL
  RENDERDLL = LoadLibraryEx(Renderpath.c_str(), nullptr, LOAD_WITH_ALTERED_SEARCH_PATH);
  if (!RENDERDLL) {
    DWORD err = GetLastError();
    MessageBox(NULL, "Could not find specified renderer DLL. Error.", "Error", MB_OK);

    FreeLibrary(RENDERDLL);
    return false;
  }

  //Get function to startup Render Pipeline module with selected pipeline 
  initRenderFunc initPipelineFunc = (initRenderFunc)GetProcAddress(RENDERDLL, "createRenderPipeline");
  if (!initPipelineFunc) {
    MessageBox(NULL, "Could not find specified render function. Error: ", "Error", MB_OK);

    FreeLibrary(RENDERDLL);
    return false;
  }

  //Startup the graphics module, and get the pointer to the instance
  /*m_renderPipeInstance = initPipelineFunc();
  if (!m_renderPipeInstance) {
    MessageBox(NULL, "Failed to create Renderer", "Error", MB_OK);

    return false;
  }*/

  m_gfxDevice = m_gfxAPIInstance->getDevice();

  //Create The main Render target for Backbuffer
  m_backBufferRTV = m_gfxDevice->createRenderTargetInsttance();
  m_backBufferRTV->createRenderTargetView(*m_gfxDevice);
  m_backBufferRTV->setRenderTarget(*m_gfxDevice, 1);

  //Create and set the viewport
  m_viewport = m_gfxDevice->createViewportInstance();
  m_viewport->createViewport(m_gfxDevice->getWidth(), m_gfxAPIInstance->getDevice()->getHeight(), 0.0f, 0.0f);
  m_viewport->setViewport(m_gfxDevice);

  // Create Depth stencil
  m_defaultDepthStencil = m_gfxDevice->createDepthStencilInstance();
  m_defaultDepthStencil->setDepthStencil(*m_gfxDevice, m_gfxAPIInstance->getDevice()->getHeight(), m_gfxAPIInstance->getDevice()->getWidth());
  m_defaultDepthStencil->createDepthStencilState(*m_gfxDevice);
  m_defaultDepthStencil->setDepthStencilState(*m_gfxDevice);

  //Create Depth Stencil view from depth stencil
  m_depthStencilView = m_gfxDevice->createDepthStencilViewInstance();
  m_depthStencilView->createDepthStencilView(*m_gfxAPIInstance->getDevice(), *m_defaultDepthStencil);

  //Create a texture manager
  m_textureManager = m_gfxDevice->createTextureInstance();

  //Create rasterizer state
  m_rasterizerState = m_gfxDevice->creatreRasterizerStateInstance();
  m_rasterizerState->createRasterizerState(*m_gfxAPIInstance->getDevice(),
                                           FILL_MODE::kFILL_SOLID,
                                           CULL_MODE::kCULL_BACK);
  //Create default sampler state
  m_defaultSampler = m_gfxDevice->createSamplerStateInstance();
  m_defaultSampler->createSamplerState(*m_gfxAPIInstance->getDevice(),
                                       SAMPLER_FILTER::E::kFILTER_ANISOTROPIC,
                                       TEXTURE_ADDRESS_MODE::E::kTEXTURE_ADDRESS_WRAP);

  //Create compute sampler state to calculate the environment cube map
  m_computeSampler = m_gfxDevice->createSamplerStateInstance();
  m_computeSampler->createSamplerState(*m_gfxAPIInstance->getDevice(),
                                       SAMPLER_FILTER::kFILTER_COMPARISON_MIN_MAG_MIP_LINEAR,
                                       TEXTURE_ADDRESS_MODE::kTEXTURE_ADDRESS_WRAP);
  
  m_mainCB = m_gfxDevice->createConstantBufferInstance();
  m_shadingCB = m_gfxDevice->createConstantBufferInstanceVec3();

  //Startup Camera manager module
  CameraManager::StartUp<CameraManager>();
  
  //Start up Scene manager module
  SceneManager::StartUp<SceneManager>();
  
  //Start up UI Module
  if(!UIManager::instance().initUI(reinterpret_cast<void*>(m_window->m_hWnd),
                                   m_gfxDevice->getDevice(),
                                   m_gfxDevice->getContext())) {
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
  localRenderSetup();
  while (m_window->isOpen())
  {
    //m_renderPipeInstance->Setup();
    m_window->handleMSG(static_cast<void*>(&msg), *m_inputManager);
    update();
    
    //m_renderPipeInstance->render();
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
  m_backBufferRTV->setRenderTarget(*m_gfxDevice, *m_depthStencilView);

  m_backBufferRTV->clearRenderTarget(m_gfxDevice, ClearColor);

  m_depthStencilView->clearDSV(*m_gfxDevice);


  m_localVS->setVertexShader(*m_gfxDevice);
  m_localPS->setPixelShader(*m_gfxDevice);
  m_localLayout->setInputLayout(*m_gfxDevice);


  m_mainCB->setConstData(0, m_world);
  m_mainCB->setConstData(1, CameraManager::instance().getActiveCamera()->GetViewMatrix());
  m_mainCB->updateSubResources(*m_gfxDevice);

  m_lightCB->setConstData(0, CameraManager::instance().getActiveCamera()->getPosition());
  m_lightCB->updateSubResources(*m_gfxDevice);

  for (uint32 i = 0; i < m_modelsVector.size(); ++i) {
    m_modelsVector[i]->Draw(m_gfxDevice);
  }
  UIManager::instance().renderUI();

  //TODO: ActiveRederPipeline.render();

  m_gfxDevice->PresentSwapChain();

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
WinApp::updateCamera(Camera* newCam)
{
  CameraManager::instance().setActiveCamera(newCam);
}

bool WinApp::loadModel()
{
  String filetypes("FBX Files\0*.fbx\0OBJ Files\0*.obj\0Any File\0*.*\0");
  String filename = EngineUtility::loadFile(&filetypes[0], m_window->gethWnd());

  if (filename != "") {

    int strPos = filename.find_last_of('\\');
    String name = filename.substr(strPos + 1);

    GameObject* newGO = SceneManager::instance().createGameObject(name);
    newGO->addComponent<Model>(newGO);
    newGO->getComponent<Model>().loadModelFromFile(filename, *m_gfxDevice);
    SceneManager::instance().getActiveScene()->addNewNode(newGO);

    m_modelsVector.push_back(make_shared<Model>(newGO->getComponent<Model>()));
  }

  return true;
}

bool 
WinApp::loadTexture()
{
  String filetypes("PNG Files\0*.png\0JPG Files\0*.jpg\0Any File\0*.*\0");
  
  String filename = EngineUtility::loadFile(filetypes, m_window->gethWnd());
  //m_textureManager->createTexture2D();
  return true;
}

//Moved to resource lodaing
//String 
//WinApp::loadFile(String filetypes)
//{
//  
//}

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

void WinApp::localRenderInit()
{
  m_PBRVS = m_gfxDevice->createVertexShaderInstance();
  m_PBRPS = m_gfxDevice->createPixelShaderInstance();
  m_pbrInputLayout = m_gfxDevice->createInputLayoutInstance();

  m_skyboxVS = m_gfxDevice->createVertexShaderInstance();
  m_skyboxPS = m_gfxDevice->createPixelShaderInstance();
  m_skyboxInputLayout = m_gfxDevice->createInputLayoutInstance();
  
  m_toneMapVS = m_gfxDevice->createVertexShaderInstance();
  m_toneMapPS = m_gfxDevice->createPixelShaderInstance();
  
  m_equirect2CubeCS = m_gfxDevice->createComputeShaderInstance();
  m_computeSampler = m_gfxDevice->createSamplerStateInstance();
  m_computeSampler = m_gfxDevice->createSamplerStateInstance();
  m_computeSampler->createSamplerState(*m_gfxAPIInstance->getDevice(),
                                       SAMPLER_FILTER::E::kFILTER_MIN_MAG_MIP_LINEAR,
                                       TEXTURE_ADDRESS_MODE::E::kTEXTURE_ADDRESS_WRAP);
}

void 
WinApp::localRenderSetup()
{
  //Setting up camera
  m_camManager->getActiveCamera()->setFOV(kraMath::DEG2RAD(90.0f));
  m_camManager->getActiveCamera()->setNearPlane(0.01f);
  m_camManager->getActiveCamera()->setFarPlane(10000.0f);
  
  //Setting up shaders

  m_PBRVS->compileVertexShader(L"resources/Shaders/PBR.hlsl", "VS");
  m_PBRVS->createVertexShader(*m_gfxAPIInstance->getDevice());

  m_PBRPS->compilePixelShader(L"resources/Shaders/PBR.hlsl", "PS");
  m_PBRPS->createPixelShader(*m_gfxAPIInstance->getDevice());

  m_skyboxVS->compileVertexShader(L"resources/Shaders/skyboxShader.hlsl", "VS");
  m_skyboxVS->createVertexShader(*m_gfxAPIInstance->getDevice());

  m_skyboxPS->compilePixelShader(L"resources/Shaders/skyboxShader.hlsl", "PS");
  m_skyboxPS->createPixelShader(*m_gfxAPIInstance->getDevice());

  m_toneMapVS->compileVertexShader(L"resources/Shaders/toneMappingShader.hlsl", "VS");
  m_toneMapVS->createVertexShader(*m_gfxAPIInstance->getDevice());

  m_toneMapPS->compilePixelShader(L"resources/Shaders/toneMappingShader.hlsl", "PS");
  m_toneMapPS->createPixelShader(*m_gfxAPIInstance->getDevice());

  //Seting input layout
  m_pbrInputLayout = m_gfxAPIInstance->getDevice()->createInputLayoutInstance();
  m_pbrInputLayout->createInputLayout(*m_gfxDevice, *m_PBRVS);

  m_skyboxInputLayout = m_gfxAPIInstance->getDevice()->createInputLayoutInstance();
  m_skyboxInputLayout->createInputLayout(*m_gfxDevice, *m_skyboxVS);

  //This one is specially disgusting
  GameObject* skyGO = SceneManager::instance().createGameObject("Skybox");
  skyGO->addComponent<Model>(skyGO);
  skyGO->getComponent<Model>().loadModelFromFile("resources/Models/skybox.obj",
                                                 *m_gfxDevice);
  SceneManager::instance().getActiveScene()->addNewNode(skyGO);
  m_modelsVector.push_back(make_shared<Model>(skyGO->getComponent<Model>()));

  m_equirect2CubeCS->compileComputeShader(L"resources/Shaders/equirect2Cube.hlsl", "CS");
  ShrdPtr<Texture> enviroTexture = m_gfxDevice->createTextureInstance();
  enviroTexture->createTexture2DFromFile(*m_gfxDevice,
                                         "/resources/Textures/HDRenvironment.hdr", 
                                         GFX_FORMAT::E::kFORMAT_R32G32B32A32_FLOAT,
                                         GFX_USAGE::E::kUSAGE_DYNAMIC,
                                         CPU_USAGE::E::kCPU_ACCESS_WRITE);
  enviroTexture->setTextureComputeShaderResource(m_gfxDevice, 0, 1);
  m_computeSampler->setComputeSamplerState(*m_gfxDevice);
  



  //Set Primitive Topology
  m_gfxAPIInstance->getDevice()->setPrimitiveTopology();
  m_defaultSampler->setSamplerState(*m_gfxAPIInstance->getDevice());

  //Setting rendering matrices
  m_world.identity();
  m_mainCB->add(m_world);

  m_activeCam = CameraManager::instance().getActiveCamera();

  CameraManager::instance().getActiveCamera()->setUp(Vector3(0.0f, 1.0f, 0.0f));
  CameraManager::instance().getActiveCamera()->setFront(Vector3(0.0f, 0.0f, -1.0f));
  CameraManager::instance().getActiveCamera()->setRight(Vector3(1.0f, 0.0f, 0.0f));
  CameraManager::instance().getActiveCamera()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
  CameraManager::instance().getActiveCamera()->SetObjecive(Vector3(0.0f, 0.0f, 1.0f));

  CameraManager::instance().getActiveCamera()->createViewMat();
  m_mainCB->add(CameraManager::instance().getActiveCamera()->GetViewMatrix());


  m_projection.MatrixPerspectiveFOV(CameraManager::instance().getActiveCamera()->getFOV(),
                                    static_cast<float>(m_gfxAPIInstance->getDevice()->getWidth()),
                                    static_cast<float>(m_gfxAPIInstance->getDevice()->getHeight()),
                                    CameraManager::instance().getActiveCamera()->getNearPlane(),
                                    CameraManager::instance().getActiveCamera()->getFarPlane());

  m_mainCB->add(m_projection);
  m_mainCB->createConstantBuffer(*m_gfxAPIInstance->getDevice());
  m_mainCB->updateSubResources(*m_gfxAPIInstance->getDevice());

  Vector3 lightPos = Vector3(100.0f, 0.0f, 100.0f);
  m_lightCB->add(Vector4(lightPos, 1.0f));
  m_lightCB->createConstantBuffer(*m_gfxAPIInstance->getDevice());
  m_lightCB->updateSubResources(*m_gfxAPIInstance->getDevice());
  
}

