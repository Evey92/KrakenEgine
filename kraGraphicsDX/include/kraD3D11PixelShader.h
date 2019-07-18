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
    compilePixelShader(std::string fileName,
                       const char* entryPoint);
    bool
    createPixelShader(const Device&  pDevice);
    void
    cleanShader();
    void
    setPixelShader(const Device& pDevice);
    /*BlobDX*
    getBlobasDX();
    */
    bool
    compileShaderFromFile(std::string filename,
                          std::string entryPoint,
                          std::string shaderModel,
                          ID3DBlob** ppBlobOut);

    ID3DBlob* m_pBlob = nullptr;
    //Blob* m_blob;
    ID3D11PixelShader* m_pPixelShader = nullptr;
  };
}
