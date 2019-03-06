#include "kraD3D11Blob.h"

namespace kraEngineSDK {

  void BlobDX::releaseBlob() {
    m_blob->Release();
  }

}