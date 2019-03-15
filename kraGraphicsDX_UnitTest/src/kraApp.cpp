#include <windows.h>
#include <string>
#include "kraApp.h"
 
void
App::run() {

}

  int
  App::startUp(void* m_hWnd) {
    typedef GraphicsAPI*(*initFunc)();
    HINSTANCE GFXDLL;
    
    /*color.x = 0.7f;
    color.y = 0.7f;
    color.z = 0.7f;
    color.w = 1.0f;*/

    std::string path = "kraGraphicsDXd.dll";

    GFXDLL = LoadLibraryExA(path.c_str(), nullptr, LOAD_WITH_ALTERED_SEARCH_PATH);
    if (!GFXDLL) {
      DWORD err = GetLastError();
      std::cout << "could not find specified DLL, error: " << err << std::endl;

      std::cout << "Press any key to continue...";

      FreeLibrary(GFXDLL);
      return 0;
    }

    initFunc initAPIFunc = (initFunc)GetProcAddress(GFXDLL, "createGraphicsAPI");
    if (!initAPIFunc) {
      std::cout << "could not find specified function" << std::endl;

      std::cout << "Press any key to continue...";

      FreeLibrary(GFXDLL);
      return 0;
    }

    gfxAPIInstance = initAPIFunc();
    if (!gfxAPIInstance) {
      MessageBox(NULL, "Failed to create Graphics API", "Error", MB_OK);

      return 0;
    }

    m_device = gfxAPIInstance->initializeAPI(reinterpret_cast<void*>(m_hWnd));
    if (!m_device)
    {
      MessageBox(NULL, "Failed to create Initialize API Device", "Error", MB_OK);
      return FALSE;
    }

    m_renderTargetView = m_device->createRenderTargetInsttance();
    if (!m_renderTargetView)
    {
      MessageBox(NULL, "Failed to create Render Target", "Error", MB_OK);
      return FALSE;
    }

    m_depthStencil = m_device->createDepthStencilInstance();
    if (!m_depthStencil)
    {
      MessageBox(NULL, "Failed to create Depth Stencil", "Error", MB_OK);
      return FALSE;
    }

    m_depthStencilView = m_device->createDepthStencilViewInstance();
    if (!m_depthStencilView)
    {
      MessageBox(NULL, "Failed to create Depth Stencil View", "Error", MB_OK);
      return FALSE;
    }

    m_inputLayout = m_device->createInputLayoutInstance();
    if (!m_inputLayout)
    {
      MessageBox(NULL, "Failed to create Input Layout", "Error", MB_OK);
      return FALSE;
    }

    m_viewport = m_device->createViewportInstance();
    if (!m_viewport)
    {
      MessageBox(NULL, "Failed to create Viewport", "Error", MB_OK);
      return FALSE;
    }

    m_vertexShader = m_device->createVertexShaderInstance();
    if (!m_vertexShader)
    {
      MessageBox(NULL, "Failed to create Vertex Shader", "Error", MB_OK);
      return FALSE;
    }

    m_pixelShader = m_device->createPixelShaderInstance();
    if (!m_pixelShader)
    {
      MessageBox(NULL, "Failed to create Pixel Shader", "Error", MB_OK);
      return FALSE;
    }

   
    m_vertBuffer = m_device->createVertexBufferInstance();
    if (!m_vertBuffer)
    {
      MessageBox(NULL, "Failed to create Vertex Buffer", "Error", MB_OK);
      return FALSE;
    }

    m_indexBuffer = m_device->createIndexBufferInstance();
    if(!m_indexBuffer)
    {
      MessageBox(NULL, "Failed to create Index Buffer", "Error", MB_OK);
      return FALSE;
    }

    m_CBNeverChanges = m_device->createConstantBufferNever();
    if (!m_CBNeverChanges)
    {
      MessageBox(NULL, "Failed to create Constant Buffer NC", "Error", MB_OK);
      return FALSE;
    }

    m_CBChangesOnResize = m_device->createConstantBufferResize();
    if (!m_CBChangesOnResize)
    {
      MessageBox(NULL, "Failed to create Constsnt Buffer CR", "Error", MB_OK);
      return FALSE;
    }

    m_CBChangesEveryframe = m_device->createConstantBufferEveryFrame();
    if (!m_CBChangesEveryframe)
    {
      MessageBox(NULL, "Failed to create Constant Buffer CEF", "Error", MB_OK);
      return FALSE;
    }
    m_samplerState = m_device->createSamplerStateInstance();
    
    if (!m_CBChangesEveryframe)
    {
      MessageBox(NULL, "Failed to create Sampler State", "Error", MB_OK);
      return FALSE;
    }
  }

  void
  App::LoadTriangle() {

    
    m_renderTargetView->createRenderTargetView(*m_device);

    m_renderTargetView->setRenderTarget(*m_device);

    m_viewport->createViewport(m_device->getHeight(), m_device->getWidth(), 1.0f, 1.0f);

    m_viewport->setViewport(m_device);
 
   
    if (!m_vertexShader->compileVertexShader("VS.hlsl", "VS"))
    {
      DWORD err = GetLastError();
      MessageBox(NULL, "Failed to compile Vertex shader", "Error", MB_OK);

      std::cout <<"Failed to compile shader\n";
      return;
    }

    m_vertexShader->createVertexShader(*m_device);

    m_inputLayout->defineVertexLayout();

    m_inputLayout->createInputLayout(*m_device, *m_vertexShader);
    
    m_inputLayout->setInputLayout(*m_device);

    if (!m_pixelShader->compilePixelShader("PS.hlsl", "PS"))
    {
      MessageBox(NULL, "Failed to compile Pixel shader", "Error", MB_OK);

      std::cout << "Failed to compile shader\n";
      return;
    }
    m_pixelShader->createPixelShader(*m_device);
    
    Vertex vert1(Vector3(0.0f, 0.5f, 0.5f));
    m_vertBuffer->add(vert1);
    Vertex vert2(Vector3(0.5f, -0.5f, 0.5f));
    m_vertBuffer->add(vert2);
    Vertex vert3(Vector3(-0.5f, -0.5f, 0.5f));
    m_vertBuffer->add(vert3);

    m_vertBuffer->createHardwareBuffer(*m_device);
    m_vertBuffer->setVertexBuffer(*m_device);

    m_device->setPrimitiveTopology();
  }

  void
  App::LoadCube() {
    
    float m_fov = kraMath::DEG2RAD(90.0f);
    float m_nearZ = 0.01f;
    float m_farZ = 100.0f;

    m_renderTargetView->createRenderTargetView(*m_device);
    
    m_depthStencil->setDepthStencil(*m_device, m_device->getHeight(), m_device->getWidth());
  
    m_depthStencilView->createDepthStencilView(*m_device, *m_depthStencil);

    m_renderTargetView->setRenderTarget(*m_device, *m_depthStencilView);

    m_viewport->createViewport(m_device->getHeight(), m_device->getWidth(), 1.0f, 1.0f);

    m_viewport->setViewport(m_device);

    if (!m_vertexShader->compileVertexShader("../VS.hlsl", "VS"))
    {
      DWORD err = GetLastError();
      MessageBox(NULL, "Failed to create Vertex shader", "Error", MB_OK);

      std::cout << "Failed to compile shader\n";
      return;
    }

    m_vertexShader->createVertexShader(*m_device);

    m_inputLayout->defineVertexLayout();
    m_inputLayout->defineTexcoordLayout();

    m_inputLayout->createInputLayout(*m_device, *m_vertexShader);

    m_inputLayout->setInputLayout(*m_device);

    if (!m_pixelShader->compilePixelShader("../PS.hlsl", "PS"))
    {
      MessageBox(NULL, "Failed to compile Pixel shader", "Error", MB_OK);

      std::cout << "Failed to compile shader\n";
      return;
    }
    m_pixelShader->createPixelShader(*m_device);

    
        Vertex vert1(Vector3(-1.0f, 1.0f, -1.0f), Vector2(0.0f, 0.0f));
        m_vertBuffer->add(vert1);
        Vertex vert2(Vector3(1.0f, 1.0f, -1.0f), Vector2(1.0f, 0.0f));
        m_vertBuffer->add(vert2);
        Vertex vert3(Vector3(1.0f, 1.0f, 1.0f), Vector2(1.0f, 1.0f));
        m_vertBuffer->add(vert3);
        Vertex vert4(Vector3(-1.0f, 1.0f, 1.0f), Vector2(0.0f, 1.0f));
        m_vertBuffer->add(vert4);

        Vertex vert5(Vector3(-1.0f, -1.0f, -1.0f), Vector2(0.0f, 0.0f));
        m_vertBuffer->add(vert5);
        Vertex vert6(Vector3(1.0f, -1.0f, -1.0f), Vector2(1.0f, 0.0f));
        m_vertBuffer->add(vert6);
        Vertex vert7(Vector3(1.0f, -1.0f, 1.0f), Vector2(1.0f, 1.0f));
        m_vertBuffer->add(vert7);
        Vertex vert8(Vector3(-1.0f, -1.0f, 1.0f), Vector2(0.0f, 1.0f));
        m_vertBuffer->add(vert8);

        Vertex vert9(Vector3(-1.0f, -1.0f, 1.0f), Vector2(0.0f, 0.0f));
        m_vertBuffer->add(vert9);
        Vertex vert10(Vector3(-1.0f, -1.0f, -1.0f), Vector2(1.0f, 0.0f));
        m_vertBuffer->add(vert10);
        Vertex vert11(Vector3(-1.0f, 1.0f, -1.0f), Vector2(1.0f, 1.0f));
        m_vertBuffer->add(vert11);
        Vertex vert12(Vector3(-1.0f, 1.0f, 1.0f), Vector2(0.0f, 1.0f));
        m_vertBuffer->add(vert12);
        
        Vertex vert13(Vector3(1.0f, -1.0f, 1.0f), Vector2(0.0f, 0.0f));
        m_vertBuffer->add(vert13);
        Vertex vert14(Vector3(1.0f, -1.0f, -1.0f), Vector2(1.0f, 0.0f));
        m_vertBuffer->add(vert14);
        Vertex vert15(Vector3(1.0f, 1.0f, -1.0f), Vector2(1.0f, 1.0f));
        m_vertBuffer->add(vert15);
        Vertex vert16(Vector3(1.0f, 1.0f, 1.0f), Vector2(0.0f, 1.0f));
        m_vertBuffer->add(vert16);
        
        Vertex vert17(Vector3(-1.0f, -1.0f, -1.0f), Vector2(0.0f, 0.0f));
        m_vertBuffer->add(vert17);
        Vertex vert18(Vector3(1.0f, -1.0f, -1.0f), Vector2(1.0f, 0.0f));
        m_vertBuffer->add(vert18);
        Vertex vert19(Vector3(1.0f, 1.0f, -1.0f), Vector2(1.0f, 1.0f));
        m_vertBuffer->add(vert19);
        Vertex vert20(Vector3(-1.0f, 1.0f, -1.0f), Vector2(0.0f, 1.0f));
        m_vertBuffer->add(vert20);
        
        Vertex vert21(Vector3(-1.0f, -1.0f, 1.0f), Vector2(0.0f, 0.0f));
        m_vertBuffer->add(vert21);
        Vertex vert22(Vector3(1.0f, -1.0f, 1.0f), Vector2(1.0f, 0.0f));
        m_vertBuffer->add(vert22);
        Vertex vert23(Vector3(1.0f, 1.0f, 1.0f), Vector2(1.0f, 1.0f));
        m_vertBuffer->add(vert23);
        Vertex vert24(Vector3(-1.0f, 1.0f, 1.0f), Vector2(0.0f, 1.0f));
        m_vertBuffer->add(vert24);
    
        m_vertBuffer->createHardwareBuffer(*m_device);
        m_vertBuffer->setVertexBuffer(*m_device);

        m_indexBuffer->add(3); m_indexBuffer->add(1); m_indexBuffer->add(0);
        m_indexBuffer->add(2); m_indexBuffer->add(1); m_indexBuffer->add(3);
        
        m_indexBuffer->add(6); m_indexBuffer->add(4); m_indexBuffer->add(5);
        m_indexBuffer->add(7); m_indexBuffer->add(4); m_indexBuffer->add(6);
        
        m_indexBuffer->add(11); m_indexBuffer->add(9); m_indexBuffer->add(8);
        m_indexBuffer->add(10); m_indexBuffer->add(9); m_indexBuffer->add(11);
        
        m_indexBuffer->add(14); m_indexBuffer->add(12); m_indexBuffer->add(13);
        m_indexBuffer->add(15); m_indexBuffer->add(12); m_indexBuffer->add(14);

        m_indexBuffer->add(19); m_indexBuffer->add(17); m_indexBuffer->add(16);
        m_indexBuffer->add(18); m_indexBuffer->add(17); m_indexBuffer->add(19);

        m_indexBuffer->add(22); m_indexBuffer->add(20); m_indexBuffer->add(21);
        m_indexBuffer->add(23); m_indexBuffer->add(20); m_indexBuffer->add(22);
        
        m_indexBuffer->createIndexBuffer(*m_device);
        m_indexBuffer->setIndexBuffer(*m_device);

        m_device->setPrimitiveTopology();

        m_CBNeverChanges->createConstantBuffer(*m_device);
        m_CBChangesOnResize->createConstantBuffer(*m_device);
        m_CBChangesEveryframe->createConstantBuffer(*m_device);

        m_samplerState->createSamplerState(*m_device);

        //////////////////////////////////////
        ///////////////////TEST//////////////

        /*Model newModel;

        for (uint32 i = 0; i < newModel.getMeshVecSize(); i++) {

          newModel.getMeshVec()[i].m_vertexBurffer->createHardwareBuffer(*m_device);

          newModel.getMeshVec()[i].m_vertexBurffer->setVertexBuffer(*m_device);
          newModel.getMeshVec()[i].m_indexBuffer->setIndexBuffer(*m_device);
        }*/

        

        /////////////////////////////////////

        Vector4 Eye(0.0f, 3.0f, - 6.0f, 0.0f);
        Vector4 At(0.0f, 1.0f, 0.0f, 0.0f);
        Vector4 Up(0.0f, 1.0f, 0.0f, 0.0f);

        m_view = m_view.MatrixLookAtLH(Eye, At, Up);
        m_view.transpose();

        CBNeverChanges cbNeverChanges;
        cbNeverChanges.m_view = m_view;

        m_CBNeverChanges->updateSubResources(*m_device, cbNeverChanges);
        
       
        m_projection.MatrixPerspectiveFOV(m_fov, static_cast<float>(m_device->getWidth() / m_device->getHeight()), m_nearZ, m_farZ);
        m_projection.transpose();
        
        CBChangeOnResize cbChangeOnResize;
        cbChangeOnResize.m_projection = m_projection;
        m_CBChangesOnResize->updateSubResources(*m_device, cbChangeOnResize);

  }

  void
  App::LoadModel() {
     float m_fov = kraMath::DEG2RAD(90.0f);
    float m_nearZ = 0.01f;
    float m_farZ = 100.0f;

    m_renderTargetView->createRenderTargetView(*m_device);

    m_depthStencil->setDepthStencil(*m_device, m_device->getHeight(), m_device->getWidth());

    m_depthStencilView->createDepthStencilView(*m_device, *m_depthStencil);

    m_renderTargetView->setRenderTarget(*m_device, *m_depthStencilView);

    m_viewport->createViewport(m_device->getHeight(), m_device->getWidth(), 1.0f, 1.0f);

    m_viewport->setViewport(m_device);

    if (!m_vertexShader->compileVertexShader("VS.hlsl", "VS"))
    {
      DWORD err = GetLastError();
      MessageBox(NULL, "Failed to create Vertex shader", "Error", MB_OK);

      std::cout << "Failed to compile shader\n";
      return;
    }

    m_vertexShader->createVertexShader(*m_device);

    m_inputLayout->defineInputLayout();
    //m_inputLayout->defineTexcoordLayout();

    m_inputLayout->createInputLayout(*m_device, *m_vertexShader);

    m_inputLayout->setInputLayout(*m_device);

    if (!m_pixelShader->compilePixelShader("PS.hlsl", "PS"))
    {
      MessageBox(NULL, "Failed to compile Pixel shader", "Error", MB_OK);

      std::cout << "Failed to compile shader\n";
      return;
    }
    m_pixelShader->createPixelShader(*m_device);

    Model newModel;

    if (!newModel.loadModelFromFile("resources/Models/cube.obj", *m_device))
    {
      MessageBox(NULL, "Failed to Load a Model", "Error", MB_OK);

      return;
    }

    m_modelsVec.push_back(newModel);

    m_device->setPrimitiveTopology();

    m_CBNeverChanges->createConstantBuffer(*m_device);
    m_CBChangesOnResize->createConstantBuffer(*m_device);
    m_CBChangesEveryframe->createConstantBuffer(*m_device);

    m_samplerState->createSamplerState(*m_device);

    Vector4 Eye(0.0f, 3.0f, -6.0f, 0.0f);
    Vector4 At(0.0f, 1.0f, 0.0f, 0.0f);
    Vector4 Up(0.0f, 1.0f, 0.0f, 0.0f);

    m_view = m_view.MatrixLookAtLH(Eye, At, Up);
    //m_view.transpose();

    CBNeverChanges cbNeverChanges;
    cbNeverChanges.m_view = m_view;

    m_CBNeverChanges->updateSubResources(*m_device, cbNeverChanges);


    m_projection.MatrixPerspectiveFOV(m_fov, static_cast<float>(m_device->getWidth() / m_device->getHeight()), m_nearZ, m_farZ);
    //m_projection.transpose();

    CBChangeOnResize cbChangeOnResize;
    cbChangeOnResize.m_projection = m_projection;
    m_CBChangesOnResize->updateSubResources(*m_device, cbChangeOnResize);

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

  }

  void
  App::render() {

    static float t = 0.0f;

    m_world.identity();
    m_world.MatrixRotY(t);

    m_world.transpose();

    Vector4 ClearColor = { 0.5f, 0.0f, 0.8f, 1.0f };
    m_renderTargetView->clearRenderTargetView(m_device, ClearColor);

    m_depthStencilView->clearDSV(*m_device);
    m_samplerState->setSamplerState(*m_device);

    CBChangesEveryFrame cbChangesEveryFrame;

    cbChangesEveryFrame.m_world = m_world;
    cbChangesEveryFrame.m_vMeshColor = color;

    m_CBChangesEveryframe->updateSubResources(*m_device, cbChangesEveryFrame);

    m_vertexShader->setVertexShader(*m_device);
    m_CBNeverChanges->setVertexConstantBuffer(*m_device, 0, 1);
    m_CBChangesOnResize->setVertexConstantBuffer(*m_device, 1, 1);
    m_CBChangesEveryframe->setVertexConstantBuffer(*m_device, 2, 1);
    m_pixelShader->setPixelShader(*m_device);
    m_CBChangesEveryframe->setPixelConstantBuffer(*m_device, 2, 1);

    

    //TODO: Replace this with the function to draw from each mesh.
    
    for (uint32 i = 0; i < m_modelsVec.size(); i++) {

      m_modelsVec[i].Draw(m_device);

    }

    m_device->PresentSwapChain();
  }

  void
  App::RenderCube() {
    
    static float t = 0.0f;

    m_world.identity();
    m_world.MatrixRotY(t);
    
    m_world.transpose();

    color.x = (sinf(t * 1.0) + 1.0f) * 0.5f;
    color.y = (sinf(t * 3.0) + 1.0f) * 0.5f;
    color.x = (sinf(t * 5.0) + 1.0f) * 0.5f;

    Vector4 ClearColor = { 0.5f, 0.0f, 0.8f, 1.0f };
    m_renderTargetView->clearRenderTargetView(m_device, ClearColor);

    m_depthStencilView->clearDSV(*m_device);

    CBChangesEveryFrame cbChangesEveryFrame;
    
    cbChangesEveryFrame.m_world = m_world;
    cbChangesEveryFrame.m_vMeshColor = color;

    m_CBChangesEveryframe->updateSubResources(*m_device, cbChangesEveryFrame);

    m_vertexShader->setVertexShader(*m_device);
    m_CBNeverChanges->setVertexConstantBuffer(*m_device, 0, 1);
    m_CBChangesOnResize->setVertexConstantBuffer(*m_device, 1, 1);
    m_CBChangesEveryframe->setVertexConstantBuffer(*m_device, 2, 1);
    m_pixelShader->setPixelShader(*m_device);
    m_CBChangesEveryframe->setPixelConstantBuffer(*m_device, 2, 1);

    m_samplerState->setSamplerState(*m_device);
    
    m_device->DrawIndexed(36, 0, 0);

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