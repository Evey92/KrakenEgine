#pragma once
#include "kraD3D11Device.h"
#include "kraD3D11Texture.h"
#include "kraD3D11Viewport.h"
#include "kraD3D11Shader.h"
#include "kraD3D11InputLayout.h"
#include "kraPrerequisitesGFX.h"
#include <d3d11.h>

namespace kraEngineSDK {
  class kraD3D11GraphicsAPI
  {
  public:
    kraD3D11GraphicsAPI();
    ~kraD3D11GraphicsAPI();

    HRESULT CreateRenderTargetView(ID3D11Texture2D* pBackBuffer);

    kraD3D11Device m_device;
    kraD3D11Texture m_texture;
    kraD3D11Texture m_pBackBuffer;
    kraD3D11Texture m_texture;
    kraD3D11Viewport m_viewport;
  };
}
