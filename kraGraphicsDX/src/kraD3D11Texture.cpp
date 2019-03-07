#include <kraDevice.h>
#include "kraD3D11Texture.h"
#include "kraD3D11Device.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace kraEngineSDK {

  void
  TextureDX::createTexture2D(Device* pDevice, int height, int width,
                             void* format, void* bindFlag) {

    DeviceDX* m_pDevice = static_cast<DeviceDX*>(pDevice);
    DXGI_FORMAT* m_format = static_cast<DXGI_FORMAT*>(format);
    D3D11_BIND_FLAG* m_bindFlag = static_cast<D3D11_BIND_FLAG*>(bindFlag);

    D3D11_TEXTURE2D_DESC descTexture;
    memset(&descTexture, 0, sizeof(descTexture));
    descTexture.Height = height;
    descTexture.Width = width;
    descTexture.MipLevels = 1;
    descTexture.ArraySize = 1;
    descTexture.Format = *m_format;
    descTexture.SampleDesc.Count = 1;
    descTexture.SampleDesc.Quality = 0;
    descTexture.Usage = D3D11_USAGE_DEFAULT;
    descTexture.BindFlags = *m_bindFlag;
    descTexture.CPUAccessFlags = 0;
    descTexture.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA initBuffer;
    memset(&initBuffer, 0, sizeof(initBuffer));
    m_pDevice->m_pd3dDevice->CreateTexture2D(&descTexture, &initBuffer, &m_pd3dTexture2D);
  }

  void
  TextureDX::createTexture2D(void* pDevice, int height, int width,
      void* format, void* bindFlag,
      void*  descTexture) {

    ID3D11Device* m_pDevice = static_cast<ID3D11Device*>(pDevice);
    DXGI_FORMAT* m_format = static_cast<DXGI_FORMAT*>(format);
    D3D11_BIND_FLAG* m_bindFlag = static_cast<D3D11_BIND_FLAG*>(bindFlag);
    D3D11_TEXTURE2D_DESC* m_desc = static_cast<D3D11_TEXTURE2D_DESC*>(descTexture);


    memset(&m_desc, 0, sizeof(m_desc));
    m_desc->Height = height;
    m_desc->Width = width;
    m_desc->MipLevels = 1;
    m_desc->ArraySize = 1;
    m_desc->Format = *m_format;
    m_desc->SampleDesc.Count = 1;
    m_desc->SampleDesc.Quality = 0;
    m_desc->Usage = D3D11_USAGE_DEFAULT;
    m_desc->BindFlags = *m_bindFlag;
    m_desc->CPUAccessFlags = 0;
    m_desc->MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA initBuffer;
    memset(&initBuffer, 0, sizeof(initBuffer));
    m_pDevice->CreateTexture2D(m_desc, NULL, &m_pd3dTexture2D);
  }

  bool
  TextureDX::createTexture2DFromFile(void* pDevice, const char*  filename,
                                    void* format, void* bindFlag) {
    
    ID3D11Device* m_pDevice = static_cast<ID3D11Device*>(pDevice);
    DXGI_FORMAT* m_fomrat = static_cast<DXGI_FORMAT*>(format);
    D3D11_BIND_FLAG* m_bindFlag = static_cast<D3D11_BIND_FLAG*>(bindFlag);

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
    descTexture.Format = *m_fomrat;
    descTexture.SampleDesc.Count = 1;
    descTexture.SampleDesc.Quality = 0;
    descTexture.Usage = D3D11_USAGE_DEFAULT;
    descTexture.BindFlags = *m_bindFlag;
    descTexture.CPUAccessFlags = 0;
    descTexture.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA initBuffer;
    memset(&initBuffer, 0, sizeof(initBuffer));
    initBuffer.pSysMem = image;
    initBuffer.SysMemPitch = m_width * 4;

    m_pDevice->CreateTexture2D(&descTexture, &initBuffer, &m_pd3dTexture2D);
    if (FAILED(hr)) {
      return hr;
    }

    stbi_image_free(image);

    return hr;
  }

  void
  TextureDX::releaseTexture() {
    m_pd3dTexture2D->Release();
  }
}
