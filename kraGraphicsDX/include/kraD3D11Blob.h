#pragma once
#include <kraBlob.h>

#include "kraPrerequisitesGFX.h"

namespace kraEngineSDK {
  class BlobDX : public Blob {
   public:
    
     BlobDX() = default;
    ~BlobDX() {}

    ID3DBlob* m_blob = nullptr;

  };
}