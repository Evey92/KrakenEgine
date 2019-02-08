#pragma once
#include "kraGraphicsBuffer.h"

namespace kraEngineSDK {

  template<typename TINDEX>
  class KRA_CORE_EXPORT IndexBuffer : public GraphicsBuffer
  {

   public:
    
    IndexBuffer() {};
    virtual 
     ~IndexBuffer() {}

    
    /**
     * @brief Reserves memory using the size of the object containing
     * the vertexes.
     * @param the size of the object containing the vertexes .
     */
    virtual void
    reserve(size_t numObjects) = 0;


    /**
    * @brief Adds a single vertex to the buffer.
    * @param the address of the vertex.
    */
    virtual void
      add(const TINDEX& index) = 0;
    /**
    * @brief Copies a whole vertex vector into the buffer.
    * @param the vector containing the vertexes.
    */
    virtual void
    add(const std::vector<TINDEX>& indexes) = 0;

    /**
    * @brief Adds multiple vertexes onto the buffer.
    * @param A pointer to the start position of the vertexes, ad the number of vertexes.
    */
    virtual void
    add(const TINDEX* pVertices, size_t numVertices) = 0;

    /**
    * @brief Cleans the vertex buffer.
    */
    virtual void
    clear() = 0;

    /**
     * @brief Creates a vertex buffer.
     * @param size of te vertex, number of vertexes, and a flag for usage.
     */
    virtual void
    createIndexBuffer(uint32 indexSize, uint32 numIndex/*, here should go the usage flag */) = 0;

    virtual void
      setIndexBuffer(void* pImmediateContext) = 0;

  };

}

