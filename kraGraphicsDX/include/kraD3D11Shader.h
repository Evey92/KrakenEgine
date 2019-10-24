#pragma once
#include <d3dcompiler.h>
#include <kraShader.h>

#include "kraPrerequisitesGFX.h"


namespace kraEngineSDK {
  class Blob;

  class KRA_UTILGFX_EXPORT ShaderDX : public Shader
  {
  public:

    ShaderDX() = default;
    ~ShaderDX() {}

    bool
    compileShaderFromFile(const WString filename,
                          String entryPoint,
                          String shaderModel) override;
    /*virtual void
    cleanShader();*/
    ID3DBlob* m_pBlob = nullptr;

  };
}

