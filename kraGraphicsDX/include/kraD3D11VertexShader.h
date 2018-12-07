#pragma once
#include "kraPrerequisitesGFX.h"
#include "kraD3D11GraphicsBuffer.h"
#include "kraD3D11Shader.h"

namespace kraEngineSDK {
  class  VertexShader :
    public Shader  {

  public:
    VertexShader() = default;
    ~VertexShader() {};

    HRESULT
    compileVertexShader(const wchar_t* fileName,
                        const char* entryPoint);

    HRESULT
    createVertexShader(ID3D11Device* pDevice);

    void 
    cleanShader();
    ID3DBlob* m_blob = nullptr;
    ID3D11VertexShader* m_pVertexShader;
  };
}
