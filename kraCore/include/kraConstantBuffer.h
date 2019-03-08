#pragma once
#include "kraGraphicsBuffer.h"
#include "kraConstantBufferMatrices.h"
#include "kraDevice.h"

namespace kraEngineSDK {

  template<typename TCONST>
  class ConstantBuffer : public GraphicsBuffer
  {

  public:
    ConstantBuffer() {};
    virtual ~ConstantBuffer() {}

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
    virtual void
    add(const Vector<TCONST>& constant) = 0;
    /**
    * @brief Copies a whole vertex vector into the buffer.
    * @param the vector containing the vertexes.
    */
    /*virtual void
    add(const std::vector<TCONST>& constants) = 0;*/

    virtual void
    clear() = 0;

    virtual void
    Release() = 0;

    virtual void
    createConstantBuffer(const Device& pDevice) = 0;

    virtual void
    setConstantBuffer(const Device& pDevice) = 0;

    virtual void
    updateSubResources(const Device& pDevice, CBNeverChanges cbNvrMat) = 0;

    virtual void
    updateSubResources(const Device& pDevice, CBChangeOnResize cbNvrMat) = 0;
    
    virtual void
    updateSubResources(const Device& pDevice, CBChangesEveryFrame cbNvrMat) = 0;

    virtual void
    setVertexConstantBuffer(const Device& pDevice, uint32 startSlot, uint32 NumBuffs) = 0;

    virtual void
    setPixelConstantBuffer(const Device& pDevice, uint32 startSlot, uint32 NumBuffs) = 0;
  };

}


