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
      m_pBlob = nullptr;
    }
    ~VertexShaderDX() {}

    bool
    compileVertexShader(const WString fileName,
                        String entryPoint);

    bool
    createVertexShader(const Device& pDevice);
    void 
    cleanShader();
    void
    setVertexShader(const Device& pDevice);

    ID3D11VertexShader* m_pVertexShader = nullptr;
  };
}
