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

  m_window = new Win32Window(1600, 1024, name, Vector2(0, 0));
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
    std::cout << "Could not find specified renderer DLL. Error: " << err << std::endl;
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

  m_gfxDevice.reset(m_gfxAPIInstance->getDevice());

  //Create The main Render target for Backbuffer
  m_backBufferRTV = m_gfxDevice->createRenderTargetInsttance();
  m_backBufferRTV->createRenderTargetView(*m_gfxDevice);
  m_backBufferRTV->setRenderTarget(*m_gfxDevice, 1);

  //Create and set the viewport
  m_viewport = m_gfxDevice->createViewportInstance();
  m_viewport->createViewport(m_gfxDevice->getWidth(), m_gfxAPIInstance->getDevice()->getHeight(), 0.0f, 0.0f);
  m_viewport->setViewport(*m_gfxDevice);

  // Create Depth stencil
  m_defaultDepthStencil = m_gfxDevice->createDepthStencilInstance();
  //m_defaultDepthStencil->setDepthStencil(*m_gfxDevice, m_gfxAPIInstance->getDevice()->getHeight(), m_gfxAPIInstance->getDevice()->getWidth());
  m_defaultDepthStencil->createDepthStencilState(*m_gfxDevice, true, DEPTH_WRITE_MASK::E::kDEPTH_WRITE_MASK_ALL, COMPARISON_FUNCTION::E::kCOMPARISON_LESS_EQUAL);
  m_defaultDepthStencil->setDepthStencilState(*m_gfxDevice);
  
  // Create Skybox Depth stencil
  m_skyboxDepthStencil = m_gfxDevice->createDepthStencilInstance();
  m_skyboxDepthStencil->createDepthStencilState(*m_gfxDevice, false, DEPTH_WRITE_MASK::E::kDEPTH_WRITE_MASK_ZERO, COMPARISON_FUNCTION::E::kCOMPARISON_LESS_EQUAL);
  
  m_defaultDepthStencil->setDepthStencilState(*m_gfxDevice);

  //Create rasterizer state
  m_rasterizerState = m_gfxDevice->creatreRasterizerStateInstance();
  m_rasterizerState->createRasterizerState(*m_gfxAPIInstance->getDevice(),
                                           true,
                                           FILL_MODE::E::kFILL_SOLID,
                                           CULL_MODE::E::kCULL_BACK);

  //Create default sampler state
  m_defaultSampler = m_gfxDevice->createSamplerStateInstance();
  m_defaultSampler->createSamplerState(*m_gfxAPIInstance->getDevice(),
                                       SAMPLER_FILTER::E::kFILTER_ANISOTROPIC,
                                       TEXTURE_ADDRESS_MODE::E::kTEXTURE_ADDRESS_WRAP,
                                       COMPARISON_FUNCTION::E::kCOMPARISON_NEVER);

  
  m_mainCB = m_gfxDevice->createConstantBufferInstance();
  m_shadingCB = m_gfxDevice->createConstantBufferInstanceVec4();

  //Startup Camera manager module
  CameraManager::StartUp<CameraManager>();
  
  //Start up Scene manager module
  SceneManager::StartUp<SceneManager>();
  
  m_sceneManager.reset(SceneManager::instancePtr());

  //Start up UI Module
  if(!UIManager::instance().initUI(reinterpret_cast<void*>(m_window->m_hWnd),
                                   m_gfxDevice->getDevice(),
                                   m_gfxDevice->getContext())) {
    Log("Couldn't initiate UI");
  }

  //Setting rendering matrices
  m_world.identity();
  m_mainCB->add(m_world);

  m_activeCam = CameraManager::instance().getActiveCamera();

  //Setting up camera
  m_activeCam->setUp(Vector3(0.0f, 1.0f, 0.0f));
  m_activeCam->setRight(Vector3(1.0f, 0.0f, 0.0f));
  m_activeCam->setFront(Vector3(0.0f, 0.0f, 1.0f));
  m_activeCam->SetPosition(Vector3(0.0f, 1.0f, -180.0f));
  m_activeCam->SetObjecive(Vector3(0.0f, 0.0f, 1.0f));

  m_activeCam->setFOV(kraMath::DEG2RAD(90.0f));
  m_activeCam->setNearPlane(0.01f);
  m_activeCam->setFarPlane(5000.0f);

   CameraManager::instance().getActiveCamera()->createViewMat();
  Matrix4 viewMat = CameraManager::instance().getActiveCamera()->GetViewMatrix();
  
 
  m_projection.MatrixPerspectiveFOVLH(CameraManager::instance().getActiveCamera()->getFOV(),
                                    static_cast<float>(m_window->getWidth()),
                                    static_cast<float>(m_window->getHeight()),
                                    CameraManager::instance().getActiveCamera()->getNearPlane(),
                                    CameraManager::instance().getActiveCamera()->getFarPlane());
  m_skyprojection = m_projection * viewMat;
  
  viewMat.transpose();
  m_mainCB->add(viewMat);

  m_projection.transpose();
  m_mainCB->add(m_projection);
  
  m_skyprojection.transpose();
  m_mainCB->add(m_skyprojection);

  m_mainCB->createConstantBuffer(*m_gfxAPIInstance->getDevice());
  //m_mainCB->updateSubResources(*m_gfxAPIInstance->getDevice());

  m_shadingCB->add(Vector4(m_activeCam->getPosition(), 1.0f));
  m_shadingCB->add(Vector4(-1.0f, 0.0f, 0.0f, 0.0f));
  m_shadingCB->add(Vector4(1.0f, 1.0f, 1.0f, 0.0f));
  m_shadingCB->createConstantBuffer(*m_gfxAPIInstance->getDevice());
  //m_shadingCB->updateSubResources(*m_gfxAPIInstance->getDevice());

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
  UIManager::instance().updateUI(m_sceneManager->getActiveScene());
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
  const Matrix4 viewRotationMat = Matrix4::eulerAngleXY(kraMath::DEG2RAD(m_activeCam->getPitch()),
                                                        kraMath::DEG2RAD(m_activeCam->getYaw()));

  //m_mainCB->clear();
  
  
  // Setting world matrix
