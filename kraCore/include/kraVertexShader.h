#pragma once
#include "kraPrerequisitesCore.h"
#include "kraGraphicsBuffer.h"
#include "kraShader.h"

namespace kraEngineSDK {
  class KRA_CORE_EXPORT  VertexShader :
    public Shader {

  public:
    VertexShader() = default;
    virtual
    ~VertexShader() {}

    virtual bool
      compileVertexShader(const wchar_t* fileName,
        const char* entryPoint) = 0;

    virtual bool
    createVertexShader(void* pDevice) = 0;

    virtual void
    cleanShader() = 0;
    void* m_blob = nullptr;
    void* m_pVertexShader;
  };
}