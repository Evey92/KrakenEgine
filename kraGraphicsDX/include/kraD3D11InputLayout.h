#pragma once
#include <kraInputLayout.h>
#include "kraPrerequisitesGFX.h"


namespace kraEngineSDK {
  class Device;
  class VertexShader;

  class KRA_UTILGFX_EXPORT InputLayoutDX : 
   public InputLayout {

   public:
  
    InputLayoutDX() = default;
    ~InputLayoutDX() {}

   /**
    * @brief Function that creates an input layout by reflecting the shader
    * @param The graphics API device, and a shader
    */
    bool
    createInputLayout(const Device& pd3dDevice, const VertexShader& pVShader);
    
    void
    setInputLayout(const Device& pDevice);
    
    void
    cleanInputLayout();

    void 
    setNullInputLayout(const Device& pDevice) override;


    ID3D11InputLayout* m_pVertexLayout = nullptr;
    std::vector<D3D11_INPUT_ELEMENT_DESC> m_layoutDescVector;
  };
}
