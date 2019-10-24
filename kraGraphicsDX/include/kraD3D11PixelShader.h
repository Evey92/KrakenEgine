#pragma once
#include <kraPixelShader.h>

#include "kraPrerequisitesGFX.h"
#include "kraD3D11Shader.h"
#include "kraD3D11Blob.h"

namespace kraEngineSDK {

  class Device;
  class Blob;

  class KRA_UTILGFX_EXPORT PixelShaderDX :
    public ShaderDX, public PixelShader {
   
  public:
    PixelShaderDX() = default;
    ~PixelShaderDX() {}

    bool
    compilePixelShader(const WString fileName,
                       String entryPoint);
    bool
    createPixelShader(const Device&  pDevice);
    void
    cleanShader();

    void
    setPixelShader(const Device& pDevice);
 
    /*bool
    compileShaderFromFile(std::string filename,
                          std::string entryPoint,
                          std::string shaderModel,
                          ID3DBlob** ppBlobOut);*/

    
    //Blob* m_blob;
    ID3D11PixelShader* m_pPixelShader = nullptr;
  };
}
