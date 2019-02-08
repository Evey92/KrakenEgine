#pragma once
#include "kraPrerequisitesGFX.h"
#include "kraD3D11Shader.h"

namespace kraEngineSDK {
  class KRA_UTILGFX_EXPORT PixelShaderDX :
    public ShaderDX {
   
  public:
    PixelShaderDX() = default;
    ~PixelShaderDX() {}

    bool
    compilePixelShader(const wchar_t* fileName,
                       const char* entryPoint);

    bool
    createPixelShader(void*  pDevice);

    void
    cleanShader();
    ID3DBlob* m_blob = nullptr;
    ID3D11PixelShader* m_pPixelShader;
  };
}