//  m_mainCB->add(m_world);


  //Setting view matrix
  Matrix4 viewMat = m_activeCam->GetViewMatrix();

  //Setting projection matrix
  m_projection.MatrixPerspectiveFOVLH(m_activeCam->getFOV(),
                                    static_cast<float>(m_window->getWidth()),
                                    static_cast<float>(m_window->getHeight()),
                                    m_activeCam->getNearPlane(),
                                    m_activeCam->getFarPlane());

  m_skyprojection = m_projection * viewMat;
  
  viewMat.transpose();
  m_mainCB->setConstData(1, viewMat);
  
  m_projection.transpose();
  m_mainCB->setConstData(2, m_projection);

  m_skyprojection.transpose();
  m_mainCB->setConstData(3, m_skyprojection);
  m_mainCB->updateSubResources(*m_gfxDevice);

  m_shadingCB->clear();
  m_shadingCB->add(Vector4(m_activeCam->getPosition(), 1.0f));
  m_shadingCB->add(Vector4(-1.0f, 0.0f, 0.0f, 1.0f));
  m_shadingCB->add(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
  m_shadingCB->updateSubResources(*m_gfxDevice);

  //WHAT?
  srcFB->m_frameRTV->setRenderTarget(*m_gfxDevice, *srcFB->m_frameDSV);
  srcFB->m_frameDSV->clearDSV(*m_gfxDevice);
  srcFB->m_frameRTV->clearRenderTarget(*m_gfxDevice, ClearColor);

  m_gfxAPIInstance->getDevice()->setPrimitiveTopology();
  m_mainCB->setVertexConstantBuffer(*m_gfxDevice, 0, 1);
  m_shadingCB->setPixelConstantBuffer(*m_gfxDevice, 0, 1);

  m_rasterizerState->setRasterizerState(*m_gfxDevice);

  

  //Render Skybox
  if (m_skyBoxGO != nullptr) {
    drawSkybox();
  }

  //Render PBR Models
  drawPBRModels();

  //Capture this frame frame
  m_gfxDevice->resolveSubreresource(*srcFB->m_colorTex, *destinationFB->m_colorTex);
  
  m_backBufferRTV->setRenderTarget(*m_gfxDevice, 1);



  //Tone mapping pass
  toneMapPasss();

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

float 
WinApp::getWindowWidth()
{
  return m_window->getWidth();
}

float 
WinApp::getWindowHeight()
{
  return m_window->getHeight();
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

bool 
WinApp::loadModel()
{
  String filetypes("FBX Files\0*.fbx\0OBJ Files\0*.obj\0Any File\0*.*\0");
  String filename = EngineUtility::loadFile(&filetypes[0], m_window->gethWnd());
  if (filename != "") {

    uint32 firstPos = filename.find_last_of('\\');
    uint32 lastPos = filename.find_last_of('.');
    String name = filename.substr(firstPos + 1, lastPos - firstPos - 1);

    //Empty GameObject that holds all the meshes.
    ShrdPtr<GameObject> newModelGO = m_sceneManager->createGameObject(name);
    Model newModel(newModelGO);
    m_sceneManager->getActiveScene()->addNewNode(newModelGO);

    newModel.loadModelFromFile(filename, *m_gfxDevice, m_sceneManager);
    
    for (auto& meshGO : newModel.getMeshVec()) {       
      newModelGO->addChild(meshGO); 
      setGoldMaterial(meshGO->getComponent<Mesh>());
      m_modelsVector.push_back(meshGO);

    }
  }
  return true;
}

bool 
WinApp::loadTexture()
{
  String filetypes("PNG Files\0*.png\0JPG Files\0*.jpg\0Any File\0*.*\0");
  
  String filename = EngineUtility::loadFile(filetypes, m_window->gethWnd());
  ShrdPtr<Texture> newTex = m_gfxDevice->createTextureInstance();

  newTex->createTexture2DFromFile(*m_gfxDevice,
                                  filename,
                                  GFX_FORMAT::E::kFORMAT_R8G8B8A8_UNORM,
                                  GFX_USAGE::E::kUSAGE_DEFAULT,
                                  CPU_USAGE::E::kCPU_ACCESS_WRITE);
  return true;
}

void 
WinApp::CleanupDevice()
{
  //do cleanup
}

void 
WinApp::localRenderSetup()
{
  //Creating instances of classes
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
  m_equirectHDRTexture = m_gfxDevice->createTextureInstance();
  m_enviroMap = m_gfxDevice->createTextureInstance();
  m_pbrInputLayout = m_gfxDevice->createInputLayoutInstance();
  spBRDFshader = m_gfxDevice->createComputeShaderInstance();
  m_skyboxInputLayout = m_gfxDevice->createInputLayoutInstance();
  m_BRDFLUT = m_gfxDevice->createTextureInstance();
  m_cubeUnfiltered = m_gfxDevice->createTextureInstance();
  m_BRDFSampler = m_gfxDevice->createSamplerStateInstance();
  srcFB = m_gfxDevice->createFrameBufferInstance();
  destinationFB = m_gfxDevice->createFrameBufferInstance();
  m_specMapCB = m_gfxDevice->createConstantBufferInstanceFloat();
  m_specMapCS = m_gfxDevice->createComputeShaderInstance();
  irradianceShader = m_gfxDevice->createComputeShaderInstance();
  m_irradMap = m_gfxDevice->createTextureInstance();

  uint32 samples = m_gfxDevice->checkMaxSupportedMSAALevel();

  if (!srcFB->initFramebuffer(m_gfxDevice->getWidth(),
                              m_gfxDevice->getHeight(),
                              samples,
                              GFX_FORMAT::E::kFORMAT_R16G16B16A16_FLOAT,
                              GFX_FORMAT::E::kFORMAT_D24_UNORM_S8_UINT)) {

    throw std::exception("Failed to initialize FrameBuffer");
  }

  if (samples > 1) {
    
    destinationFB->initFramebuffer(m_gfxDevice->getWidth(),
                                   m_gfxDevice->getHeight(),
                                   1,
                                   GFX_FORMAT::E::kFORMAT_R16G16B16A16_FLOAT,
                                   GFX_FORMAT::E::kFORMAT_UNKNOWN);
  }
  else {
    destinationFB = srcFB;
  }

  //m_mainCB->createConstantBuffer(*m_gfxDevice);

  //Compiling up shaders
  m_PBRVS->compileVertexShader(L"resources/Shaders/PBR.hlsl", "VS");
  m_PBRVS->createVertexShader(*m_gfxDevice);

  m_PBRPS->compilePixelShader(L"resources/Shaders/PBR.hlsl", "PS");
  m_PBRPS->createPixelShader(*m_gfxDevice);

  m_skyboxVS->compileVertexShader(L"resources/Shaders/skyboxShader.hlsl", "VS");
  m_skyboxVS->createVertexShader(*m_gfxDevice);

  m_skyboxPS->compilePixelShader(L"resources/Shaders/skyboxShader.hlsl", "PS");
  m_skyboxPS->createPixelShader(*m_gfxDevice);


  m_toneMapVS->compileVertexShader(L"resources/Shaders/toneMappingShader.hlsl", "VS");
  m_toneMapVS->createVertexShader(*m_gfxDevice);

  m_toneMapPS->compilePixelShader(L"resources/Shaders/toneMappingShader.hlsl", "PS");
  m_toneMapPS->createPixelShader(*m_gfxDevice);

  //setting input layout
  m_pbrInputLayout->createInputLayout(*m_gfxDevice, *m_PBRVS);
  m_skyboxInputLayout->createInputLayout(*m_gfxDevice, *m_skyboxVS);

  //This one is specially disgusting
  //m_skyBoxGO = m_sceneManager->createGameObject("Skybox");
  Model* skyModel = new Model(m_skyBoxGO);
  if (skyModel->loadModelFromFile("resources/Models/Skybox3.fbx",
                                 *m_gfxDevice, m_sceneManager)) {
    m_skyBoxGO = skyModel->getMeshVec()[0];
    m_skyBoxGO->getComponent<Material>().setAlbedoTex(*m_gfxDevice, m_enviroMap);

  }
  else {
    MessageBox(m_window->gethWnd(), "Skybox model couldn't be loaded", "ERROR", MB_OK | MB_ICONWARNING);
    m_skyBoxGO = nullptr;
  }

  setUpIBL();
    
  setUpIrradianceMap();

  setUpBRDF();

}

void 
WinApp::setUpIBL()
{
 
  //Creating unfiltered cube texture
  m_cubeUnfiltered->createCubeTexture(*m_gfxDevice,
                                      1024,
                                      1024,
                                      GFX_FORMAT::E::kFORMAT_R16G16B16A16_FLOAT,
                                      GFX_USAGE::E::kUSAGE_DEFAULT,
                                      0U);
  m_cubeUnfiltered->createTextureUAV(*m_gfxDevice, 0);

  //Compiling shader to convert an equirectangular projection image into a cubemap 
  m_equirect2CubeCS->compileComputeShader(L"resources/Shaders/equirect2Cube.hlsl", "main");
  m_equirect2CubeCS->createComputeShader(*m_gfxDevice);

  //Loading the equirectangular projection texture
  m_equirectHDRTexture->createTexture2DFromFile(*m_gfxDevice,
                                                "resources/Textures/HDR/circus.hdr",
                                                GFX_FORMAT::E::kFORMAT_R32G32B32A32_FLOAT,
                                                GFX_USAGE::E::kUSAGE_DEFAULT,
                                                CPU_USAGE::E::kCPU_ACCESS_WRITE,
                                                4,
                                                1);
  m_computeSampler->createSamplerState(*m_gfxAPIInstance->getDevice(),
                                       SAMPLER_FILTER::E::kFILTER_MIN_MAG_MIP_LINEAR,
                                       TEXTURE_ADDRESS_MODE::E::kTEXTURE_ADDRESS_WRAP,
                                       COMPARISON_FUNCTION::E::kCOMPARISON_NEVER);
  
  //Setting up both textures to be used by the shader
  m_equirectHDRTexture->setTextureComputeShaderResource(*m_gfxDevice, 0, 1);
  m_cubeUnfiltered->setTextureUnorderedAccesVews(*m_gfxDevice, 0, 1);
  m_computeSampler->setComputeSamplerState(*m_gfxDevice);
  m_equirect2CubeCS->setComputeShader(*m_gfxDevice);
  m_equirect2CubeCS->dispatchCS(*m_gfxDevice,
                                m_cubeUnfiltered->getWidth() / 32,
                                m_cubeUnfiltered->getHeight() / 32,
                                6);
  m_cubeUnfiltered->setComputeNullUAV(*m_gfxDevice);


  m_gfxDevice->generateMips(m_cubeUnfiltered);

  //Compiling shader to compute the specular env map 
  m_specMapCS->compileComputeShader(L"resources/Shaders/specMapShader.hlsl", "main");
  m_specMapCS->createComputeShader(*m_gfxDevice);

  m_specMapCB->createConstantBuffer(*m_gfxDevice);

  m_enviroMap->createCubeTexture(*m_gfxDevice,
                                 1024,
                                 1024,
                                 GFX_FORMAT::E::kFORMAT_R16G16B16A16_FLOAT,
                                 GFX_USAGE::E::kUSAGE_DEFAULT);

  for (uint32 arraySlice = 0; arraySlice < 6; ++arraySlice) {
    //This is the same as calling D3D11CalcSubresource. But I was too lazy to implement the function...
    /*To calculate the index of a subresource, you have to do: MipSlice + (ArraySlice * MipLevels).
    Here we're calculating the most detailed level, so mipslice = 0.*/
    const uint32 subResourceIndex = arraySlice * m_enviroMap->getLevels();
    m_gfxDevice->copySubresourceRegion(m_enviroMap, 
                                       subResourceIndex,
                                       0,
                                       0,
                                       0,
                                       m_cubeUnfiltered,
                                       subResourceIndex,
                                       nullptr);
  }

  m_cubeUnfiltered->setTextureComputeShaderResource(*m_gfxDevice, 0, 1);
  m_computeSampler->setComputeSamplerState(*m_gfxDevice);
  m_specMapCS->setComputeShader(*m_gfxDevice);

  //Filtering the rest of the mip levels
  const float deltaRoughness = 1.0f / kraMath::fmax(m_enviroMap->getLevels() - 1.0f, 1.0f);
  float roughness;

  for (uint32 level = 1, size = 512; level < m_enviroMap->getLevels(); ++level, size/=2) {
    
    uint32 numGroups = kraMath::fmax<uint32>(1, size / 32);
    m_specMapCB->clear();
    m_enviroMap->createTextureUAV(*m_gfxDevice, level);
    
    roughness = level * deltaRoughness;
    m_specMapCB->add(roughness);

    m_specMapCB->updateSubResources(*m_gfxDevice);
    m_specMapCB->setComputeConstantBuffer(*m_gfxDevice, 0, 1);

    m_enviroMap->setTextureUnorderedAccesVews(*m_gfxDevice, 0, 1);
    m_specMapCS->dispatchCS(*m_gfxDevice, numGroups, numGroups, 6);
  }

  m_specMapCB->setComputeNullConstantBuffer(*m_gfxDevice);
  m_enviroMap->setComputeNullUAV(*m_gfxDevice);

}

void WinApp::setUpIrradianceMap()
{  
  irradianceShader->compileComputeShader(L"resources/Shaders/irradianceMapShader.hlsl", "main");
  irradianceShader->createComputeShader(*m_gfxDevice);

  m_irradMap->createCubeTexture(*m_gfxDevice,
                                32, 32,
                                GFX_FORMAT::E::kFORMAT_R16G16B16A16_FLOAT,
                                GFX_USAGE::E::kUSAGE_DEFAULT,
                                1);

  m_irradMap->createTextureUAV(*m_gfxDevice, 0);
  m_enviroMap->setTextureComputeShaderResource(*m_gfxDevice, 0, 1);
  m_computeSampler->setComputeSamplerState(*m_gfxDevice);
  m_irradMap->setTextureUnorderedAccesVews(*m_gfxDevice, 0, 1);
  irradianceShader->setComputeShader(*m_gfxDevice);
  irradianceShader->dispatchCS(*m_gfxDevice,
                               m_irradMap->getWidth() / 32,
                               m_irradMap->getHeight() / 32,
                               6);
  m_irradMap->setComputeNullUAV(*m_gfxDevice);

  m_skyBoxGO->getComponent<Mesh>().setTexture(*m_gfxDevice, TEXTURE_TYPE::E::ALBEDO, m_enviroMap);

}

void WinApp::setUpBRDF()
{
  //Calculating Cook-Torrance's BRFD model
  spBRDFshader->compileComputeShader(L"resources/Shaders/specBRDF.hlsl", "main");
  spBRDFshader->createComputeShader(*m_gfxDevice);

  m_BRDFLUT->createTexture2DFromFile(*m_gfxDevice,
                                     "resources/Textures/brfdLUT.png",
                                     GFX_FORMAT::E::kFORMAT_R16G16_FLOAT,
                                     GFX_USAGE::E::kUSAGE_DEFAULT,
                                     CPU_USAGE::E::kCPU_ACCESS_WRITE,
                                     4,
                                     1);

  m_BRDFSampler->createSamplerState(*m_gfxDevice,
                                    SAMPLER_FILTER::E::kFILTER_MIN_MAG_MIP_LINEAR,
                                    TEXTURE_ADDRESS_MODE::E::kTEXTURE_ADDRESS_CLAMP,
                                    COMPARISON_FUNCTION::E::kCOMPARISON_NEVER);

  m_BRDFLUT->createTextureUAV(*m_gfxDevice, 0);
  m_BRDFLUT->setTextureUnorderedAccesVews(*m_gfxDevice, 0, 1);
  spBRDFshader->setComputeShader(*m_gfxDevice);
  spBRDFshader->dispatchCS(*m_gfxDevice, m_BRDFLUT->getWidth() / 32, m_BRDFLUT->getHeight() / 32, 1);
  m_BRDFLUT->setComputeNullUAV(*m_gfxDevice);
}

void 
WinApp::drawSkybox()
{
  m_skyboxInputLayout->setInputLayout(*m_gfxDevice);
  m_skyboxVS->setVertexShader(*m_gfxDevice);
  m_skyboxPS->setPixelShader(*m_gfxDevice);
  m_defaultSampler->setSamplerState(*m_gfxDevice, 0, 1);
  m_skyboxDepthStencil->setDepthStencilState(*m_gfxDevice);
  m_skyBoxGO->getComponent<Mesh>().setIndexBuffer(*m_gfxDevice);
  m_skyBoxGO->getComponent<Mesh>().setVertexBuffer(*m_gfxDevice);
  m_skyBoxGO->getComponent<Mesh>().setTexShaderResources(*m_gfxDevice);
  m_skyBoxGO->getComponent<Mesh>().DrawMesh(*m_gfxDevice);

}

void 
WinApp::drawPBRModels()
{
  m_pbrInputLayout->setInputLayout(*m_gfxDevice);
  m_PBRVS->setVertexShader(*m_gfxDevice);
  m_PBRPS->setPixelShader(*m_gfxDevice);
  m_defaultSampler->setSamplerState(*m_gfxDevice, 0, 1);
  m_BRDFSampler->setSamplerState(*m_gfxDevice, 1, 1);
  m_defaultDepthStencil->setDepthStencilState(*m_gfxDevice);

  m_enviroMap->setTextureShaderResource(*m_gfxDevice, 4, 1);
  m_irradMap->setTextureShaderResource(*m_gfxDevice, 5, 1);
  m_BRDFLUT->setTextureShaderResource(*m_gfxDevice, 6, 1);

  for (uint32 i = 0; i < m_modelsVector.size(); ++i) {
    
    Matrix4 movelMatrix = m_modelsVector[i]->getWorldMatrix();
    movelMatrix.transpose();
    m_mainCB->setConstData(0, movelMatrix);
    m_mainCB->updateSubResources(*m_gfxDevice);

    m_modelsVector[i]->getComponent<Mesh>().setIndexBuffer(*m_gfxDevice);
    m_modelsVector[i]->getComponent<Mesh>().setVertexBuffer(*m_gfxDevice);
    m_modelsVector[i]->getComponent<Mesh>().setTexShaderResources(*m_gfxDevice);
    m_modelsVector[i]->getComponent<Mesh>().DrawMesh(*m_gfxDevice);
    
  }
}

void
WinApp::toneMapPasss()
{

  m_backBufferRTV->setRenderTarget(*m_gfxDevice, 1);
  m_skyboxInputLayout->setNullInputLayout(*m_gfxDevice);
  m_toneMapVS->setVertexShader(*m_gfxDevice);
  m_toneMapPS->setPixelShader(*m_gfxDevice);
  destinationFB->m_colorTex->setTextureShaderResource(*m_gfxDevice, 0, 1);
  m_computeSampler->setComputeSamplerState(*m_gfxDevice);
  m_gfxDevice->Draw(3, 0);
}

void
WinApp::setGoldMaterial(Mesh& meshGO) {
 
  Material goldMaterial(meshGO.getOwner());

  ShrdPtr<Texture> albedo = m_gfxDevice->createTextureInstance();
  ShrdPtr<Texture> normal = m_gfxDevice->createTextureInstance();
  ShrdPtr<Texture> metal = m_gfxDevice->createTextureInstance();
  ShrdPtr<Texture> rough = m_gfxDevice->createTextureInstance();


  albedo->createTexture2DFromFile(*m_gfxDevice,
                                  "resources/Textures/pbr/gold/gold_albedo2.png",
                                  GFX_FORMAT::E::kFORMAT_R8G8B8A8_UNORM_SRGB,
                                  GFX_USAGE::E::kUSAGE_DEFAULT,
                                  CPU_USAGE::E::kCPU_ACCESS_WRITE);

  normal->createTexture2DFromFile(*m_gfxDevice,
                                  "resources/Textures/pbr/gold/gold_normal.png",
                                  GFX_FORMAT::E::kFORMAT_R8G8B8A8_UNORM,
                                  GFX_USAGE::E::kUSAGE_DEFAULT,
                                  CPU_USAGE::E::kCPU_ACCESS_WRITE);

  metal->createTexture2DFromFile(*m_gfxDevice,
                                 "resources/Textures/pbr/gold/gold_metalness.png",
                                 GFX_FORMAT::E::kFORMAT_R8_UNORM,
                                 GFX_USAGE::E::kUSAGE_DEFAULT,
                                 CPU_USAGE::E::kCPU_ACCESS_WRITE,
                                 1);

  rough->createTexture2DFromFile(*m_gfxDevice,
                                 "resources/Textures/pbr/gold/gold_roughness.png",
                                 GFX_FORMAT::E::kFORMAT_R8_UNORM,
                                 GFX_USAGE::E::kUSAGE_DEFAULT,
                                 CPU_USAGE::E::kCPU_ACCESS_WRITE,
                                 1);


  goldMaterial.setAlbedoTex(*m_gfxDevice, albedo);
  goldMaterial.setNormalTex(*m_gfxDevice, normal);
  goldMaterial.setMetalTex(*m_gfxDevice, metal);
  goldMaterial.setRoughnessTex(*m_gfxDevice, rough);

  meshGO.setMeshMaterial(*m_gfxDevice, &goldMaterial);
}

