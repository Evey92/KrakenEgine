#pragma once
#include "kraPrerequisitesCore.h"

namespace kraEngineSDK {
  class Blob {
  public:

    Blob() = default;
    virtual ~Blob() {}

    virtual void
      releaseBlob() = 0;

  };
}