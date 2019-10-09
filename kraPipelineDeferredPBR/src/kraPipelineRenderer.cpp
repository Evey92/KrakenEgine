#include "kraPipelineRenderer.h"

namespace kraEngineSDK {

  void
    DeferredPBRenderer::initialize()
  {
    m_GFXAPI = GraphicsAPI::instancePtr();

    m_gbufferVS = std::make_shared<VertexShader>(m_GFXAPI->getDevice()->createVertexShaderInstance());
    m_gbufferPS = std::make_shared<PixelShader>(m_GFXAPI->getDevice()->createPixelShaderInstance());
    m_PBRPS = std::make_shared<PixelShader>(m_GFXAPI->getDevice()->createPixelShaderInstance());

    
  }

  void
  DeferredPBRenderer::gBufferSetup()
  {
    m_gbufferVS->compileVertexShader("gBufferShader.hlsl", "VS");

    m_gbufferPS->compilePixelShader("gBufferShader.hlsl", "PS");

    m_PBRPS->compilePixelShader("gBufferShader.hlsl", "PS");
  }
}  