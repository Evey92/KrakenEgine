#pragma once
#include "kraPrerequisitesGFX.h"
#include "kraD3D11GraphicsBuffer.h"
#include "kraD3D11Shader.h"

namespace kraEngineSDK {
  class PixelShader : 
    public Shader {
   
  public:
    HRESULT
      compilePixelShader(const wchar_t* fileName,
        const char* entryPoint);

    HRESULT
      createPixelShader(ID3D11Device* pDevice);

    ID3DBlob* m_blob;
    ID3D11PixelShader* m_pPixelShader;
  };

  HRESULT
    PixelShader::compilePixelShader(const wchar_t* fileName,
      const char* entryPoint) {
    HRESULT hr = S_OK;

    hr = compileShaderFromFile(fileName, entryPoint, "vs_5_0", &m_blob);

    if (FAILED(hr))
    {
      return hr;
    }
  }

  HRESULT
    PixelShader::createPixelShader(ID3D11Device* pDevice) {

    HRESULT hr = S_OK;
    hr = pDevice->CreatePixelShader(m_blob->GetBufferPointer(),
      m_blob->GetBufferSize(),
      NULL, &m_pPixelShader);
    if (FAILED(hr))
    {
      m_blob->Release();
      return hr;
    }
  }

}