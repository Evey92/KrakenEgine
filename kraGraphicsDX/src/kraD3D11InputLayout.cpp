#include "kraD3D11InputLayout.h"
#include <kraDevice.h>
#include <kraVertexShader.h>
#include "kraD3D11Device.h"
#include "kraD3D11VertexShader.h"
#include "kraD3D11Blob.h"

namespace kraEngineSDK {

  bool
  InputLayoutDX::createInputLayout(const Device& pDevice, const VertexShader& pVShader) {

    HRESULT hr = S_OK;

    m_layoutDescVector.clear();

    const DeviceDX& m_pDevice = static_cast<const DeviceDX&>(pDevice);
    const VertexShaderDX& m_pVShader = static_cast<const VertexShaderDX&>(pVShader);
    ID3DBlob* pShaderBlob = m_pVShader.m_pBlob;

    //Reflect the shader into pShaderReflection
    ID3D11ShaderReflection* pShaderReflection = nullptr;
    if (FAILED(D3DReflect(pShaderBlob->GetBufferPointer(),
                          pShaderBlob->GetBufferSize(),
                          IID_ID3D11ShaderReflection,
                          (void**)&pShaderReflection))) {

      return false;
    }

    //Get shader description
    D3D11_SHADER_DESC shaderDesc;
    pShaderReflection->GetDesc(&shaderDesc);

    for (uint32 i = 0; i < shaderDesc.InputParameters; i++) {
      
      D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
      pShaderReflection->GetInputParameterDesc(i, &paramDesc);

      D3D11_INPUT_ELEMENT_DESC elementDesc;
      elementDesc.SemanticName = paramDesc.SemanticName;
      elementDesc.SemanticIndex = paramDesc.SemanticIndex;
      elementDesc.InputSlot = 0;
      elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
      elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
      elementDesc.InstanceDataStepRate = 0;

      // determine DXGI format
      if (paramDesc.Mask == 1)
      {
        if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32_UINT;
        else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32_SINT;
        else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
      }
      else if (paramDesc.Mask <= 3)
      {
        if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
        else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
        else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
      }
      else if (paramDesc.Mask <= 7)
      {
        if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
        else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
        else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
      }
      else if (paramDesc.Mask <= 15)
      {
        if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
        else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
        else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
      }

      m_layoutDescVector.push_back(elementDesc);
    }

    hr = m_pDevice.m_pd3dDevice->CreateInputLayout(&m_layoutDescVector[0],
                                                    m_layoutDescVector.size(), 
                                                    m_pVShader.m_pBlob->GetBufferPointer(),
                                                    m_pVShader.m_pBlob->GetBufferSize(),
                                                    &m_pVertexLayout);
    pShaderReflection->Release();

    if (FAILED(hr))
    {
      MessageBox(NULL, "Failed to create Input Layout", "Error", MB_OK);
      return false;
    }
    return true;
    
  }

  void
  InputLayoutDX::setInputLayout(const Device& pDevice) {

    const DeviceDX& m_pDevice = static_cast<const DeviceDX&>(pDevice);

    m_pDevice.m_pImmediateContext->IASetInputLayout(m_pVertexLayout);
    
  }

  void InputLayoutDX::setNullInputLayout(const Device& pDevice)
  {
    const DeviceDX& m_pDevice = static_cast<const DeviceDX&>(pDevice);

    m_pDevice.m_pImmediateContext->IASetInputLayout(nullptr);
  }

  void
  InputLayoutDX::cleanInputLayout() {
    m_pVertexLayout->Release();
  }
}
