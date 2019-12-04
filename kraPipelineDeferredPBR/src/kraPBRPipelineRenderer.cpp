#include "kraPBRPipelineRenderer.h"
#include <kraDevice.h>
#include <kraBaseApplication.h>
#include <kraVertexShader.h>
#include <kraPixelShader.h>
#include <kraComputeShader.h>
#include <kraRenderTargetView.h>
#include <kraTexture.h>
#include <kraDepthStencil.h>
#include <kraDepthStencilView.h>
#include <kraInputLayout.h>
#include <kraFrameBuffer.h>
#include <kraSampler.h>
#include <kraMesh.h>
#include <kraGameObject.h>

namespace kraEngineSDK {


  void
  DeferredPBRenderer::initialize(const ShrdPtr<Device>& pDevice)
  {
    //TODO: Try to fix this.
   /* m_GFXAPI = GraphicsAPI::instancePtr();
    m_appInstance = BaseApplication::instancePtr();*/

    m_gfxDevice = pDevice;

    //Init textures
    m_equirectHDRTexture = m_gfxDevice->createTextureInstance();
    m_enviroMap = m_gfxDevice->createTextureInstance();
    m_irradMap = m_gfxDevice->createTextureInstance();
    m_BRDFLUT = m_gfxDevice->createTextureInstance();
    m_cubeUnfiltered = m_gfxDevice->createTextureInstance();

    //Init shaders
    m_GbufferVS = m_gfxDevice->createVertexShaderInstance();
    m_GbufferPS = m_gfxDevice->createPixelShaderInstance();
    m_PBRVS = m_gfxDevice->createVertexShaderInstance();
    m_PBRPS = m_gfxDevice->createPixelShaderInstance();
    m_skyboxVS = m_gfxDevice->createVertexShaderInstance();
    m_skyboxPS = m_gfxDevice->createPixelShaderInstance();
    m_toneMapVS = m_gfxDevice->createVertexShaderInstance();
    m_toneMapPS = m_gfxDevice->createPixelShaderInstance();
    m_equirect2CubeCS = m_gfxDevice->createComputeShaderInstance();
    spBRDFshader = m_gfxDevice->createComputeShaderInstance();
    irradianceShader = m_gfxDevice->createComputeShaderInstance();

    //Init input layouts
    m_GbufferInputLayout = m_gfxDevice->createInputLayoutInstance();
    m_pbrInputLayout = m_gfxDevice->createInputLayoutInstance();
    m_skyboxInputLayout = m_gfxDevice->createInputLayoutInstance();
    
    //Init Samplers
    m_defaultSampler = m_gfxDevice->createSamplerStateInstance();
    m_computeSampler = m_gfxDevice->createSamplerStateInstance();
    m_BRDFSampler = m_gfxDevice->createSamplerStateInstance();

    //Init frame buffers
    srcFB = m_gfxDevice->createFrameBufferInstance();
    destinationFB = m_gfxDevice->createFrameBufferInstance();

    //Init constant buffers
    m_mainCB = m_gfxDevice->createConstantBufferInstance();
    m_shadingCB = m_gfxDevice->createConstantBufferInstanceVec4();
    m_specMapCB = m_gfxDevice->createConstantBufferInstanceFloat();

    //Init Depth stencils 
    m_defaultDepthStencil = m_gfxDevice->createDepthStencilInstance();
    m_skyboxDepthStencil = m_gfxDevice->createDepthStencilInstance();

    m_rasterizerState = m_gfxDevice->creatreRasterizerStateInstance();

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

    //Set up graphics API. Which makes no sense.
    m_rasterizerState->createRasterizerState(*m_gfxDevice,
                                             false,
                                             FILL_MODE::E::kFILL_SOLID,
                                             CULL_MODE::E::kCULL_BACK);

    m_defaultSampler->createSamplerState(*m_gfxDevice,
      SAMPLER_FILTER::E::kFILTER_ANISOTROPIC,
      TEXTURE_ADDRESS_MODE::E::kTEXTURE_ADDRESS_WRAP,
      COMPARISON_FUNCTION::E::kCOMPARISON_NEVER);

    uint32 samples = m_gfxDevice->checkMaxSupportedMSAALevel();

    if (!srcFB->initFramebuffer(m_gfxDevice->getWidth(),
      m_gfxDevice->getHeight(),
      samples,
      GFX_FORMAT::E::kFORMAT_R16G16B16A16_FLOAT,
      GFX_FORMAT::E::kFORMAT_D24_UNORM_S8_UINT)) {

      throw std::exception("Failed to initialize FrameBuffer");
    }

    if (samples > 1) {

      destinationFB->initFramebuffer(m_gfxDevice->getWidth(),
        m_gfxDevice->getHeight(),
        1,
        GFX_FORMAT::E::kFORMAT_R16G16B16A16_FLOAT,
        GFX_FORMAT::E::kFORMAT_UNKNOWN);
    }
    else {
      destinationFB = srcFB;
    }

    //Compiling up shaders
    m_PBRVS->compileVertexShader(L"resources/Shaders/PBR.hlsl", "VS");
    m_PBRVS->createVertexShader(*m_gfxDevice);

    m_PBRPS->compilePixelShader(L"resources/Shaders/PBR.hlsl", "PS");
    m_PBRPS->createPixelShader(*m_gfxDevice);

    m_skyboxVS->compileVertexShader(L"resources/Shaders/skyboxShader.hlsl", "VS");
    m_skyboxVS->createVertexShader(*m_gfxDevice);

    m_skyboxPS->compilePixelShader(L"resources/Shaders/skyboxShader.hlsl", "PS");
    m_skyboxPS->createPixelShader(*m_gfxDevice);


    m_toneMapVS->compileVertexShader(L"resources/Shaders/toneMappingShader.hlsl", "VS");
    m_toneMapVS->createVertexShader(*m_gfxDevice);

    m_toneMapPS->compilePixelShader(L"resources/Shaders/toneMappingShader.hlsl", "PS");
    m_toneMapPS->createPixelShader(*m_gfxDevice);

    //setting input layout
    m_pbrInputLayout->createInputLayout(*m_gfxDevice, *m_PBRVS);
    m_skyboxInputLayout->createInputLayout(*m_gfxDevice, *m_skyboxVS);


    //Setup IBL
    if (m_useIBL) {
      iblSetup();
    }

  }

