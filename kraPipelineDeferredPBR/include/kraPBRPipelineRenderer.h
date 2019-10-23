#pragma once
#include <kraRenderTargetView.h>
#include <kraGraphicsAPI.h>
#include <kraBaseApplication.h>
#include <kraRenderPipeline.h>
#include <kraVertexShader.h>
#include <kraPixelShader.h>

#include "kraPrerequisitesPBRenderer.h"

namespace kraEngineSDK {
  
  /*class VertexShader;
  class PixelShader;*/
  class Model;

  class KRA_RENDERER_EXPORT DeferredPBRenderer : 
  public RenderPipeline
  {
   public:

    DeferredPBRenderer() = default;
    ~DeferredPBRenderer() = default;

    void
    initialize() override;

    void
    Setup() override;

    void
    render() override;

   private:

     

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

   protected:
    virtual void
      onStartUp() override;


    virtual void
      onShutdown() override;

   public:
     GraphicsAPI* m_GFXAPI = nullptr;
     BaseApplication* m_appInstance = nullptr;
     Vector<ShrdPtr<RenderTargetView*>> m_GbufferTextures;
     
     ShrdPtr<VertexShader> m_PBRVS;
     ShrdPtr<PixelShader> m_PBRPS;
     ShrdPtr<InputLayout> m_pbrInputLayout;

     ShrdPtr<VertexShader> m_skyboxVS;
     ShrdPtr<PixelShader> m_skyboxPS;
     ShrdPtr<InputLayout> m_skyboxInputLayout;

     ShrdPtr<VertexShader> m_toneMapVS;
     ShrdPtr<PixelShader> m_toneMapPS;

     bool m_useIBL = true;
     /*ShrdPtr<VertexShader> m_toTextureVS;
     ShrdPtr<PixelShader> m_toTexturePS;*/
     


  };

}