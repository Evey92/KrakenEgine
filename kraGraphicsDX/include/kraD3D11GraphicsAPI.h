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
#include <windows.h>
namespace kraEngineSDK {
  class KRA_UTILGFX_EXPORT GraphicsAPI
  {
  public:
    GraphicsAPI() = default;
    ~GraphicsAPI();

    HRESULT
    initializeAPI(HWND g_hWnd);
    void 
    Render();
    void
    Cleanup();

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
    Texture m_pBackBuffer;
    Texture m_texture;
  };
}
