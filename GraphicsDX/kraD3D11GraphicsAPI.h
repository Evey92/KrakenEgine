#pragma once
#include "kraPrerequisitesGFX.h"
#include "kraD3D11Device.h"
#include "kraD3D11RenderTargetView.h"
#include "kraD3D11Texture.h"
#include "kraD3D11DepthStencil.h"
#include "kraD3D11DepthStencylView.h"
#include "kraD3D11Viewport.h"
#include "kraD3D11Shader.h"
#include "kraD3D11VertexShader.h"
#include "kraD3D11InputLayout.h"
#include "kraD3D11PixelShader.h"
#include "kraD3D11VertexBuffer.h"
#include "kraD3D11IndexBuffer.h"
#include "kraD3D11ConstantBuffer.h"
#include "kraVertex.h"

#include <d3d11.h>

namespace kraEngineSDK {
  class GraphicsAPI
  {
  public:
    GraphicsAPI();
    ~GraphicsAPI();

    HRESULT initializeAPI();
    void Render();

    Device m_device;
    RenderTargetView m_renderTargetView;
    DepthStencil m_depthStencil;
    DepthStencylView m_depthStencilView;
    Viewport m_viewport;
    VertexShader* m_vertexShader;
    InputLayout m_inputLayout;
    PixelShader* m_pixelShader;
    VertexBuffer<Vertex>* m_vertexBuffer;
    IndexBuffer<Vertex>* m_indexBuffer;
    ConstantBuffer<Vertex>* m_constantBuffer;
    HWND g_hWnd;
    Texture m_pBackBuffer;
    Texture m_texture;
  };

  HRESULT
    GraphicsAPI::initializeAPI() {
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
    * Set Primitive topologyu 
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

    m_vertexShader->compileVertexShader(L"VS.hlsl", "VS");
    m_vertexShader->createVertexShader(m_device.m_pd3dDevice);

    m_inputLayout.defineVertexLayout();
    m_inputLayout.defineTexcoordLayout();
    m_inputLayout.createInputLayout(m_device.m_pd3dDevice,
                                    m_vertexShader);
    m_inputLayout.setInputLayout(m_device.m_pImmediateContext);

    m_pixelShader->compilePixelShader(L"PS.hlsl", "PS");
    m_pixelShader->createPixelShader(m_device.m_pd3dDevice);

    /*
    * TODO:
    * -Set up VertexBuffer
    * -Set up IndexBuffer
    * -Set up primitive  topology
    * -Set up ConstantBuffer
    * -Load Texture
    * -Create Sample State
    * -Initialize World matrices
    * -Initialize View Matrix
    * -Iniitialize projection Matrix
    * After Setup, call Render
    */
    return hr;
  }

  void
  GraphicsAPI::Render() {

  }
}
