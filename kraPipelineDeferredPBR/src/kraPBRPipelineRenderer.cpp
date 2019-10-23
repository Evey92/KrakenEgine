#include "kraPBRPipelineRenderer.h"

namespace kraEngineSDK {

  void
    DeferredPBRenderer::initialize()
  {
    //m_GFXAPI = GraphicsAPI::instance();
    m_appInstance = BaseApplication::instancePtr();
    m_PBRVS = make_shared<VertexShader>(GraphicsAPI::instance().getDevice()->createVertexShaderInstance());
    //m_PBRPS = m_GFXAPI->getDevice()->createPixelShaderInstance();
    m_PBRPS = make_shared<PixelShader>(GraphicsAPI::instance().getDevice()->createVertexShaderInstance());
   

    
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
    std::cout << "Setting up the pipeline\n";
    //m_PBRPS->compilePixelShader("gBufferShader.hlsl", "PS");

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

  void 
  DeferredPBRenderer::onStartUp()
  {
    initialize();
  }
  
  void
  DeferredPBRenderer::onShutdown()
  {
    //Shutdown
  }


}  