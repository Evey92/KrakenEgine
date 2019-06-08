#include <windows.h>
#include <string>
#include "kraApp.h"

void
App::run() {

}

  bool
  App::startUp(void* m_hWnd) {
    typedef GraphicsAPI*(*initFunc)();
    typedef InputAPI*(*initInptFunc)();
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

    initFunc initAPIFunc = (initFunc)GetProcAddress(GFXDLL, "createGraphicsAPI");
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

    gfxAPIInstance = initAPIFunc();
    if (!gfxAPIInstance) {
      MessageBox(NULL, "Failed to create Graphics API", "Error", MB_OK);

      return false;
    }

    inputAPIInstance = initInputAPIFunc();
    if (!inputAPIInstance) {
      MessageBox(NULL, "Failed to create Input API", "Error", MB_OK);

      return false;
    }

    m_device = gfxAPIInstance->initializeAPI(reinterpret_cast<void*>(m_hWnd));
    if (!m_device)
    {
      MessageBox(NULL, "Failed to create Initialize API Device", "Error", MB_OK);
      return false;
    }

    m_inputManager = inputAPIInstance->initializeAPI(m_device->getWidth(), m_device->getHeight());
    if (!m_device)
    {
      MessageBox(NULL, "Failed to create Initialize Input Manager", "Error", MB_OK);
      return false;
    }

    m_renderTargetView = m_device->createRenderTargetInsttance();
    if (!m_renderTargetView)
    {
      MessageBox(NULL, "Failed to create Render Target", "Error", MB_OK);
      return false;
    }

    m_normalTargetView = m_device->createRenderTargetInsttance();
    if (!m_renderTargetView)
    {
      MessageBox(NULL, "Failed to create Render Target", "Error", MB_OK);
      return false;
    }

    m_depthStencil = m_device->createDepthStencilInstance();
    if (!m_depthStencil)
    {
      MessageBox(NULL, "Failed to create Depth Stencil", "Error", MB_OK);
      return false;
    }

    m_depthStencilView = m_device->createDepthStencilViewInstance();
    if (!m_depthStencilView)
    {
      MessageBox(NULL, "Failed to create Depth Stencil View", "Error", MB_OK);
      return false;
    }

    m_inputLayout = m_device->createInputLayoutInstance();
    if (!m_inputLayout)
    {
      MessageBox(NULL, "Failed to create Input Layout", "Error", MB_OK);
      return false;
    }

    m_viewport = m_device->createViewportInstance();
    if (!m_viewport)
    {
      MessageBox(NULL, "Failed to create Viewport", "Error", MB_OK);
      return false;
    }

    m_vertexShader = m_device->createVertexShaderInstance();
    if (!m_vertexShader)
    {
      MessageBox(NULL, "Failed to create Vertex Shader", "Error", MB_OK);
      return false;
    }

    m_pixelShader = m_device->createPixelShaderInstance();
    if (!m_pixelShader)
    {
      MessageBox(NULL, "Failed to create Pixel Shader", "Error", MB_OK);
      return false;
    }

   
    m_vertBuffer = m_device->createVertexBufferInstance();
    if (!m_vertBuffer)
    {
      MessageBox(NULL, "Failed to create Vertex Buffer", "Error", MB_OK);
      return false;
    }

    m_indexBuffer = m_device->createIndexBufferInstance();
    if(!m_indexBuffer)
    {
      MessageBox(NULL, "Failed to create Index Buffer", "Error", MB_OK);
      return false;
    }

    m_CBNeverChanges = m_device->createConstantBufferNever();
    if (!m_CBNeverChanges)
    {
      MessageBox(NULL, "Failed to create Constant Buffer NC", "Error", MB_OK);
      return false;
    }

    m_CBChangesOnResize = m_device->createConstantBufferResize();
    if (!m_CBChangesOnResize)
    {
      MessageBox(NULL, "Failed to create Constsnt Buffer CR", "Error", MB_OK);
      return false;
    }

    m_CBChangesEveryframe = m_device->createConstantBufferEveryFrame();
    if (!m_CBChangesEveryframe)
    {
      MessageBox(NULL, "Failed to create Constant Buffer CEF", "Error", MB_OK);
      return false;
    }
    m_samplerState = m_device->createSamplerStateInstance();
    
    if (!m_CBChangesEveryframe)
    {
      MessageBox(NULL, "Failed to create Sampler State", "Error", MB_OK);
      return false;
    }

    textureManager = m_device->createTextureInstance();
    if (!m_indexBuffer)
    {
      MessageBox(NULL, "Failed to create Index Buffer", "Error", MB_OK);
      return false;
    }
    m_texture = m_device->createTextureInstance();
    if (!m_indexBuffer)
    {
      MessageBox(NULL, "Failed to create Index Buffer", "Error", MB_OK);
      return false;
    }

    m_rasState = m_device->creatreRasterizerStateInstance();

    m_SRV = m_device->createShaderRVInstance();
    if (!m_indexBuffer)
    {
      MessageBox(NULL, "Failed to create Index Buffer", "Error", MB_OK);
      return false;
    }

    m_mainCB = m_device->createConstantBufferInstance();
    if (!m_mainCB)
    {
      MessageBox(NULL, "Failed to create const Buffer", "Error", MB_OK);
      return false;
    }

    m_lightCB = m_device->createConstantBufferInstanceVec3();
    if (!m_lightCB)
    {
      MessageBox(NULL, "Failed to create const Buffer", "Error", MB_OK);
      return false;
    }

    return true;
  }

  
  void
  App::LoadModel() {
    mainCam.setFOV(kraMath::DEG2RAD(90.0f));
    mainCam.setNearPlane(0.01f);
    mainCam.setFarPlane(1000.0f);
    
    //m_texture->createTexture2DFromFile(*m_device, "resources/Textures/Vela_Gun_BaseColor.tga");
    m_renderTargetView->createRenderTargetView(*m_device);
    //m_texture->releaseTexture();

    //m_texture->createTexture2DFromFile(*m_device, "resources/Textures/Vela_Gun_Normal.tga");
    //m_renderTargetView->createRenderTargetView(*m_device, m_texture);
    //m_texture->releaseTexture();

    m_depthStencil->setDepthStencil(*m_device, m_device->getHeight(), m_device->getWidth());

    m_depthStencil->createDepthStencilState(*m_device);

    m_depthStencil->setDepthStencilState(*m_device);

    m_depthStencilView->createDepthStencilView(*m_device, *m_depthStencil);

    m_renderTargetView->setRenderTarget(*m_device, *m_depthStencilView, 1);

    m_viewport->createViewport(m_device->getWidth(), m_device->getHeight(), 0.0f, 0.0f);

    m_viewport->setViewport(m_device);

    if (!m_vertexShader->compileVertexShader("simpleVS.hlsl", "VS"))
    {
      DWORD err = GetLastError();
      MessageBox(NULL, "Failed to create Vertex shader. Error: " + err, "Error", MB_OK);

      std::cout << "Failed to compile shader\n";
      return;
    }

    m_vertexShader->createVertexShader(*m_device);

    m_inputLayout->defineInputLayout();

    m_inputLayout->createInputLayout(*m_device, *m_vertexShader);


    if (!m_pixelShader->compilePixelShader("simplePS.hlsl", "PS"))
    {
      MessageBox(NULL, "Failed to compile Pixel shader", "Error", MB_OK);
       
      std::cout << "Failed to compile shader\n";
      return;
    }
    m_pixelShader->createPixelShader(*m_device);

    /*for (uint32 i = 0 ; i <  6; ++i)
    {
      
      std::string modelName = "Vela_Mat_" + std::to_string(i+1) + ".X";
      modelPath += modelName;

      Model* newModel = new Model();
      Texture* newTex = m_device->createTextureInstance();
      Texture* normalTex = m_device->createTextureInstance();
      if (!newModel->loadModelFromFile(modelPath, *m_device, textureManager))
      {
        MessageBox(NULL, "Failed to Load a Model", "Error", MB_OK);

        return;
      }

      switch (i)
      {
      case 0:
        //newModel.getMeshVec()[i].m_material->setTextureOfType(*m_device, kraTextureType::BASECOLOR, "resources/Textures/Vela_Gun_BaseColor.tga");
        newTex->createTexture2DFromFile(*m_device, "resources/Textures/Vela_Gun_BaseColor.tga");
        normalTex->createTexture2DFromFile(*m_device, "resources/Textures/Vela_Gun_Normal.tga");
        //newModel->getMeshVec()[i]->m_material->m_baseColor->createTexture2DFromFile(*m_device, "resources/Textures/Vela_Gun_BaseColor.tga");

        break;

      case 1:
        //newModel.getMeshVec()[i].m_material->setTextureOfType(*m_device, kraTextureType::BASECOLOR, *textureManager, "resources/Textures/Vela_Legs_BaseColor.tga");
        newTex->createTexture2DFromFile(*m_device, "resources/Textures/Vela_Legs_BaseColor.tga");
        normalTex->createTexture2DFromFile(*m_device, "resources/Textures/Vela_Legs_Normal.tga");
        //newModel->getMeshVec()[i]->m_material->m_baseColor->createTexture2DFromFile(*m_device, "resources/Textures/Vela_Legs_BaseColor.tga");

        break;

      case 2:
        //newModel.getMeshVec()[i].m_material->setTextureOfType(*m_device, kraTextureType::BASECOLOR, *textureManager, "resources/Textures/Vela_Mechanical_BaseColor.tga");
        newTex->createTexture2DFromFile(*m_device, "resources/Textures/Vela_Mechanical_BaseColor.tga");
        normalTex->createTexture2DFromFile(*m_device, "resources/Textures/Vela_Mechanical_Normal.tga");
        //newModel->getMeshVec()[i]->m_material->m_baseColor->createTexture2DFromFile(*m_device, "resources/Textures/Vela_Mechanical_BaseColor.tga");
        break;
      
      case 3:
        //newModel.getMeshVec()[i].m_material->setTextureOfType(*m_device, kraTextureType::BASECOLOR, *textureManager, "resources/Textures/Vela_Char_BaseColor.tga");
        newTex->createTexture2DFromFile(*m_device, "resources/Textures/Vela_Char_BaseColor.tga");
        normalTex->createTexture2DFromFile(*m_device, "resources/Textures/Vela_Char_Normal.tga");
        //newModel->getMeshVec()[i]->m_material->m_baseColor->createTexture2DFromFile(*m_device, "resources/Textures/Vela_Char_BaseColor.tga");

        break;

      case 4:
        //newModel.getMeshVec()[i].m_material->setTextureOfType(*m_device, kraTextureType::BASECOLOR, *textureManager, "resources/Textures/Vela_Plate_BaseColor.tga");
        newTex->createTexture2DFromFile(*m_device, "resources/Textures/Vela_Plate_BaseColor.tga");
        normalTex->createTexture2DFromFile(*m_device, "resources/Textures/Vela_Plate_Normal.tga");

        //newModel->getMeshVec()[i]->m_material->m_baseColor->createTexture2DFromFile(*m_device, "resources/Textures/Vela_Plate_BaseColor.tga");

        break;

      case 5:
        //newModel.getMeshVec()[i].m_material->setTextureOfType(*m_device, kraTextureType::BASECOLOR, *textureManager, "resources/Textures/Vela_EyeCornea_BaseColor.tga");
        newTex->createTexture2DFromFile(*m_device, "resources/Textures/Vela_EyeCornea_BaseColor.tga");
        normalTex->createTexture2DFromFile(*m_device, "resources/Textures/Vela_EyeCornea_Normal.tga");

        //newModel->getMeshVec()[i]->m_material->m_baseColor->createTexture2DFromFile(*m_device, "resources/Textures/Vela_EyeCornea_BaseColor.tga");

        break;
      }

      for (int j = 0; j < newModel->getMeshVecSize(); ++j) {
        //newModel->getMeshVec()[j]->m_material->setTextureOfType(*m_device, kraTextureType::BASECOLOR, newTex, "resources/Textures/Vela_Gun_BaseColor.tga");
        newModel->getMeshVec()[j]->m_material->m_baseColor = newTex;
        newModel->getMeshVec()[j]->m_material->m_Normal = normalTex;

      }
      newTex->releaseTexture();
      normalTex->releaseTexture();
      m_modelsVec.push_back(newModel);
    }*/

    
      modelPath += "SCAR Mark16.obj";
      Model* newModel = new Model();
      Texture* newTex = m_device->createTextureInstance();
      Texture* normalTex = m_device->createTextureInstance();
      if (!newModel->loadModelFromFile(modelPath, *m_device, textureManager))
      {
        MessageBox(NULL, "Failed to Load a Model", "Error", MB_OK);

        return;
      }
      m_modelsVec.push_back(newModel);

    m_device->setPrimitiveTopology();
    m_rasState->createRasterizerState(*m_device);
    m_rasState->setRasterizerState(*m_device);

    m_samplerState->createSamplerState(*m_device);
    m_samplerState->setSamplerState(*m_device);


    m_world.identity();
    m_mainCB->add(m_world);
    

    mainCam.SetPosition(Vector3(0.0f, 50.0f, -20.0f));
    mainCam.SetObjecive(Vector3(0.0f, 50.0f, 0.0f));
    mainCam.setUp(Vector3(0.0f, 1.0f, 0.0f));
    mainCam.setFront(Vector3(0.0f, 0.0f, 1.0f));
    mainCam.setRight(Vector3(1.0f, 0.0f, 0.0f));
    mainCam.createViewMat();
    m_mainCB->add(mainCam.GetViewMatrix());

    m_projection.MatrixPerspectiveFOV(mainCam.getFOV(), static_cast<float>(m_device->getWidth()), static_cast<float>(m_device->getHeight()), mainCam.getNearPlane(), mainCam.getFarPlane());
    m_mainCB->add(m_projection);

    m_lightCB->add(Vector4(mainCam.getPosition(), 1.0f));

    m_mainCB->createConstantBuffer(*m_device);
    m_lightCB->createConstantBuffer(*m_device);

    m_mainCB->createConstantBuffer(*m_device);
    m_lightCB->updateSubResources(*m_device);
  }

  HINSTANCE
  App::loadDLL() {
    HINSTANCE GFXDLL;
    char currDirect[300];
    GetWindowsDirectoryA(currDirect, 300);

    std::string DLLPath(currDirect);
    DLLPath = DLLPath.append("\\").append("kraGraphicsDXd.dll");
  
    GFXDLL = LoadLibraryEx(DLLPath.c_str(), nullptr, LOAD_WITH_ALTERED_SEARCH_PATH);
  
    return GFXDLL;
  }

  void
  App::Initialize() {

  }

  void
  App::update(float deltaTime) {

    deltaTime += 5.0125f;


  }

  InputManager*
  App::getInputManager() {
    
    return m_inputManager;
  }

  uint32
  App::createBoolDevice(uint32 type) {
   
    switch (type)
    {
    case 0:
      return m_inputManager->createMouseDevice();
      break;
    case 1:
      return m_inputManager->createKeyboardDevice();
      break;
    case 2:
      return m_inputManager->createGamepadDevice();
      break;
    }


  }

  void
  App::MapBoolDevice(uint32 userBtn, uint32 deviceID, uint32 key) {
    
    m_inputManager->mapBoolDevice(userBtn, deviceID, key);

  }

  Camera*
  App::getActiveCamera() {
    return &mainCam;
  }

  void
  App::RotateWorldMat(int dir) {
    
    float t = 0.0f;
    
    t += kraMath::PI * 900000.00125f;
    m_world.MatrixRotY(t * dir);
  }

  void
  App::strafeCamera(int dir) {

    mainCam.MoveRight(5.0f * dir);

  }

  void
  App::render() {

    static float t = 0.0f;

    t += kraMath::PI * .00125f;
     
    //m_world.MatrixRotY(t);

    m_vertexShader->setVertexShader(*m_device);
    m_pixelShader->setPixelShader(*m_device);
    
    m_mainCB->setVertexConstantBuffer(*m_device, 0, 1);
    m_mainCB->setPixelConstantBuffer(*m_device, 0, 1);

    m_inputLayout->setInputLayout(*m_device);

    Vector4 ClearColor = { 0.5f, 0.0f, 0.8f, 1.0f };

    m_renderTargetView->clearRenderTargetView(m_device, ClearColor);
    m_depthStencilView->clearDSV(*m_device);
    

    m_mainCB->setConstData(0, m_world);
    m_mainCB->setConstData(1, mainCam.GetViewMatrix());
    m_mainCB->updateSubResources(*m_device);

    m_lightCB->setConstData(0, mainCam.getPosition());
    m_lightCB->updateSubResources(*m_device);

    for (uint32 i = 0; i < m_modelsVec.size(); ++i) {
      //for (uint32 j = 0; j < m_modelsVec[i]->getMeshVecSize(); ++j) {

      //    m_modelsVec[i]->getMeshVecObjbyIndex(j).m_material->getTextureOfType(kraTextureType::BASECOLOR)->setTextureShaderResource(m_device, 0, 1);
      //    m_modelsVec[i]->getMeshVec()[j]->m_material->getTextureOfType(kraTextureType::NORMAL)->setTextureShaderResource(m_device, 1, 1); 
      //}
      //
      m_modelsVec[i]->Draw(m_device);
    }

    m_device->PresentSwapChain();
  }

  

  void
  App::CleanupDevice() {
    if (m_device) {
      m_device->cleanContextState();
    }
    if (m_vertBuffer) {
      m_vertBuffer->Release();
    }
    if (m_inputLayout) {
      m_inputLayout->cleanInputLayout();
    }
    if (m_vertexShader) {
      m_vertexShader->cleanShader();
    }
    if (m_pixelShader) {
      m_pixelShader->cleanShader();
    }
    if (m_renderTargetView) {
      m_renderTargetView->cleanRTV();
    }
    if (m_device) {
      m_device->cleanSwapChain();
      m_device->cleanContext();
      m_device->cleanDevice();
    }
  }

  void
  App::destroy() {

  }

  void
  App::preInitialice() {

  }

  void
  App::postInitialice() {

  }

  void
    App::postUpdate() {

  }

  void
  App::postRender() {

  }

  void
  App::preDestroy() {

  }