#pragma once
#include "kraGraphicsBuffer.h"
#include "kraDevice.h"

namespace kraEngineSDK {
 
  template<typename TVERTEX>
  class VertexBuffer : public GraphicsBuffer
  {

  public:
    VertexBuffer() = default;
    virtual 
    ~VertexBuffer() {}

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
    add(const TVERTEX& vertex) = 0;
    /**
    * @brief Copies a whole vertex vector into the buffer.
    * @param the vector containing the vertexes.
    */
    virtual void
    add(const std::vector<TVERTEX>& vertices) = 0;

    /**
    * @brief Adds multiple vertexes onto the buffer.
    * @param A pointer to the start position of the vertexes, ad the number of vertexes.
    */
    virtual void
    add(const TVERTEX* pVertices, size_t numVertices) = 0;

    virtual void
    clear() = 0;

    /**
 * @brief Creates a vertex buffer.
 * @param size of te vertex, number of vertexes, and a flag for usage.
 */
    virtual void
    createHardwareBuffer(Device* pDevice) = 0;

    virtual void
    setVertexBuffer(Device* pImmediateContext) = 0;

    /**
    * @brief Cleans the vertex buffer.
    */
    virtual void
      cleanVertexBuffer() = 0;
    

  };

}
