#include <kraDevice.h>
#include <kraResourceLoading.h>

#include "kraD3D11Device.h"
#include "kraD3D11Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace kraEngineSDK {

  TextureDX::TextureDX(const TextureDX& newTex) {
    m_pd3dTexture2D = newTex.m_pd3dTexture2D;

  }

  void
  TextureDX::createTexture2D(const Device& pDevice, int height, int width) {

    const DeviceDX& m_pDevice = static_cast<const DeviceDX&>(pDevice);
    /*DXGI_FORMAT* m_format = static_cast<DXGI_FORMAT*>(format);
    D3D11_BIND_FLAG* m_bindFlag = static_cast<D3D11_BIND_FLAG*>(bindFlag);*/

    D3D11_TEXTURE2D_DESC descTexture;
    memset(&descTexture, 0, sizeof(descTexture));
    descTexture.Height = height;
    descTexture.Width = width;
    descTexture.MipLevels = 1;
    descTexture.ArraySize = 1;
    descTexture.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    descTexture.SampleDesc.Count = 1;
    descTexture.SampleDesc.Quality = 0;
    descTexture.Usage = D3D11_USAGE_DEFAULT;
    descTexture.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
    descTexture.CPUAccessFlags = 0;
    descTexture.MiscFlags = 0;


    D3D11_SUBRESOURCE_DATA initBuffer;
    memset(&initBuffer, 0, sizeof(initBuffer));
    m_pDevice.m_pd3dDevice->CreateTexture2D(&descTexture, &initBuffer, &m_pd3dTexture2D);
  }

 
  void 
  TextureDX::createTexture2D(void* pDevice, int height, int width, GFX_FORMAT::E format, void* bindFlag, GFX_USAGE::E usage, CPU_USAGE::E cpuUsage)
  {
    //TODO
  }

  void 
  TextureDX::createRenderableTexture2D(const Device& pDevice, int height, int width)
  {
    //TODO
  }

  bool 
  TextureDX::createTexture2DFromFile(const Device& pDevice, 
                                     String filename, 
                                     GFX_FORMAT::E format, 
                                     GFX_USAGE::E usage, 
                                     CPU_USAGE::E cpuUsage)
  {
    const DeviceDX& m_pDevice = static_cast<const DeviceDX&>(pDevice);

    HRESULT hr = S_OK;

    Image image;
    unsigned char* pixels;
    int channels;

    if (EngineUtility::LoadImageFromFile(filename, &image))
    {
      m_width = image.m_width;
      m_height = image.m_height;
      m_isHDR = image.m_isHDR;
      channels = image.channels;
      pixels = image.pixels;
    }

    D3D11_TEXTURE2D_DESC descTexture;

    memset(&descTexture, 0, sizeof(descTexture));
    descTexture.Height = static_cast<uint32>(m_height);
    descTexture.Width = static_cast<uint32>(m_width);
    descTexture.MipLevels = 1;
    descTexture.ArraySize = 1;
    descTexture.Format = static_cast<DXGI_FORMAT>(format);
    descTexture.SampleDesc.Count = 1;
    descTexture.SampleDesc.Quality = 0;
    descTexture.Usage = static_cast<D3D11_USAGE>(usage);
    descTexture.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
    descTexture.CPUAccessFlags = static_cast<D3D11_CPU_ACCESS_FLAG>(cpuUsage);
    descTexture.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA initBuffer;
    memset(&initBuffer, 0, sizeof(initBuffer));
    initBuffer.pSysMem = pixels;
    initBuffer.SysMemPitch = m_width * 4;

    hr = m_pDevice.m_pd3dDevice->CreateTexture2D(&descTexture, &initBuffer, &m_pd3dTexture2D);
    if (FAILED(hr)) {
      return false;
    }

    stbi_image_free(pixels);

    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    memset(&srvDesc, 0, sizeof(srvDesc));
    srvDesc.Format = static_cast<DXGI_FORMAT>(format);
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MostDetailedMip = 0;
    srvDesc.Texture2D.MipLevels = -1;

    m_pDevice.m_pd3dDevice->CreateShaderResourceView(m_pd3dTexture2D, &srvDesc, &m_pSRV);

    return true;
  }

  void
  TextureDX::setTextureShaderResource(const Device* pDevice,
                                      uint32 startSlot,
                                      uint32 numViews) {

    const DeviceDX* m_pDevice = static_cast<const DeviceDX*>(pDevice);

    m_pDevice->m_pImmediateContext->PSSetShaderResources(startSlot,
                                                         numViews,
                                                         &m_pSRV);
  }

  void
  TextureDX::releaseTexture() {
    m_pd3dTexture2D->Release();
  }
}
