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
    virtual bool
    compileComputeShader(const WString fileName, String entryPoint) override;

    virtual bool 
    createComputeShader(const Device& pDevice) override;
    
    void
    cleanShader();

    virtual void 
    setComputeShader(const Device& pDevice) override;

    virtual void 
    dispatchCS(const Device& pDevice, 
               uint32 threadCountX,
               uint32 threadCountY,
               uint32 threadCountZ) override;
    
 
    ID3D11ComputeShader* m_pcomputeShader = nullptr;

  };
}
