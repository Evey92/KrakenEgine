#include "kraD3D11FrameBuffer.h"

#include <kraTexture.h>
#include <kraRenderTargetView.h>
#include <kraD3D11DepthStencylView.h>
#include <kraGraphicsAPI.h>

#include "kraD3D11Device.h"
#include "kraD3D11Texture.h"
#include "kraD3D11RenderTargetView.h"
#include "kraD3D11DepthStencylView.h"

namespace kraEngineSDK {
   
  bool
  FrameBufferDX::initFramebuffer(uint32 width,
                                 uint32 height,
                                 uint32 samples,
                                 GFX_FORMAT::E colorFormat,
                                 GFX_FORMAT::E depthFormat)  {
    
    DeviceDX* pDevice = static_cast<DeviceDX*>(GraphicsAPI::instance().getDevice());
    m_colorTex = pDevice->createTextureInstance();
    m_depthTex = pDevice->createTextureInstance();
    m_frameRTV = pDevice->createRenderTargetInsttance();
    m_frameDSV = pDevice->createDepthStencilViewInstance();

    TextureDX& pTexture = reinterpret_cast<TextureDX&>(*m_colorTex);
    TextureDX& pDepthTex = reinterpret_cast<TextureDX&>(*m_depthTex);
    RenderTargetViewDX& pRTV = reinterpret_cast<RenderTargetViewDX&>(*m_frameRTV);
    DepthStencilViewDX& pDSV = reinterpret_cast<DepthStencilViewDX&>(*m_frameDSV);

    m_width = width;
    m_height = height;
    m_samples = samples;

    D3D11_TEXTURE2D_DESC texDesc;
    memset(&texDesc, 0, sizeof(texDesc));

    texDesc.Width = width;
    texDesc.Height = height;
    texDesc.MipLevels = 1;
    texDesc.ArraySize = 1;
    texDesc.SampleDesc.Count = samples;


    if (colorFormat != GFX_FORMAT::E::kFORMAT_UNKNOWN) {
      texDesc.Format = static_cast<DXGI_FORMAT>(colorFormat);
      texDesc.BindFlags = D3D11_BIND_RENDER_TARGET;
      
      if (samples <= 1) {
        texDesc.BindFlags |= D3D11_BIND_SHADER_RESOURCE;
      }

      if (FAILED(pDevice->m_pd3dDevice->CreateTexture2D(&texDesc, nullptr, &pTexture.m_pd3dTexture2D))) {
        std::cout<< "Failed to create FrameBuffer color texture";
        return false;
      }

      D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
      memset(&rtvDesc, 0, sizeof(rtvDesc));
      rtvDesc.Format = texDesc.Format;
      rtvDesc.ViewDimension = (samples > 1) ? D3D11_RTV_DIMENSION_TEXTURE2DMS : D3D11_RTV_DIMENSION_TEXTURE2D;
     
      if (FAILED(pDevice->m_pd3dDevice->CreateRenderTargetView(pTexture.m_pd3dTexture2D, &rtvDesc, &pRTV.m_pRenderTargetView))) {
        std::cout << "Failed to create FrameBuffer render target view\n";
        return false;
      }

      if (samples <= 1) {
        D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
        memset(&srvDesc, 0, sizeof(srvDesc));
        srvDesc.Format = texDesc.Format;
        srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        srvDesc.Texture2D.MostDetailedMip = 0;
        srvDesc.Texture2D.MipLevels = 1;
        if (FAILED(pDevice->m_pd3dDevice->CreateShaderResourceView(pTexture.m_pd3dTexture2D, &srvDesc, &pTexture.m_pSRV))) {
          std::cout<< "Failed to create FrameBuffer shader resource view\n";
          return false;
        }
      }
    }

    if (depthFormat != GFX_FORMAT::E::kFORMAT_UNKNOWN) {
      texDesc.Format = static_cast<DXGI_FORMAT>(depthFormat);
      texDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
      
      if (FAILED(pDevice->m_pd3dDevice->CreateTexture2D(&texDesc, nullptr, &pDepthTex.m_pd3dTexture2D))) {
        std::cout << "Failed to create FrameBuffer Depth Stencil View texture\n";
        return false;
      }

      D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
      memset(&dsvDesc, 0, sizeof(dsvDesc));
      dsvDesc.Format = texDesc.Format;
      dsvDesc.ViewDimension = (samples > 1) ? D3D11_DSV_DIMENSION_TEXTURE2DMS : D3D11_DSV_DIMENSION_TEXTURE2D;

      if (FAILED(pDevice->m_pd3dDevice->CreateDepthStencilView(pDepthTex.m_pd3dTexture2D, &dsvDesc, &pDSV.m_pDepthStencilView))) {
        std::cout << "Failed to create FrameBuffer Depth Stencil View\n";
        return false;
      }
    }
    
   return true;
  }

}
