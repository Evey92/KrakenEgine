#pragma once
#include "kraGraphicsBuffer.h"

namespace kraEngineSDK {

  template <typename TCONSTANT>
  class kraConstantBuffer : public kraGraphicsBuffer
  {
  
   public:
    kraConstantBuffer(){}
    ~kraConstantBuffer() { clearBuffer(); }

    /**
     * @brief Creates an Index buffer.
     * @param A pointer to the device, and a flag for usage.
     */
    void
    createConstantBuffer(ID3D11Device* pd3dDevice, D3D11_USAGE usage = D3D11_USAGE_DEFAULT) {
      D3D11_BUFFER_DESC bd;
      memset(&bd, 0, sizeof(bd));

      bd.Usage = usage;
      bd.ByteWidth = static_cast<uint32_t>(sizeof(TCONSTANT)*m_constantData.size()); // TODO: Make it use My own Uint32 type
      bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
      bd.CPUAccessFlags = 0;

      D3D11_SUBRESOURCE_DATA InitData;
      memset(&InitData, 0, sizeof(InitData));
      InitData.pSysMem = &m_constantData[0];

      HRESULT hr = pd3dDevice->CreateBuffer(&bd, &InitData, &m_pBuffer);
      if (FAILED(hr))
      {
        throw std::exception("Failed to create Constant Buffer");
      }
    }

    /**
    * @brief Reserves memory using the size of the object containing the constants.
    * @param the size of the object containing the vertexes .
    */
    void
    reserve(size_t numObjects) {
      m_constantData.reserve(numObjects);
    }

    /**
    * @brief Adds a single constant to the buffer.
    * @param the address of the constant.
    */
    void
    add(const TCONSTANT& vertex) {
      m_constantData.push_back(vertex);
    }
    /**
    * @brief Copies a whole constant vector into the buffer.
    * @param the vector containing the constants.
    */
    void
    add(const std::vector<TCONSTANT>& vertices) {
      m_constantData.insert(m_constantData.end(), vertices.begin(), vertices.end());
    }

    /**
    * @brief Adds multiple constants onto the buffer.
    * @param A pointer to the start position and the number of constants.
    */
    void
    add(const TCONSTANT* pindexes, size_t numIndexes) {

      m_constantData.insert(m_constantData.end(),
        pindexes,
        pindexes +
        numIndexes);
    }

    /**
    * @brief Cleans the constant buffer.
    */
    void
    clearBuffer() {
      m_constantData.clear();
    }

  private:
    std::vector<TCONSTANT> m_constantData;
  };

}
