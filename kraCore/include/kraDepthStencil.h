#pragma once
#include "kraPrerequisitesCore.h"
#include "kraTexture.h"

namespace kraEngineSDK {
  class KRA_CORE_EXPORT DepthStencil
  {
   public:
     void
     createDepthStencil(void* pDevice, int height, int width);
     
     void
     cleanDepthStencil();
     
     Texture m_pd3dDepthStencil;
     void* descDepth; // IDK if I'm supposed to create my own descriptors.
  };
}
