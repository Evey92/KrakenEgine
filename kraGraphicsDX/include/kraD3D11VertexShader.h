#pragma once
#include "kraPrerequisitesGFX.h"
#include "kraD3D11GraphicsBuffer.h"
#include "kraD3D11Shader.h"
#include "kraD3D11Device.h"
#include "kraD3D11Blob.h"

namespace kraEngineSDK {
  class BlobDX;

  class Device;

  class KRA_UTILGFX_EXPORT  VertexShaderDX : public ShaderDX {

  public:
    VertexShaderDX()
    {
      m_blob = getBlobasDX();
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
    BlobDX*
    getBlobasDX();

    Blob* m_blob;
    ID3D11VertexShader* m_pVertexShader;
  };
}
