#pragma once
#include "kraPrerequisitesCore.h"
#include "kraIndexBuffer.h"
#include "kraVertexBuffer.h"
#include <kraVertex.h>

namespace kraEngineSDK {
  
  class KRA_CORE_EXPORT Model
  {
   public:

     Model() = default;
     virtual
     ~Model() {}

    IndexBuffer<unsigned short>* m_indexBuffer;
    VertexBuffer* m_vertexBurffer;

    void 
    load(const std::string& fileName);

  };
}