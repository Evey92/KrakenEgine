#pragma once
#include "kraPrerequisitesGFX.h"
#include "kraD3D11GraphicsBuffer.h"
#include "kraD3D11Shader.h"

namespace kraEngineSDK {
  class  PixelShader :
    public Shader {
   
  public:
    PixelShader() = default;
    ~PixelShader() {};

    HRESULT
    compilePixelShader(const wchar_t* fileName,
                       const char* entryPoint);

    HRESULT
    createPixelShader(ID3D11Device* pDevice);

    void
    cleanShader();
    ID3DBlob* m_blob = nullptr;
    ID3D11PixelShader* m_pPixelShader;
  };
}
