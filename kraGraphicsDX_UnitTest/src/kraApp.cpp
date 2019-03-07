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
    

    std::string path = "C:\\Users\\Usuario\\Documents\\UAD\\8vo\\KrakenEgine\\bin\\x64\\kraGraphicsDXd.dll";
    //std::string path = "C:\\Users\\Ivan\\Documents\\UAD\\8vo\\Motores\\KrakenEgine\\bin\\x64\\kraGraphicsDXd.dll";
  
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
      std::cout << "could not create GFX API" << std::endl;

      return 0;
    }

    m_device = gfxAPIInstance->initializeAPI(reinterpret_cast<void*>(m_hWnd));

    if (!m_device)
    {
      std::cout << "could not find specified function" << std::endl;
      return FALSE;
    }

    m_renderTargetView = m_device->createRenderTargetInsttance();
    if (!m_renderTargetView)
    {
      std::cout << "could not find specified function" << std::endl;
      return FALSE;
    }

    m_inputLayout = m_device->createInputLayoutInstance();
    if (!m_inputLayout)
    {
      std::cout << "could not find specified function" << std::endl;
      return FALSE;
    }

    m_viewport = m_device->createViewportInstance();
    if (!m_viewport)
    {
      std::cout << "could not find specified function" << std::endl;
      return FALSE;
    }

    m_vertexShader = m_device->createVertexShaderInstance();
    if (!m_vertexShader)
    {
      std::cout << "could not find specified function" << std::endl;
      return FALSE;
    }

    /*m_pixelShader = reinterpret_cast<PixelShader*>(m_device->createPixelShaderInstance());
    if (!m_pixelShader)
    {
      std::cout << "could not find specified function" << std::endl;
      return FALSE;
    }


    m_vertBuffer = reinterpret_cast<VertexBuffer<Vertex>*>(m_device->createVertexBufferInstance());
    if (!m_vertBuffer)
    {
      std::cout << "could not find specified function" << std::endl;
      return FALSE;
    }*/

  }

  void
  App::RenderTriangle() {

    
    m_renderTargetView->createRenderTargetView(m_device);

    m_viewport->createViewport(m_device->getHeight(), m_device->getWidth(), 1.0f, 1.0f);

    m_viewport->setViewport(m_device);
 
    m_vertexShader->compileVertexShader("VS.hlsl", "VS");
    /*if (!m_vertexShader->compileVertexShader(L"VS.hlsl", "VS"))
    {
      DWORD err = GetLastError();
      std::cout <<"Failed to compile shader\n";
      return;
    }*/

    m_vertexShader->createVertexShader(*m_device);

    m_inputLayout->defineVertexLayout();

    m_inputLayout->createInputLayout(*m_device, *m_vertexShader);
    
    m_inputLayout->setInputLayout(*m_device);

    if (!m_pixelShader->compilePixelShader(L"PS.hlsl", "PS"))
    {
      std::cout << "Failed to compile shader\n";
      return;
    }
    m_pixelShader->createPixelShader(m_device);
    
    Vertex vert1(Vector3(0.0f, 0.5f, 0.5f));
    m_vertBuffer->add(vert1);
    Vertex vert2(Vector3(0.5f, -0.5f, 0.5f));
    m_vertBuffer->add(vert2);
    Vertex vert3(Vector3(-0.5f, -0.5f, 0.5f));
    m_vertBuffer->add(vert3);

    m_vertBuffer->createHardwareBuffer(m_device);
    m_vertBuffer->setVertexBuffer(m_device);

    m_device->setPrimitiveTopology();
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
    Vector4 ClearColor = { 0.0f, 0.125f, 0.3f, 1.0f };
    m_renderTargetView->clearRenderTargetView(m_device, ClearColor);
    m_vertexShader->setVertexShader(m_device);
    m_pixelShader->setPixelShader(m_device);
    m_device->Draw(3, 0);
    m_device->PresentSwapChain();
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