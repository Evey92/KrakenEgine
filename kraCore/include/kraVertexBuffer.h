#pragma once
#include "kraGraphicsBuffer.h"

namespace kraEngineSDK {
 
  class Device;
  //template<typename TVERTEX>
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
    add(const Vertex& vertex) = 0;
    /**
    * @brief Copies a whole vertex vector into the buffer.
    * @param the vector containing the vertexes.
    */
    virtual void
    add(const std::vector<Vertex>& vertices) = 0;

    /**
    * @brief Adds multiple vertexes onto the buffer.
    * @param A pointer to the start position of the vertexes, ad the number of vertexes.
    */
    virtual void
    add(const Vertex* pVertices, size_t numVertices) = 0;

    virtual void
    clear() = 0;

    virtual void
    Release() = 0;

    /**
 * @brief Creates a vertex buffer.
 * @param size of te vertex, number of vertexes, and a flag for usage.
 */
    virtual void
    createHardwareBuffer(const Device& pDevice) = 0;

    virtual void
    setVertexBuffer(const Device& pDevice) = 0;

  };

}
