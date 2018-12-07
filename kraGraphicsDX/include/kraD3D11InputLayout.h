#pragma once
#include "kraD3D11GraphicsBuffer.h"
#include "kraD3D11VertexShader.h"

namespace kraEngineSDK {
  class  InputLayout
  {
  public:
    InputLayout() = default;
    ~InputLayout() {};

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
      createInputLayout(ID3D11Device* pd3dDevice, VertexShader* pVShader);
    void
      setInputLayout(ID3D11DeviceContext* pDeviceContext);
    void
      cleanInputLayout();

    std::vector<D3D11_INPUT_ELEMENT_DESC> layoutDescVector;
    ID3D11InputLayout* m_pVertexLayout;
  };
}
