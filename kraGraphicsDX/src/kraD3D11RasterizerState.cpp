#include "kraD3D11RasterizerState.h"


namespace kraEngineSDK {
 
  void
  RasterizerStateDX::createRasterizerState()
  {
    D3D11_RASTERIZER_DESC rasDesc;
    memset(&rasDesc, 0, sizeof(D3D11_RASTERIZER_DESC));
 
   
    rasDesc.CullMode = D3D11_CULL_BACK;
    rasDesc.FillMode =D3D11_FILL_SOLID;
    rasDesc.FrontCounterClockwise = false;
  }
}