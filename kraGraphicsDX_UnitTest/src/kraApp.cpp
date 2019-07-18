#include "kraApp.h"

#include <windows.h>
#include <string>

#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>

void
App::run() {

  ImGui::Text("Hello world %d", 123);
  if (ImGui::Button("Save")) {

    std::cout << "Yay, you did the thing";
  }

  MSG msg = { 0 };

  while (m_window->m_isOpen)
  {
    m_inputManager->managerUpdate();
    m_window->handleMSG(static_cast<void*>(&msg), *m_inputManager);
    m_inputManager->handleMessage(static_cast<void*>(&msg));
    update();
    if (m_inputManager->boolWasDown(Button::E::CTRLKey))
    {

      Log("CTRL Key was pressed");

      getActiveCamera()->MoveUP(-10.0f);
    }
    render();
  }
}

  bool
  App::startUp(void* m_hWnd, int nCmdShow) {
    
    Initialize(nCmdShow);
    
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

    m_device = gfxAPIInstance->initializeAPI(reinterpret_cast<void*>(m_window->m_hWnd));
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

    uint32 KeyDValue = 129;
    uint32 keyAValue = 0x41;
    uint32 keyWValue = 0x57;
    uint32 keySValue = 0x0053;
    uint32 keyQValue = 81;
    uint32 keyEValue = 69;
    uint32 keySPACEValue = 0x20;
    uint32 keyCTRLValue = 130;
    uint32 mouseXvalue = 21;
    uint32 mouseyvalue = 22;
    uint32 keyboardID;
    uint32 mouseID;

    keyboardID = createBoolDevice(DeviceType::E::Keyboard);
    mouseID = createBoolDevice(DeviceType::E::Mouse);

    m_inputManager->setInputMap();

    MapBoolDevice(Button::E::Dkey, keyboardID, KeyDValue);
    MapBoolDevice(Button::E::AKey, keyboardID, keyAValue);
    MapBoolDevice(Button::E::WKey, keyboardID, keyWValue);
    MapBoolDevice(Button::E::SKey, keyboardID, keySValue);
    MapBoolDevice(Button::E::QKey, keyboardID, keyQValue);
    MapBoolDevice(Button::E::EKey, keyboardID, keyEValue);
    MapBoolDevice(Button::E::SPACEKey, keyboardID, keySPACEValue);
    MapBoolDevice(Button::E::CTRLKey, keyboardID, keyCTRLValue);
    m_inputManager->mapFloatDevice(Button::E::MouseX, mouseID, mouseXvalue);
    m_inputManager->mapFloatDevice(Button::E::MouseY, mouseID, mouseyvalue);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();
    
    ImGui_ImplWin32_Init(m_hWnd);


    return true;
  }

  
  bool
  App::LoadModel() {
    mainCam.setFOV(kraMath::DEG2RAD(90.0f));
    mainCam.setNearPlane(0.01f);
    mainCam.setFarPlane(10000.0f);

    m_renderTargetView->createRenderTargetView(*m_device);


    m_depthStencil->setDepthStencil(*m_device, m_device->getHeight(), m_device->getWidth());

    m_depthStencil->createDepthStencilState(*m_device);

    m_depthStencil->setDepthStencilState(*m_device);

    m_depthStencilView->createDepthStencilView(*m_device, *m_depthStencil);

    m_renderTargetView->setRenderTarget(*m_device, *m_depthStencilView, 1);

    m_viewport->createViewport(m_device->getWidth(), m_device->getHeight(), 0.0f, 0.0f);

    m_viewport->setViewport(m_device);

    if (!m_vertexShader->compileVertexShader("bumpVS.hlsl", "VS"))
    {
      DWORD err = GetLastError();
      MessageBox(NULL, "Failed to create Vertex shader. Error: " + err, "Error", MB_OK);

      std::cout << "Failed to compile shader\n";
      return false;
    }

    m_vertexShader->createVertexShader(*m_device);

    m_inputLayout->defineInputLayout();

    m_inputLayout->createInputLayout(*m_device, *m_vertexShader);


    if (!m_pixelShader->compilePixelShader("bumpPS.hlsl", "PS"))
    {
      MessageBox(NULL, "Failed to compile Pixel shader", "Error", MB_OK);
       
      std::cout << "Failed to compile shader\n";
      return false;
    }
    m_pixelShader->createPixelShader(*m_device);

    
      modelPath += "Soi_Armour_A.fbx";
      Model* newModel = new Model();
      Texture* newTex = m_device->createTextureInstance();
      Texture* normalTex = m_device->createTextureInstance();
      if (!newModel->loadModelFromFile(modelPath, *m_device, textureManager))
      {
        Log("Failed to Load a Model");

        return false;
      }
      m_modelsVec.push_back(newModel);

    m_device->setPrimitiveTopology();
    m_rasState->createRasterizerState(*m_device);
    m_rasState->setRasterizerState(*m_device);

    m_samplerState->createSamplerState(*m_device);
    m_samplerState->setSamplerState(*m_device);


    m_world.identity();
    m_mainCB->add(m_world);
    

    mainCam.setUp(Vector3(0.0f, 1.0f, 0.0f));
    mainCam.setFront(Vector3(0.0f, 0.0f, -1.0f));
    mainCam.setRight(Vector3(1.0f, 0.0f, 0.0f));
    mainCam.SetPosition(Vector3(0.0f, 60.0f, 80.0f));
    mainCam.SetObjecive(Vector3(0.0f, 50.0f, 0.0f));

    mainCam.createViewMat();
    m_mainCB->add(mainCam.GetViewMatrix());

    Vector3 lightPosition = Vector3(100.0f, 0.0f, 100.0f);

    m_projection.MatrixPerspectiveFOV(mainCam.getFOV(), static_cast<float>(m_device->getWidth()), static_cast<float>(m_device->getHeight()), mainCam.getNearPlane(), mainCam.getFarPlane());
    m_mainCB->add(m_projection);

    m_lightCB->add(Vector4(mainCam.getPosition(), 1.0f));

    m_mainCB->createConstantBuffer(*m_device);
    m_lightCB->createConstantBuffer(*m_device);

    m_mainCB->createConstantBuffer(*m_device);
    m_lightCB->updateSubResources(*m_device);
    return true;
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
  App::Initialize(int nCmdShow) {
    m_window = new Win32Window(1600, 1000, "Kraken Engine Tesat Application", Vector2(0, 0));
    if (!m_window->initWindow(nCmdShow))
    {
      std::cout << "Window couldn't be initialized.\n";
    }
  }

  void
  App::update() {
    
    //Log("Entered update state");

    if (m_inputManager->boolWasDown(0)) {
      getActiveCamera()->MoveRight(10.0f);
      Log("D Key was pressed");

    }
    if (m_inputManager->boolWasDown(Button::E::AKey))
    {
      //MessageBox(NULL, "Presionaste la tecla A", "Event", MB_OK);
      Log("A Key was pressed");

      getActiveCamera()->MoveRight(-10.0f);
    }
    if (m_inputManager->boolWasDown(Button::E::WKey))
    {
      
      getActiveCamera()->MoveForward(10.0f);
      Log("W Key was pressed");

    }
    if (m_inputManager->boolWasDown(Button::E::SKey))
    {
      //MessageBox(NULL, "Presionaste la tecla S", "Event", MB_OK);
      Log("S Key was pressed");

      getActiveCamera()->MoveForward(-10.0f);
    }
    if (m_inputManager->boolWasDown(Button::E::SPACEKey))
    {
      //MessageBox(NULL, "Presionaste la tecla W", "Event", MB_OK);
      Log("space Key was pressed");

      getActiveCamera()->MoveUP(10.0f);
    }

    if (m_inputManager->boolWasDown(Button::E::CTRLKey))
    {
      
      Log("CTRL Key was pressed");

      getActiveCamera()->MoveUP(-10.0f);
    }
    if (m_inputManager->boolWasDown(Button::E::Dkey))
    {
      Log("D Key was pressed");

      rotateCamera(10);
    }
    if (m_inputManager->boolWasDown(Button::E::EKey))
    {
      Log("E Key was pressed");

      rotateCamera(-10);

    }
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
      m_modelsVec[i]->Draw(m_device);
    }

    m_device->PresentSwapChain();
  }


#pragma region INPUT_FUNCTIONS
  kraInputManager*
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

#pragma endregion INPUT_FUNCTIONS

#pragma region CAMERA_FUNCTIONS
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
    App::rotateCamera(float angle) {

    mainCam.Yaw(angle);

  }

#pragma endregion CAMERA_FUNCTIONS
 

  void 
  App::Log(String outputString)
  {
    std::cout << outputString << std::endl;
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