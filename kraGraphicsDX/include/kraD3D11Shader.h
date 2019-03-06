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

    /*bool
    compileShaderFromFile(const wchar_t* filename,
                                  std::string entryPoint,
                                  std::string shaderModel,
                                  Blob* ppBlobOut);*/
    /*virtual void
    cleanShader();*/
  };
}

