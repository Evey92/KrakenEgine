#include "kraD3D11GraphicsAPI.h"

namespace kraEngineSDK {
  
  GraphicsAPI::~GraphicsAPI()
  {

  }
  HRESULT
  GraphicsAPI::initializeAPI(HWND g_hWnd) {
    HRESULT hr = S_OK;
    /*
    * Init device and Swap Chain
    * Create Render target view
    * Create Depth Stencil texture
    * Create Depth Stencil view
    * Set Viewport
    * Compile vertex Shader
    * Create Vertex Shader
    * Define Input Layout
    * Create Input Layout
    * Set input Layout
    * compile pixel shader
    * Create Pixel shader
    * Create vertex buffer
    * Creat Index Buffer
    * Set Primitive topology 
    * Create Constant buffer
    * Load texture
    * Create Sample State
    * Initialize world Matrices
    * Initialize view Matrices
    * Initialize project Matrices
    */
    
    m_device.initializeDevice(g_hWnd);
    m_renderTargetView.createRenderTargetView(m_device.m_pd3dDevice,
                                             m_device.m_pSwapChain);

    m_depthStencil.createDepthStencil(m_device.m_pd3dDevice, 
                                      m_device.m_height,
                                      m_device.m_width);

    m_depthStencilView.createDepthStencilView(m_device.m_pd3dDevice,
                                              &m_depthStencil);

    m_viewport.createViewport(m_device.m_width, m_device.m_height, 0, 0);

    m_viewport.setViewport(m_device.m_pImmediateContext);

    m_vertexShader.compileVertexShader(L"VS.hlsl", "VS");
    m_vertexShader.createVertexShader(m_device.m_pd3dDevice);

    m_inputLayout.defineVertexLayout();
    //m_inputLayout.defineTexcoordLayout();
    m_inputLayout.createInputLayout(m_device.m_pd3dDevice,
                                    &m_vertexShader);
    m_inputLayout.setInputLayout(m_device.m_pImmediateContext);

    m_pixelShader.compilePixelShader(L"PS.hlsl", "PS");
    m_pixelShader.createPixelShader(m_device.m_pd3dDevice);

    Vertex vert1;
    vert1.m_position = Vector3(0.0f, 0.5f, 0.5f);
    m_vertexBuffer.add(vert1);
    vert1.m_position = Vector3(0.5f, -0.5f, 0.5f);
    m_vertexBuffer.add(vert1);
    vert1.m_position = Vector3(-0.5f, -0.5f, 0.5f);
    m_vertexBuffer.add(vert1);

    m_vertexBuffer.createHardwareBuffer(m_device.m_pd3dDevice);
    m_vertexBuffer.setVertexBuffer(m_device.m_pImmediateContext);

    /*
    * TODO:
    * -Set up VertexBuffer
    * -Set up IndexBuffer
    * -Set up ConstantBuffer
    * -Load Texture
    * -Create Sample State
    * -Initialize World matrices
    * -Initialize View Matrix
    * -Iniitialize projection Matrix
    * After Setup, call Render
    */
    m_device.m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    return hr;
  }

  void
  GraphicsAPI::Render() {
    
    Vector4 clearColor = { 0.0f, 0.125f, 0.3f, 1.0f };
    m_device.m_pImmediateContext->ClearRenderTargetView(m_renderTargetView.m_pRenderTargetView, &clearColor[0]);
    m_device.m_pImmediateContext->VSSetShader(m_vertexShader.m_pVertexShader, NULL, 0);
    m_device.m_pImmediateContext->PSSetShader(m_pixelShader.m_pPixelShader, NULL, 0);
    m_device.m_pImmediateContext->Draw(3, 0);

    m_device.m_pSwapChain->Present(0, 0);

  }

  void
  GraphicsAPI::Cleanup() {
    
    m_device.cleanContextState();
    
    m_vertexBuffer.cleanVertexBuffer();
    m_indexBuffer.cleanIndexBuffer();
    m_inputLayout.cleanInputLayout();
    m_vertexShader.cleanShader();
    m_pixelShader.cleanShader();
    m_depthStencil.cleanDepthStencil();
    m_depthStencilView.cleanDSV();
    m_renderTargetView.cleanRTV();
    m_device.cleanSwapChain();
    m_device.cleanContext();
    m_device.cleanDevice();
  }
}