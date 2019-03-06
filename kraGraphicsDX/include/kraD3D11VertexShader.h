#pragma once
#include <kraVertexShader.h>

#include "kraPrerequisitesGFX.h"
#include "kraD3D11GraphicsBuffer.h"
#include "kraD3D11Shader.h"
#include "kraD3D11Device.h"
#include "kraD3D11Blob.h"

namespace kraEngineSDK {
  class BlobDX;
  class Device;

  class KRA_UTILGFX_EXPORT  VertexShaderDX :
  public ShaderDX,  public VertexShader {

  public:
    VertexShaderDX()
    {
      //m_blob = new BlobDX();
    }
    ~VertexShaderDX() {}

    bool
    compileVertexShader(const wchar_t* fileName,
                        const char* entryPoint);
    bool
    createVertexShader(Device* pDevice);
    void 
    cleanShader();
    void
    setVertexShader(Device* pDevice);
    /*BlobDX*
    getBlobasDX();*/

    bool
    compileShaderFromFile(const wchar_t* filename,
        std::string entryPoint,
        std::string shaderModel,
      ID3DBlob** ppBlobOut);

    ID3DBlob* m_pBlob;
    //Blob* m_blob;
    ID3D11VertexShader* m_pVertexShader;
  };
}
