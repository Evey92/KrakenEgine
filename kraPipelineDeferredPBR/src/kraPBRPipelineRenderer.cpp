#include "kraPBRPipelineRenderer.h"

namespace kraEngineSDK {

  void
    DeferredPBRenderer::initialize()
  {
    m_GFXAPI = GraphicsAPI::instancePtr();
    m_appInstance = BaseApplication::instancePtr();
    m_PBRVS = m_GFXAPI->getDevice()->createVertexShaderInstance();
    m_PBRPS = m_GFXAPI->getDevice()->createPixelShaderInstance();
   

    
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
  DeferredPBRenderer::Setup()
  {
    //Set up PBR
    m_PBRVS->compileVertexShader("gBufferShader.hlsl", "VS");

    m_PBRPS->compilePixelShader("gBufferShader.hlsl", "PS");

    //Setup Skybox

    //Setup tonemap

    //Setup IBL
    if (m_useIBL) {
      iblSetup();
    }

  }

  void 
  DeferredPBRenderer::iblSetup()
  {
    //create texture
    //Texture envMap = m_GFXAPI->getDevice->createTextureInstance();

  }

}  