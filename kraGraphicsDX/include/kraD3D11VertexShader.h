#pragma once
#include "kraPrerequisitesGFX.h"
#include "kraD3D11GraphicsBuffer.h"
#include "kraD3D11Shader.h"
#include "kraD3D11Device.h"

namespace kraEngineSDK {
  class Device;

  class KRA_UTILGFX_EXPORT  VertexShaderDX : public ShaderDX {

  public:
    VertexShaderDX() = default;
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

    ID3DBlob* m_blob = nullptr;
    ID3D11VertexShader* m_pVertexShader;
  };
}