  void 
  DeferredPBRenderer::setUpIrradianceMap()
  {
    irradianceShader->compileComputeShader(L"resources/Shaders/irradianceMapShader.hlsl", "main");
    irradianceShader->createComputeShader(*m_gfxDevice);

    m_irradMap->createCubeTexture(*m_gfxDevice,
      32, 32,
      GFX_FORMAT::E::kFORMAT_R16G16B16A16_FLOAT,
      GFX_USAGE::E::kUSAGE_DEFAULT,
      1);

    m_irradMap->createTextureUAV(*m_gfxDevice, 0);
    m_enviroMap->setTextureComputeShaderResource(*m_gfxDevice, 0, 1);
    m_computeSampler->setComputeSamplerState(*m_gfxDevice);
    m_irradMap->setTextureUnorderedAccesVews(*m_gfxDevice, 0, 1);
    irradianceShader->setComputeShader(*m_gfxDevice);
    irradianceShader->dispatchCS(*m_gfxDevice,
                                 m_irradMap->getWidth() / 32,
                                 m_irradMap->getHeight() / 32,
                                 6);
    m_irradMap->setComputeNullUAV(*m_gfxDevice);

    m_skyBoxGO->getComponent<Mesh>().setTexture(*m_gfxDevice, TEXTURE_TYPE::E::ALBEDO, m_enviroMap);
  }

  void 
  DeferredPBRenderer::setUpGBuffer()
  {
    m_GbufferVS->compileVertexShader(L"resources/Shaders/Gbuffer.hlsl", "VS");
    m_GbufferVS->createVertexShader(*m_gfxDevice);

    m_GbufferPS->compilePixelShader(L"resources/Shaders/Gbuffer.hlsl", "PS");
    m_GbufferPS->createPixelShader(*m_gfxDevice);

   /* for () {

    }*/

  }

