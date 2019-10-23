#pragma once
#include <kraComputeShader.h>

#include "kraPrerequisitesGFX.h"
#include "kraD3D11Shader.h"
#include "kraD3D11Blob.h"

namespace kraEngineSDK {

  class Device;
  class Blob;

  class KRA_UTILGFX_EXPORT ComputeShaderDX :
  public ShaderDX, public ComputeShader {
  
  public:
    virtual bool compileComputeShader(const WString fileName, String entryPoint) override;


    virtual bool createComputeShader(const Device& pDevice) override;

    void
    cleanShader();

    virtual void setComputeShader(const Device& pDevice) override;

    ID3DBlob* m_pBlob = nullptr;
    ID3D11ComputeShader* m_pcomputeShader = nullptr;

  };
}
