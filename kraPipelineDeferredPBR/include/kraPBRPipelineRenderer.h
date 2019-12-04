#pragma once
#include "kraPrerequisitesPBRenderer.h"
#include <kraRenderPipeline.h>
#include <kraRenderTargetView.h>
#include <kraGraphicsAPI.h>
#include <kraConstantBuffer.h>
#include <kraVector4.h>
#include <kraMatrix4.h>

namespace kraEngineSDK {
  
  /*class VertexShader;
  class PixelShader;*/
  class GameObject;
  class Camera;
  class Model;
  class Mesh;
  class Device;
  class FrameBuffer;
  class RasterizerState;
  class VertexShader;
  class PixelShader;
  class ComputeShader;
  class BaseApplication;
  class DepthStencil;
  class DepthStencilView;
  class InputLayout;
  class SamplerState;

  class KRA_RENDERER_EXPORT DeferredPBRenderer : 
  public RenderPipeline
  {
   public:

    DeferredPBRenderer() = default;
    ~DeferredPBRenderer() = default;

    void
    initialize(const ShrdPtr<Device>&, ShrdPtr<Camera>&, ShrdPtr<BaseApplication>&) override;

    void
    Setup() override;

    void
    render() override;

   private:

     void 
     setUpIrradianceMap();
     
     void
     lightPass();

     void
     saoPass();

     void
     setUpGBuffer();

     void
     iblSetup();

   protected:
    void
    onStartUp() override;


    void
    onShutdown() override;

   public:
     
     GraphicsAPI* m_GFXAPI = nullptr;
     ShrdPtr<Device> m_gfxDevice;
     ShrdPtr<Camera> m_activeCam;
     ShrdPtr<BaseApplication> m_appInstance = nullptr;

     //Textures
     Vector<ShrdPtr<Texture*>> m_GbufferTextures;
     ShrdPtr<Texture> m_equirectHDRTexture = nullptr;
     ShrdPtr<Texture> m_enviroMap = nullptr;
     ShrdPtr<Texture> m_irradMap = nullptr;
     ShrdPtr<Texture> m_BRDFLUT = nullptr;
     ShrdPtr<Texture> m_cubeUnfiltered = nullptr;

     //Shaders
     ShrdPtr<VertexShader> m_GbufferVS;
     ShrdPtr<PixelShader> m_GbufferPS;
     ShrdPtr<VertexShader> m_PBRVS;
     ShrdPtr<PixelShader> m_PBRPS;
     ShrdPtr<VertexShader> m_skyboxVS;
     ShrdPtr<PixelShader> m_skyboxPS;
     ShrdPtr<VertexShader> m_toneMapVS;
     ShrdPtr<PixelShader> m_toneMapPS;
     ShrdPtr<ComputeShader> m_equirect2CubeCS;
     ShrdPtr<ComputeShader> m_specMapCS;
     ShrdPtr<ComputeShader> spBRDFshader;
     ShrdPtr<ComputeShader> irradianceShader;

     //Input layouts
     ShrdPtr<InputLayout> m_GbufferInputLayout;
     ShrdPtr<InputLayout> m_pbrInputLayout;
     ShrdPtr<InputLayout> m_skyboxInputLayout;

     //Samplers 
     ShrdPtr<SamplerState> m_defaultSampler;
     ShrdPtr<SamplerState> m_computeSampler;
     ShrdPtr<SamplerState> m_BRDFSampler;

     //Frame buffers 
     ShrdPtr<FrameBuffer> srcFB;
     ShrdPtr<FrameBuffer> destinationFB;

    //Cosntant Buffers
     ShrdPtr<ConstantBuffer<Matrix4>> m_mainCB;
     ShrdPtr<ConstantBuffer<Vector4>> m_shadingCB;
     ShrdPtr<ConstantBuffer<float>> m_specMapCB;

     //Depth Stencils. I probably just need one
     ShrdPtr<DepthStencil> m_defaultDepthStencil = nullptr;
     ShrdPtr<DepthStencil> m_skyboxDepthStencil = nullptr;
     //Now I'm using the one on the frame buffer
     //ShrdPtr<DepthStencilView> m_depthStencilView = nullptr;

     //Rasterizer
     ShrdPtr<RasterizerState> m_rasterizerState = nullptr;

     Vector<ShrdPtr<GameObject>> m_modelsVector;
     ShrdPtr<GameObject> m_skyBoxGO;
     
     bool m_useIBL = true;
  };

}