  void
  DeferredPBRenderer::iblSetup()
  {
    //Creating unfiltered cube texture
    m_cubeUnfiltered->createCubeTexture(*m_gfxDevice,
                                        1024,
                                        1024,
                                        GFX_FORMAT::E::kFORMAT_R16G16B16A16_FLOAT,
                                        GFX_USAGE::E::kUSAGE_DEFAULT,
                                        0U);
    m_cubeUnfiltered->createTextureUAV(*m_gfxDevice, 0);

    //Compiling shader to convert an equirectangular projection image into a cubemap 
    m_equirect2CubeCS->compileComputeShader(L"resources/Shaders/equirect2Cube.hlsl", "main");
    m_equirect2CubeCS->createComputeShader(*m_gfxDevice);

    //Loading the equirectangular projection texture
    m_equirectHDRTexture->createTexture2DFromFile(*m_gfxDevice,
                                                  "resources/Textures/HDR/circus.hdr",
                                                  GFX_FORMAT::E::kFORMAT_R32G32B32A32_FLOAT,
                                                  GFX_USAGE::E::kUSAGE_DEFAULT,
                                                  CPU_USAGE::E::kCPU_ACCESS_WRITE,
                                                  4,
                                                  1);

    m_computeSampler->createSamplerState(*m_gfxDevice,
      SAMPLER_FILTER::E::kFILTER_MIN_MAG_MIP_LINEAR,
      TEXTURE_ADDRESS_MODE::E::kTEXTURE_ADDRESS_WRAP,
      COMPARISON_FUNCTION::E::kCOMPARISON_NEVER);

    //Setting up both textures to be used by the shader
    m_equirectHDRTexture->setTextureComputeShaderResource(*m_gfxDevice, 0, 1);
    m_cubeUnfiltered->setTextureUnorderedAccesVews(*m_gfxDevice, 0, 1);
    m_computeSampler->setComputeSamplerState(*m_gfxDevice);
    m_equirect2CubeCS->setComputeShader(*m_gfxDevice);
    m_equirect2CubeCS->dispatchCS(*m_gfxDevice,
                                  m_cubeUnfiltered->getWidth() / 32,
                                  m_cubeUnfiltered->getHeight() / 32,
                                  6);
    m_cubeUnfiltered->setComputeNullUAV(*m_gfxDevice);


    m_gfxDevice->generateMips(m_cubeUnfiltered);

    //Compiling shader to compute the specular env map 
    m_specMapCS->compileComputeShader(L"resources/Shaders/specMapShader.hlsl", "main");
    m_specMapCS->createComputeShader(*m_gfxDevice);

    m_specMapCB->createConstantBuffer(*m_gfxDevice);

    m_enviroMap->createCubeTexture(*m_gfxDevice,
                                   1024,
                                   1024,
                                   GFX_FORMAT::E::kFORMAT_R16G16B16A16_FLOAT,
                                   GFX_USAGE::E::kUSAGE_DEFAULT);

    for (uint32 arraySlice = 0; arraySlice < 6; ++arraySlice) {
      //This is the same as calling D3D11CalcSubresource. But I was too lazy to implement the function...
      /*To calculate the index of a subresource, you have to do: MipSlice + (ArraySlice * MipLevels).
      Here we're calculating the most detailed level, so mipslice = 0.*/
      const uint32 subResourceIndex = arraySlice * m_enviroMap->getLevels();
      m_gfxDevice->copySubresourceRegion(m_enviroMap,
                                         subResourceIndex,
                                         0,
                                         0,
                                         0,
                                         m_cubeUnfiltered,
                                         subResourceIndex,
                                         nullptr);
    }

    m_cubeUnfiltered->setTextureComputeShaderResource(*m_gfxDevice, 0, 1);
    m_computeSampler->setComputeSamplerState(*m_gfxDevice);
    m_specMapCS->setComputeShader(*m_gfxDevice);

    //Filtering the rest of the mip levels
    const float deltaRoughness = 1.0f / kraMath::fmax(m_enviroMap->getLevels() - 1.0f, 1.0f);
    float roughness;

    for (uint32 level = 1, size = 512; level < m_enviroMap->getLevels(); ++level, size /= 2) {

      uint32 numGroups = kraMath::fmax<uint32>(1, size / 32);
      m_specMapCB->clear();
      m_enviroMap->createTextureUAV(*m_gfxDevice, level);

      roughness = level * deltaRoughness;
      m_specMapCB->add(roughness);
      //m_specMapCB->createConstantBuffer(*m_gfxDevice);

      m_specMapCB->updateSubResources(*m_gfxDevice);
      m_specMapCB->setComputeConstantBuffer(*m_gfxDevice, 0, 1);

      m_enviroMap->setTextureUnorderedAccesVews(*m_gfxDevice, 0, 1);
      m_specMapCS->dispatchCS(*m_gfxDevice, numGroups, numGroups, 6);
    }

    m_specMapCB->setComputeNullConstantBuffer(*m_gfxDevice);
    m_enviroMap->setComputeNullUAV(*m_gfxDevice);

  }

  void 
  DeferredPBRenderer::onStartUp()
  {
    //initialize();
  }
  
  void
  DeferredPBRenderer::onShutdown()
  {
    //Shutdown
  }


}  