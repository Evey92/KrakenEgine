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
  TextureDX::createCubeTexture(const Device& pDevice,
                               uint32 height,
                               uint32 width,
                               GFX_FORMAT::E format,
                               GFX_USAGE::E usage = GFX_USAGE::E::kUSAGE_DEFAULT,
                               uint32 levels = 0U) {

    const DeviceDX& m_pDevice = static_cast<const DeviceDX&>(pDevice);

    m_height = height;
    m_width = width;
    m_levels = (levels > 0) ? levels : EngineUtility::numMipLevels(width, height);

    D3D11_TEXTURE2D_DESC descTexture;
    memset(&descTexture, 0, sizeof(descTexture));
    descTexture.Width = width;
    descTexture.Height = height;
    descTexture.MipLevels = levels;
    descTexture.ArraySize = 6;
    descTexture.Format = static_cast<DXGI_FORMAT>(format);
    descTexture.SampleDesc.Count = 1;
    descTexture.Usage = static_cast<D3D11_USAGE>(usage);
    descTexture.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
    descTexture.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;
    
    if (levels == 0) {
      descTexture.BindFlags |= D3D11_BIND_RENDER_TARGET;
      descTexture.MiscFlags |= D3D11_RESOURCE_MISC_GENERATE_MIPS;
    }

    if (FAILED(m_pDevice.m_pd3dDevice->CreateTexture2D(&descTexture, nullptr, &m_pd3dTexture2D))) {
      std::cout << "Failed to create Cubemap texture\n";
    }

    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    memset(&srvDesc, 0, sizeof(srvDesc));
    srvDesc.Format = descTexture.Format;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
    srvDesc.Texture2D.MostDetailedMip = 0;
    srvDesc.Texture2D.MipLevels = -1;

    if (FAILED(m_pDevice.m_pd3dDevice->CreateShaderResourceView(m_pd3dTexture2D, &srvDesc, &m_pSRV))) {
      std::cout << "Failed to create Cubemap Shader Resource View\n";

    }
  }

 
  void 
  TextureDX::createTexture2D(const Device& pDevice,
                             uint32 height,
                             uint32 width,
                             GFX_FORMAT::E format ,
                             GFX_USAGE::E usage = GFX_USAGE::E::kUSAGE_DEFAULT,
                             uint32 levels = 0U)
  {

    const DeviceDX& m_pDevice = static_cast<const DeviceDX&>(pDevice);

    m_height = height;
    m_width = width;
    m_levels = levels;

    D3D11_TEXTURE2D_DESC descTexture;
    memset(&descTexture, 0, sizeof(descTexture));
    descTexture.Width = width;
    descTexture.Height = height;
    descTexture.MipLevels = levels;
    descTexture.ArraySize = 1;
    descTexture.Format = static_cast<DXGI_FORMAT>(format);

    descTexture.SampleDesc.Count = 1;
    descTexture.Usage = static_cast<D3D11_USAGE>(usage);
    descTexture.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
    if (levels == 0) {
      descTexture.BindFlags |= D3D11_BIND_RENDER_TARGET;
      descTexture.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;
    }

    if (FAILED(m_pDevice.m_pd3dDevice->CreateTexture2D(&descTexture, nullptr, &m_pd3dTexture2D))) {
      std::cout << "Failed to create 2D texture\n";
    }

    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    memset(&srvDesc, 0, sizeof(srvDesc));
    srvDesc.Format = static_cast<DXGI_FORMAT>(format);
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MostDetailedMip = 0;
    srvDesc.Texture2D.MipLevels = -1;

    if (FAILED(m_pDevice.m_pd3dDevice->CreateShaderResourceView(m_pd3dTexture2D, &srvDesc, &m_pSRV))) {
      std::cout << "Failed to create Shader Resource View\n";

    }
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
                                     CPU_USAGE::E cpuUsage,
                                     int _channels,
                                     uint32 levels)
  {
    const DeviceDX& m_pDevice = static_cast<const DeviceDX&>(pDevice);

    HRESULT hr = S_OK;

   //ShrdPtr<Image> image = Image::LoadImageFromFile("resources/Textures/default.png", _channels);
    ShrdPtr<Image> image = Image::LoadImageFromFile(filename, _channels);

    if (image != nullptr)
    {
      m_width = image->getWidth();
      m_height = image->getHeight();
      m_isHDR = image->isHDR();
    }
    else
    {
      std::cout << "There was an error while loading the file." << std::endl;
      //ShrdPtr<Image> image = Image::LoadImageFromFile(filename, _channels);
      //m_width = image->getWidth();
      //m_height = image->getHeight();
      //m_isHDR = image->isHDR();

      return false;
    }

    m_levels = (levels > 0) ? levels : EngineUtility::numMipLevels(m_width, m_height);
   
    D3D11_TEXTURE2D_DESC descTexture;
    memset(&descTexture, 0, sizeof(descTexture));

    descTexture.Height = static_cast<uint32>(m_height);
    descTexture.Width = static_cast<uint32>(m_width);
    descTexture.MipLevels = levels;
    descTexture.ArraySize = 1;
    descTexture.Format = static_cast<DXGI_FORMAT>(format);
    descTexture.SampleDesc.Count = 1;
    descTexture.Usage = static_cast<D3D11_USAGE>(usage);
    descTexture.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
    if (levels == 0) {
      descTexture.BindFlags |= D3D11_BIND_RENDER_TARGET;
      descTexture.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;
    }

    D3D11_SUBRESOURCE_DATA initBuffer;
    memset(&initBuffer, 0, sizeof(initBuffer));
    initBuffer.pSysMem = image->getPixels<void>();
    initBuffer.SysMemPitch = image->getPitch();
    initBuffer.SysMemSlicePitch = 0;

    hr = m_pDevice.m_pd3dDevice->CreateTexture2D(&descTexture, nullptr, &m_pd3dTexture2D);
    if (FAILED(hr)) {
      return false;
    }

    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    memset(&srvDesc, 0, sizeof(srvDesc));
    srvDesc.Format = static_cast<DXGI_FORMAT>(format);
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MostDetailedMip = 0;
    srvDesc.Texture2D.MipLevels = -1;

    m_pDevice.m_pd3dDevice->CreateShaderResourceView(m_pd3dTexture2D, &srvDesc, &m_pSRV);


    m_pDevice.m_pImmediateContext->UpdateSubresource(m_pd3dTexture2D, 0, nullptr, image->getPixels<void>(), image->getPitch(), 0);

    return true;
  }

  void TextureDX::createTextureUAV(const Device& pDevice, uint32 mipSlice)
  {
    assert(m_pd3dTexture2D);
    const DeviceDX& m_pDevice = static_cast<const DeviceDX&>(pDevice);

    D3D11_TEXTURE2D_DESC descTexture;
    memset(&descTexture, 0, sizeof(descTexture));

    m_pd3dTexture2D->GetDesc(&descTexture);

    D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc;
    memset(&uavDesc, 0, sizeof(uavDesc));

    uavDesc.Format = descTexture.Format;
    if (descTexture.ArraySize == 1) {
      uavDesc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2D;
      uavDesc.Texture2D.MipSlice = mipSlice;
    }
    else {
      uavDesc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2DARRAY;
      uavDesc.Texture2DArray.MipSlice = mipSlice;
      uavDesc.Texture2DArray.FirstArraySlice = 0;
      uavDesc.Texture2DArray.ArraySize = descTexture.ArraySize;
    }

    if (FAILED(m_pDevice.m_pd3dDevice->CreateUnorderedAccessView(m_pd3dTexture2D, &uavDesc, &m_UAV))) {
      std::cout << "Failed to create texture UAV\n";
    }

  }

  void
  TextureDX::setTextureShaderResource(const Device& pDevice,
                                      uint32 startSlot,
                                      uint32 numViews) {

    const DeviceDX& m_pDevice = static_cast<const DeviceDX&>(pDevice);

    m_pDevice.m_pImmediateContext->PSSetShaderResources(startSlot,
                                                         numViews,
                                                         &m_pSRV);
  }


  void
  TextureDX::setTextureComputeShaderResource(const Device& pDevice,
                                             uint32 startSlot,
                                             uint32 numViews) {

    const DeviceDX& m_pDevice = static_cast<const DeviceDX&>(pDevice);
    m_pDevice.m_pImmediateContext->CSSetShaderResources(startSlot,
                                                         numViews,
                                                         &m_pSRV);
  }

  void 
  TextureDX::setPSTextureShaderResources(const Device& pDevice, 
                                         uint32 startSlot,
                                         uint32 numViews,
                                         Vector<ShrdPtr<Texture>> shaderResources)
  {
    const DeviceDX& m_pDevice = static_cast<const DeviceDX&>(pDevice);
    Vector<ID3D11ShaderResourceView*> shdrVec;

    for (auto tex : shaderResources) {

      const TextureDX& texDx = reinterpret_cast<const TextureDX&>(shaderResources);
      shdrVec.push_back(texDx.m_pSRV);
    }

    m_pDevice.m_pImmediateContext->PSSetShaderResources(startSlot,
                                                         numViews,
                                                         &shdrVec[0]);
  }

  void
  TextureDX::setTextureUnorderedAccesVews(const Device& pDevice, 
                                          uint32 startSlot,
                                          uint32 numViews)
  {
    const DeviceDX& m_pDevice = static_cast<const DeviceDX&>(pDevice);
    m_pDevice.m_pImmediateContext->CSSetUnorderedAccessViews(startSlot,
                                                              numViews,
                                                              &m_UAV,
                                                              nullptr);
  }

  void
  TextureDX::setComputeNullUAV(const Device& pDevice)
  {
    const DeviceDX& m_pDevice = static_cast<const DeviceDX&>(pDevice);
    m_UAV = nullptr;
    m_pDevice.m_pImmediateContext->CSSetUnorderedAccessViews(0, 1, &m_UAV, nullptr);
  }

  uint32 
  TextureDX::getHeight()
  {
    return m_height;
  }

  uint32 
  TextureDX::getWidth()
  {
    return m_width;
  }

  uint32
  TextureDX::getLevels()
  {
    return m_levels;
  }

  bool
  TextureDX::isHDR()
  { 
    return m_isHDR;
  }

  void
  TextureDX::releaseTexture() {
    m_pd3dTexture2D->Release();
  } 

  

  void* TextureDX::getShaderResourceView()
  {
    return m_pSRV;
  }

  void TextureDX::generateMips()
  {
    //do
  }

}
