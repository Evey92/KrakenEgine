#include "kraD3D11Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace kraEngineSDK {

  Texture::~Texture() {

  }

  void
  Texture::createTexture2D(ID3D11Device* pDevice, int height, int width,
      DXGI_FORMAT format, D3D11_BIND_FLAG bindFlag) {
    D3D11_TEXTURE2D_DESC descTexture;

    memset(&descTexture, 0, sizeof(descTexture));
    descTexture.Height = height;
    descTexture.Width = width;
    descTexture.MipLevels = 1;
    descTexture.ArraySize = 1;
    descTexture.Format = format;
    descTexture.SampleDesc.Count = 1;
    descTexture.SampleDesc.Quality = 0;
    descTexture.Usage = D3D11_USAGE_DEFAULT;
    descTexture.BindFlags = bindFlag;
    descTexture.CPUAccessFlags = 0;
    descTexture.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA initBuffer;
    memset(&initBuffer, 0, sizeof(initBuffer));
    pDevice->CreateTexture2D(&descTexture, &initBuffer, &m_pd3dTexture2D);
  }

  void
  Texture::createTexture2D(ID3D11Device* pDevice, int height, int width,
      DXGI_FORMAT format, D3D11_BIND_FLAG bindFlag,
      D3D11_TEXTURE2D_DESC descTexture) {

    memset(&descTexture, 0, sizeof(descTexture));
    descTexture.Height = height;
    descTexture.Width = width;
    descTexture.MipLevels = 1;
    descTexture.ArraySize = 1;
    descTexture.Format = format;
    descTexture.SampleDesc.Count = 1;
    descTexture.SampleDesc.Quality = 0;
    descTexture.Usage = D3D11_USAGE_DEFAULT;
    descTexture.BindFlags = bindFlag;
    descTexture.CPUAccessFlags = 0;
    descTexture.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA initBuffer;
    memset(&initBuffer, 0, sizeof(initBuffer));
    pDevice->CreateTexture2D(&descTexture, NULL, &m_pd3dTexture2D);
  }

  HRESULT
  Texture::createTexture2DFromFile(ID3D11Device* pDevice, const char*  filename,
                                   DXGI_FORMAT format, D3D11_BIND_FLAG bindFlag) {
    
    HRESULT hr = S_OK;
    int channels;

    auto image = stbi_load(filename, &m_width, &m_height, &channels, 4);

    if (!image)
    {
      throw std::exception("Texture couldn't be loaded." );
      stbi_image_free(image);
      image = stbi_load(m_missingTexture, &m_width, &m_height, &channels, 4);
    }

    D3D11_TEXTURE2D_DESC descTexture;

    memset(&descTexture, 0, sizeof(descTexture));
    descTexture.Height = m_height;
    descTexture.Width = m_width;
    descTexture.MipLevels = 1;
    descTexture.ArraySize = 1;
    descTexture.Format = format;
    descTexture.SampleDesc.Count = 1;
    descTexture.SampleDesc.Quality = 0;
    descTexture.Usage = D3D11_USAGE_DEFAULT;
    descTexture.BindFlags = bindFlag;
    descTexture.CPUAccessFlags = 0;
    descTexture.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA initBuffer;
    memset(&initBuffer, 0, sizeof(initBuffer));
    initBuffer.pSysMem = image;
    initBuffer.SysMemPitch = m_width * 4;

    pDevice->CreateTexture2D(&descTexture, &initBuffer, &m_pd3dTexture2D);
    if (FAILED(hr)) {
      return hr;
    }

    stbi_image_free(image);

    return hr;
  }

  void
  Texture::releaseTexture() {
    m_pd3dTexture2D->Release();
  }
}
