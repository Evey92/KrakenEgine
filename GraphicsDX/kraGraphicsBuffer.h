#pragma once
#include "kraGraphicsDXPrequisites.h"

namespace kraEngineSDK {
  
  class kraGraphicsBuffer
  {

   public:
    kraGraphicsBuffer() = default;
    virtual ~kraGraphicsBuffer() { clearBuffer(); };
    virtual void clearBuffer() = 0;
    ID3D11Buffer* m_pBuffer = nullptr;
  
  };

}
