#include "kraD3D11InputLayout.h"
#include <kraDevice.h>
#include <kraVertexShader.h>
#include "kraD3D11Device.h"
#include "kraD3D11VertexShader.h"
#include "kraD3D11Blob.h"

namespace kraEngineSDK {

  /*
   * @brief Function to define full Input Layout
   */
  void
    InputLayoutDX::defineInputLayout() {

    D3D11_INPUT_ELEMENT_DESC inputDesc;
    /*
    * @brief Vertex layout
    */
    memset(&inputDesc, 0, sizeof(D3D11_INPUT_ELEMENT_DESC));
    inputDesc.SemanticName = "POSIITION";
    inputDesc.SemanticIndex = 0;
    inputDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
    inputDesc.InputSlot = 0;
    inputDesc.AlignedByteOffset = 0;
    inputDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    inputDesc.InstanceDataStepRate = 0;
    layoutDescVector.push_back(inputDesc);

    /*
    * @brief Index layout
    */
    memset(&inputDesc, 0, sizeof(D3D11_INPUT_ELEMENT_DESC));
    inputDesc.SemanticName = "COLOR";
    inputDesc.SemanticIndex = 0;
    inputDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    inputDesc.InputSlot = 0;
    inputDesc.AlignedByteOffset = 16;
    inputDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    inputDesc.InstanceDataStepRate = 0;
    layoutDescVector.push_back(inputDesc);

    /*
    * @brief Normal layout
    */
    memset(&inputDesc, 0, sizeof(D3D11_INPUT_ELEMENT_DESC));
    inputDesc.SemanticName = "NORMAL";
    inputDesc.SemanticIndex = 0;
    inputDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    inputDesc.InputSlot = 0;
    inputDesc.AlignedByteOffset = 32;
    inputDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    inputDesc.InstanceDataStepRate = 0;
    layoutDescVector.push_back(inputDesc);

    /*
    * @brief TEXCOORD layout
    */
    memset(&inputDesc, 0, sizeof(D3D11_INPUT_ELEMENT_DESC));
    inputDesc.SemanticName = "TEXCOORD";
    inputDesc.SemanticIndex = 0;
    inputDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
    inputDesc.InputSlot = 0;
    inputDesc.AlignedByteOffset = 12;
    inputDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    inputDesc.InstanceDataStepRate = 0;
    layoutDescVector.push_back(inputDesc);

  }

  /*
   * @brief Define Vertex layout
   */
  void
  InputLayoutDX::defineVertexLayout() {
    D3D11_INPUT_ELEMENT_DESC inputDesc;
    memset(&inputDesc, 0, sizeof(D3D11_INPUT_ELEMENT_DESC));
    inputDesc.SemanticName = "POSITION";
    inputDesc.SemanticIndex = 0;
    inputDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
    inputDesc.InputSlot = 0;
    inputDesc.AlignedByteOffset = 0;
    inputDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    inputDesc.InstanceDataStepRate = 0;
    layoutDescVector.push_back(inputDesc);
  }

  /*
   * @brief Define Vertex layout
   */
  void
  InputLayoutDX::defineIndexLayout() {
    D3D11_INPUT_ELEMENT_DESC inputDesc;
    memset(&inputDesc, 0, sizeof(D3D11_INPUT_ELEMENT_DESC));
    inputDesc.SemanticName = "COLOR";
    inputDesc.SemanticIndex = 0;
    inputDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    inputDesc.InputSlot = 0;
    inputDesc.AlignedByteOffset = 16;
    inputDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    inputDesc.InstanceDataStepRate = 0;
    layoutDescVector.push_back(inputDesc);
  }

  /*
   * @brief Define Vertex layout
   */
  void
  InputLayoutDX::defineNormalLayout() {
    D3D11_INPUT_ELEMENT_DESC inputDesc;
    memset(&inputDesc, 0, sizeof(D3D11_INPUT_ELEMENT_DESC));
    inputDesc.SemanticName = "NORMAL";
    inputDesc.SemanticIndex = 0;
    inputDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    inputDesc.InputSlot = 0;
    inputDesc.AlignedByteOffset = 32;
    inputDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    inputDesc.InstanceDataStepRate = 0;
    layoutDescVector.push_back(inputDesc);
  }

  /*
   * @brief Define Vertex layout
   */
  void
  InputLayoutDX::defineTexcoordLayout() {
    D3D11_INPUT_ELEMENT_DESC inputDesc;
    memset(&inputDesc, 0, sizeof(D3D11_INPUT_ELEMENT_DESC));
    inputDesc.SemanticName = "TEXCOORD";
    inputDesc.SemanticIndex = 0;
    inputDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
    inputDesc.InputSlot = 0;
    inputDesc.AlignedByteOffset = 12;
    inputDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    inputDesc.InstanceDataStepRate = 0;
    layoutDescVector.push_back(inputDesc);
  }

  void
  InputLayoutDX::createInputLayout(const Device& pDevice, const VertexShader& pVShader) {

    const DeviceDX& m_pDevice = reinterpret_cast<const DeviceDX&>(pDevice);
    const VertexShaderDX& m_pVShader = reinterpret_cast<const VertexShaderDX&>(pVShader);
    //BlobDX* myBlob = reinterpret_cast<BlobDX*>(m_pVShader->m_blob);
    
    m_pDevice.m_pd3dDevice->CreateInputLayout(&layoutDescVector[0], 
                                               static_cast<uint32>(layoutDescVector.size()), 
                                               m_pVShader.m_pBlob->GetBufferPointer(),
                                               m_pVShader.m_pBlob->GetBufferSize(),
                                               &m_pVertexLayout);
    
  }

  void
  InputLayoutDX::setInputLayout(Device* pDevice) {

    DeviceDX* m_pDevice = reinterpret_cast<DeviceDX*>(pDevice);

    m_pDevice->m_pImmediateContext->IASetInputLayout(m_pVertexLayout);
    
  }

  void
  InputLayoutDX::cleanInputLayout() {
    m_pVertexLayout->Release();
  }
}
