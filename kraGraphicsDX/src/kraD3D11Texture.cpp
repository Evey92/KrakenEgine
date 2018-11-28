#include "kraD3D11Texture.h"


namespace kraEngineSDK {

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
    pDevice->CreateTexture2D(&descTexture, &initBuffer, &m_pd3dTexture2D);
  }

  void
    Texture::createTexture2DFromFile(ID3D11Device* pDevice, std::string  filename,
      DXGI_FORMAT format, D3D11_BIND_FLAG bindFlag) {

    int width, height, channels;
  
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
    Texture::releaseTexture() {
    m_pd3dTexture2D->Release();
  }
}
