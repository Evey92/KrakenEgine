#pragma once
#include "kraPrerequisitesGFX.h"

class kraD3D11GraphicsBuffer
{
public:
  kraD3D11GraphicsBuffer() = default;
  virtual ~kraD3D11GraphicsBuffer() {
    if(m_pBuffer)
      m_pBuffer->Release();
  }

  virtual void
  reserve(size_t numObjects) = 0;

  virtual void
  clear() = 0;

  void
  createHardwareBuffer(ID3D11Device* pd3dDevice, unsigned int usage = D3D11_USAGE_DEFAULT);



  ID3D11Buffer* m_pBuffer = nullptr;
};

