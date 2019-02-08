#pragma once
#include <kraInputLayout.h>

#include "kraPrerequisitesGFX.h"
#include "kraD3D11VertexShader.h"

namespace kraEngineSDK {
  class KRA_UTILGFX_EXPORT InputLayoutDX : public InputLayout
  {
  public:
  
    InputLayoutDX() = default;
    ~InputLayoutDX() {}

    void
    defineInputLayout();
    void
    defineVertexLayout();
    void
    defineIndexLayout();
    void
    defineNormalLayout();
    void
    defineTexcoordLayout();
    void
    createInputLayout(void* pd3dDevice, void* pVShader);
    void
    setInputLayout(void* pDeviceContext);
    void
    cleanInputLayout();

    std::vector<D3D11_INPUT_ELEMENT_DESC> layoutDescVector;
    ID3D11InputLayout* m_pVertexLayout;
  };
}
