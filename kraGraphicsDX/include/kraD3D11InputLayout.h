#pragma once
#include <kraInputLayout.h>
#include "kraPrerequisitesGFX.h"


namespace kraEngineSDK {
  class Device;
  class VertexShader;

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
    bool
    createInputLayout(const Device& pd3dDevice, const VertexShader& pVShader);
    void
    setInputLayout(const Device& pDevice);
    void
    cleanInputLayout();

    ID3D11InputLayout* m_pVertexLayout;
    std::vector<D3D11_INPUT_ELEMENT_DESC> m_layoutDescVector;
    
  };
}
