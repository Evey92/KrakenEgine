#include <kraDevice.h>

#include "kraD3D11DepthStencil.h"

namespace kraEngineSDK {
  bool
  DepthStencilDX::setDepthStencil(const Device& pDevice, uint32 height, uint32 width) {
    
    const DeviceDX& m_device = static_cast<const DeviceDX&>(pDevice);

    D3D11_TEXTURE2D_DESC descTexture;
    memset(&descTexture, 0, sizeof(descTexture));
    descTexture.Height = height;
    descTexture.Width = width;
    descTexture.MipLevels = 1;
    descTexture.ArraySize = 1;
    descTexture.Format = DXGI_FORMAT_R24G8_TYPELESS;
    descTexture.SampleDesc.Count = 1;
    descTexture.SampleDesc.Quality = 0;
    descTexture.Usage = D3D11_USAGE_DEFAULT;
    descTexture.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
    descTexture.CPUAccessFlags = 0;
    descTexture.MiscFlags = 0;


    m_device.m_pd3dDevice->CreateTexture2D(&descTexture, nullptr, &m_pd3dDepthStencil);

    if (!m_pd3dDepthStencil)
    {
      DWORD err = GetLastError();
      MessageBox(NULL, "Failed to set the Depth Stencil. Error: " + err, "Error", MB_OK);
      //std::cout << "No se pudo crear depth sctencil";
      return false;
    }
    return true;
  }

  bool
  DepthStencilDX::createDepthStencilState(const Device& pDevice) {

    const DeviceDX& m_device = static_cast<const DeviceDX&>(pDevice);
    
    HRESULT hr = S_OK;

    D3D11_DEPTH_STENCIL_DESC stencilStateDesc;
    memset(&stencilStateDesc, 0, sizeof(stencilStateDesc));

    stencilStateDesc.DepthEnable = true;
    stencilStateDesc.DepthFunc = D3D11_COMPARISON_LESS;
    stencilStateDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    stencilStateDesc.StencilEnable = false;
    stencilStateDesc.StencilReadMask;
    stencilStateDesc.StencilWriteMask;
    
    
    const D3D11_DEPTH_STENCILOP_DESC defaultDesc =
    { D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP,D3D11_COMPARISON_ALWAYS };
    stencilStateDesc.FrontFace = defaultDesc;
    stencilStateDesc.BackFace = defaultDesc;

    hr = m_device.m_pd3dDevice->CreateDepthStencilState(&stencilStateDesc, &m_pd3dDepthStencilState);
    if (FAILED(hr)) {
      return false;
    }

    return true;
  }
  
  void
  DepthStencilDX::setDepthStencilState(const Device& pDevice) {

    const DeviceDX& m_device = static_cast<const DeviceDX&>(pDevice);

    m_device.m_pImmediateContext->OMSetDepthStencilState(m_pd3dDepthStencilState, 1);
  }

  void
  DepthStencilDX::cleanDepthStencil() {
    m_pd3dDepthStencil->Release();
  }
}
