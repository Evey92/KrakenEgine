#pragma once
#include "kraPrerequisitesGFX.h"
#include "kraD3D11Shader.h"
#include "kraD3D11Blob.h"

namespace kraEngineSDK {

  class Device;
  class Blob;

  class KRA_UTILGFX_EXPORT PixelShaderDX :
    public ShaderDX {
   
  public:
    PixelShaderDX() = default;
    ~PixelShaderDX() {}

    bool
    compilePixelShader(const wchar_t* fileName,
                       const char* entryPoint);
    bool
    createPixelShader(Device*  pDevice);
    void
    cleanShader();
    void
    setPixelShader(Device* pDevice);
    BlobDX*
    getBlobasDX();
    
    Blob* m_blob;
    ID3D11PixelShader* m_pPixelShader;
  };
}
