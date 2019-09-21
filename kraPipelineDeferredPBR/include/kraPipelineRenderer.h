#pragma once
#include "kraPrerequisitesPBRenderer.h"

namespace kraEngineSDK {
  
  class VertexShader;
  class PixelShader;
  class Model;

  class KRA_RENDERER_EXPORT DeferredPBRenderer
  {
   public:

    DeferredPBRenderer() = default;
    ~DeferredPBRenderer() = default;

    void
    initialize();

    void
    render();

   private:

     void
     gBufferSetup();

     void
     lightPass();

     void
     saoPass();

     void 
     postProcessPass();

     void
     forwardPass();

     void
     iblSetup();

     ShrdPtr<VertexShader> m_gbufferVS;
     ShrdPtr<VertexShader> m_toTextureVS;
     ShrdPtr<PixelShader> m_toTexturePS;
     ShrdPtr<PixelShader> m_PBRPS;


  };

}