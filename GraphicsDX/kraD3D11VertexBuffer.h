#pragma once
#include "kraD3D11GraphicsBuffer.h"
#include <d3d11.h>
#include <vector>

namespace kraEngineSDK {
  template<typename TVERTEX>
  class kraD3D11VertexBuffer :
    public kraD3D11GraphicsBuffer
  {
  public:
    kraD3D11VertexBuffer();
    ~kraD3D11VertexBuffer();
  
    void createHardwareBuffer(ID3D11Device* pd3dDevice, unsigned int usage = D3D11_USAGE_DEFAULT);
  };


}
