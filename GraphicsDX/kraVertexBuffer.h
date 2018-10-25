#pragma once


#include "kraGraphicsBuffer.h"


namespace kraEngineSDK {

  template<typename TVERTEX>
  class kraVertexBuffer : public kraGraphicsBuffer
  {

   public:
     kraVertexBuffer() {};
    ~kraVertexBuffer() { clearBuffer(); }
    
    /**
     * @brief Creates a vertex buffer.
     * @param A pointer to the device, and a flag for usage.
     */
    void 
    createVertexBuffer(ID3D11Device* pd3dDevice,
                       unsigned int usage = D3D11_USAGE_DEFAULT) {

      D3D11_BUFFER_DESC bd;
      memset(&bd, 0, sizeof(bd));

      bd.Usage = usage;
      bd.ByteWidth = static_cast<uint32_t>(sizeof(TVERTEX)* 
                                           m_vertexData.size()); // TODO Make it use MY Uint32 type
      bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
      bd.CPUAccessFlags = 0;

      D3D11_SUBRESOURCE_DATA InitData;
      memset(&InitData, 0, sizeof(InitData));
      InitData.pSysMem = &m_vertexData[0];

      HRESULT hr = pd3dDevice->CreateBuffer(&bd, &InitData, &m_pBuffer);
      if (FAILED(hr))
      {
        throw std::exception("Failed to create Vertex Buffer.");
      }
    }
    
   /**
    * @brief Reserves memory using the size of the object containing the vertexes.
    * @param the size of the object containing the vertexes .
    */
    void
    reserve(size_t numObjects) {
      m_vertexData.reserve(numObjects);
    }

    /**
    * @brief Adds a single vertex to the buffer.
    * @param the address of the vertex.
    */
    void 
    add(const TVERTEX& vertex) {
      m_vertexData.push_back(vertex);
    }
    /**
    * @brief Copies a whole vertex vector into the buffer.
    * @param the vector containing the vertexes.
    */
    void 
    add(const std::vector<TVERTEX>& vertices) {
      m_vertexData.insert(m_vertexData.end(), vertices.begin(), vertices.end());
    }

    /**
    * @brief Adds multiple vertexes onto the buffer.
    * @param A pointer to the start position of the vertexes, ad the number of vertexes.
    */
    void 
    add(const TVERTEX* pVertices, size_t numVertices) {
      
      m_vertexData.insert(m_vertexData.end(),
        pVertices,
        pVertices +
        numVertices);
    }

    /**
    * @brief Cleans the vertex buffer.
    */
    void 
    clearBuffer() {
      m_vertexData.clear();
    }

   private:
    std::vector<TVERTEX> m_vertexData;

  };
}

