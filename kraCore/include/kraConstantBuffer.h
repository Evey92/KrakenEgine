#pragma once
#include "kraGraphicsBuffer.h"

namespace kraEngineSDK {

  template<typename TCONST>
  class kraConstantBuffer : public GraphicsBuffer
  {

  public:
    kraConstantBuffer() {};
    virtual ~kraConstantBuffer() { clearBuffer(); }

    /**
     * @brief Creates a vertex buffer.
     * @param size of te vertex, number of vertexes, and a flag for usage.
     */
    virtual void
      createConstantBuffer(uint32 constantSize, uint32 numConstant/*, here should go the usage flag */) = 0;
    /**
     * @brief Reserves memory using the size of the object containing
     * the vertexes.
     * @param the size of the object containing the vertexes .
     */
    void
      reserve(size_t numObjects) = 0;


    /**
    * @brief Adds a single vertex to the buffer.
    * @param the address of the vertex.
    */
    void
      add(const TCONST& constant) = 0;
    /**
    * @brief Copies a whole vertex vector into the buffer.
    * @param the vector containing the vertexes.
    */
    void
      add(const std::vector<TCONST>& constants) = 0;

    /**
    * @brief Adds multiple constants onto the buffer.
    * @param A pointer to the start position of the constants, ad the number of constants.
    */
    void
      add(const TCONST* pConstants, size_t numConstants) = 0;

    /**
    * @brief Cleans the Constant buffer.
    */
    void
      clearBuffer() {
      m_constantData.clear();
    }

  private:
    std::vector<TCONST> m_constantData;

  };

}


