#include "kraPipelineRenderer.h"

namespace kraEngineSDK {

  void
    DeferredPBRenderer::initialize()
  {
    m_GFXAPI = GraphicsAPI::instancePtr();

    m_gbufferVS = m_GFXAPI->getDevice()->createVertexShaderInstance();
    m_gbufferPS = m_GFXAPI->getDevice()->createPixelShaderInstance();
   

    
  }

  void 
  DeferredPBRenderer::render()
  {
    
    //Steps:

    //update constant buffers for vertex shader (models, WVP mats etc)

    //update vertex buffers for pixel shader (Lights, cam position etc)

    //Set pipeline state

    //Draw Skybox

    //Draw PBR models

    // Draw a full screen triangle for post processing/tone mapping.


  }

  void
  DeferredPBRenderer::gBufferSetup()
  {
    m_gbufferVS->compileVertexShader("gBufferShader.hlsl", "VS");

    m_gbufferPS->compilePixelShader("gBufferShader.hlsl", "PS");

    //m_PBRPS->compilePixelShader("gBufferShader.hlsl", "PS");
  }

  void 
  DeferredPBRenderer::iblSetup()
  {

  }

}  