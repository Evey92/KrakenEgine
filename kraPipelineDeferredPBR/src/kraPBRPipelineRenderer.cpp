#include "kraPBRPipelineRenderer.h"

namespace kraEngineSDK {

  void
    DeferredPBRenderer::initialize()
  {
    m_GFXAPI = GraphicsAPI::instancePtr();
    m_appInstance = BaseApplication::instancePtr();

    //Init shaders
    m_PBRVS = m_GFXAPI->getDevice()->createVertexShaderInstance();
    m_PBRPS = m_GFXAPI->getDevice()->createPixelShaderInstance();
    m_skyboxVS = m_GFXAPI->getDevice()->createVertexShaderInstance();
    m_skyboxPS = m_GFXAPI->getDevice()->createPixelShaderInstance();
    m_toneMapVS = m_GFXAPI->getDevice()->createVertexShaderInstance();
    m_toneMapPS = m_GFXAPI->getDevice()->createPixelShaderInstance();
    m_equirect2CubeCS = m_GFXAPI->getDevice()->createComputeShaderInstance();

    m_skyboxInputLayout;
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
    m_PBRVS->compileVertexShader(L"PBR.hlsl", "VS");
    m_PBRPS->compilePixelShader(L"PBR.hlsl", "PS");

    //Setup Skybox
    m_skyboxVS->compileVertexShader(L"skyboxShader.hlsl", "VS");
    m_skyboxPS->compilePixelShader(L"skyboxShader.hlsl", "PS");

    //Setup tone mapping
    m_toneMapVS->compileVertexShader(L"toneMappingShader.hlsl", "VS");
    m_toneMapPS->compilePixelShader(L"toneMappingShader.hlsl", "PS");

    //Setup IBL
    if (m_useIBL) {
      iblSetup();
    }

  }

  void 
  DeferredPBRenderer::iblSetup()
  {
    m_equirect2CubeCS->compileComputeShader(L"equirect2Cube.hlsl", "CS");
    ShrdPtr<Texture> envitromentText = m_GFXAPI->getDevice()->createTextureInstance();
    envitromentText->createTexture2DFromFile(*m_GFXAPI->getDevice(),
                                             "enviroment.hdr",
                                             GFX_FORMAT::E::kFORMAT_R32G32B32A32_FLOAT,
                                             GFX_USAGE::E::kUSAGE_DYNAMIC,
                                             CPU_USAGE::E::kCPU_ACCESS_WRITE,
                                             1);


    envitromentText->setTextureComputeShaderResource(m_GFXAPI->getDevice(), 0, 1);
    m_equirectSampler->setComputeSamplerState(*m_GFXAPI->getDevice());
    m_equirect2CubeCS->setComputeShader(*m_GFXAPI->getDevice());

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