#pragma once
#include "kraGraphicsBuffer.h"

namespace kraEngineSDK {
  template <typename TINDEX>
  class kraIndexBuffer : public kraGraphicsBuffer
  {
   
   public:
    kraIndexBuffer() = default;
    ~kraIndexBuffer() { clearBuffer(); };
  
    /**
     * @brief Creates an Index buffer.
     * @param A pointer to the device, and a flag for usage.
     */
    void 
    createIndexBuffer(ID3D11Device* pd3dDevice, D3D11_USAGE usage = D3D11_USAGE_DEFAULT) {
      D3D11_BUFFER_DESC bd;
      memset(&bd, 0, sizeof(bd));

      bd.Usage = usage;
      bd.ByteWidth = static_cast<uint32_t>(sizeof(TINDEX)*m_indexData.size()); // TODO: Make it use My own Uint32 type
      bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
      bd.CPUAccessFlags = 0;

      D3D11_SUBRESOURCE_DATA InitData;
      memset(&InitData, 0, sizeof(InitData));
      InitData.pSysMem = &m_indexData[0];

      HRESULT hr = pd3dDevice->CreateBuffer(&bd, &InitData, &m_pBuffer);
      if (FAILED(hr))
      {
        throw std::exception("Failed to create Index Buffer");
      }
    }

    /**
    * @brief Reserves memory using the size of the object containing the indexes.
    * @param the size of the object containing the vertexes .
    */
    void
    reserve(size_t numObjects) {
      m_indexData.reserve(numObjects);
    }

    /**
    * @brief Adds a single index to the buffer.
    * @param the address of the index.
    */
    void
      add(const TINDEX& vertex) {
      m_indexData.push_back(vertex);
    }
    /**
    * @brief Copies a whole index vector into the buffer.
    * @param the vector containing the indexes.
    */
    void
      add(const std::vector<TINDEX>& vertices) {
      m_indexData.insert(m_indexData.end(), vertices.begin(), vertices.end());
    }

    /**
    * @brief Adds multiple indexes onto the buffer.
    * @param A pointer to the start position and the number of indexes.
    */
    void
      add(const TINDEX* pindexes, size_t numIndexes) {

      m_indexData.insert(m_indexData.end(),
        pindexes,
        pindexes +
        numIndexes);
    }

    /**
    * @brief Cleans the indexes buffer.
    */
    void
      clearBuffer() {
      m_indexData.clear();
    }

   private:
     std::vector<TINDEX> m_indexData;
  };

}
