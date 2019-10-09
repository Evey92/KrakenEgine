#pragma once
#include <kraRenderTargetView.h>
#include <kraGraphicsAPI.h>
#include <kraVertexShader.h>
#include <kraPixelShader.h>

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

     GraphicsAPI* m_GFXAPI;
     Vector<ShrdPtr<RenderTargetView*>> m_GbufferTextures;
     ShrdPtr<VertexShader> m_gbufferVS;
     ShrdPtr<PixelShader> m_gbufferPS;

     ShrdPtr<VertexShader> m_toTextureVS;
     ShrdPtr<PixelShader> m_toTexturePS;
     ShrdPtr<PixelShader> m_PBRPS;


  };

}