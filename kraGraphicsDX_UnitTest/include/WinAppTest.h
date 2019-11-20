#pragma once
#include <kraBaseApplication.h>
#include <windows.h>
#include <string>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <d3d11shader.h>

//Utility Headers
#include <kraVector4.h>
#include <kraMatrix4.h>
#include <kraResourceLoading.h>
//Core Headers
#include <kraCameraManager.h>

//GFX Headers
#include <kraRenderAPIManager.h>
#include <kraGraphicsAPI.h>
#include <kraDevice.h>
#include <kraRenderTargetView.h>
#include <kraTexture.h>
#include <kraDepthStencil.h>
#include <kraDepthStencilView.h>
#include <kraViewport.h>
#include <kraShader.h>
#include <kraVertexShader.h>
#include <kraInputLayout.h>
#include <kraPixelShader.h>
#include <kraComputeShader.h>
#include <kraVertexBuffer.h>
#include <kraIndexBuffer.h>
#include <kraConstantBuffer.h>
#include <kraConstantBufferMatrices.h>
#include <kraRasterizerState.h>
#include <kraShaderResourceView.h>
#include <kraSampler.h>
#include <kraVector4.h>
#include <kraMatrix4.h>
#include <kraFrameBuffer.h>

//Input headers
#include <kraInputAPI.h>
#include <kraInputManager.h>

#include "kraWin32Window.h"
#include "kraUIManager.h"
using namespace kraEngineSDK;

class WinApp :
  public BaseApplication
{
 public:

   WinApp(int nCmdShow) 
     : m_nCmdShow(nCmdShow) {}
   ~WinApp() = default;

#pragma region APP_LIFECYCLE
   
   void
   preInitialice() override;

   bool
   Initialize() override;

   void
   postInitialice() override;

   void
   run() override;

   void
   preUpdate() override;

   void
   update() override;

   void
   update(float deltaTime) override;

   void
   postUpdate() override;

   void
   render() override;

   void
   postRender() override;

   void
   preDestroy() override;

   void
   destroy() override;
#pragma endregion APP_LIFECYCLE

#pragma region INPUT_FUNCTIONS
   
   kraInputManager*
   getInputManager();

   uint32
   createBoolDevice(uint32 type);

   void
   MapBoolDevice(uint32 userBtn, uint32 deviceID, uint32 key);

#pragma endregion INPUT_FUNCTIONS

#pragma region CAMERA_FUNCTIONS
   
   Camera*
   getActiveCamera();

   void
   updateCamera(Camera* newCam);

   void
   RotateWorldMat(int dir);

   void
   strafeCamera(int dir);

   void
   rotateCamera(float angle);

#pragma endregion CAMERA_FUNCTIONS

#pragma region UTILITY_FUNCTIONS
 public:

   //TODO: All of these should probably be on a resource manager or at least utility
   bool
   loadModel() override;

   /*HINSTANCE
   loadDLL() override;*/

   bool
   loadTexture();

   String
   loadFile(String filetypes);

   void
   CleanupDevice() override;

   //This is only so i can render stuff while I work on the pbr renderer
   void
   localRenderSetup();

   void
   setUpIBL();

   void
   setUpIrradianceMap();

   void
   setUpBRDF();

   void
   drawSkybox();

   void
   drawPBRModels();

   void
   toneMapPasss();

   //Very ugly function to set a hardcoded material
   void
   setGoldMaterial(Mesh& meshGO);

#pragma endregion UTILITY_FUNCTIONS

#pragma region PUBLIC_MEMBERS

   Device* m_gfxDevice = nullptr;
   Camera* m_activeCam =nullptr;
   CameraManager* m_camManager = nullptr;
   kraInputManager* m_inputManager = nullptr;

#pragma endregion PUBLIC_MEMBERS


#pragma region PRIVARE_MEMBERS

 public:
   


 private:
   Vector<ShrdPtr<Model>> m_modelsVector;
   ShrdPtr<Model> m_skyBoxModel;
   ShrdPtr<RenderTargetView> m_backBufferRTV = nullptr;
   ShrdPtr<Texture> m_equirectHDRTexture = nullptr;
   ShrdPtr<Texture> m_enviroMap = nullptr;
   ShrdPtr<Texture> m_irradMap = nullptr;
   ShrdPtr<Texture> m_BRDFLUT = nullptr;
   ShrdPtr<Texture> m_cubeUnfiltered = nullptr;
   ShrdPtr<ComputeShader> spBRDFshader;
   ShrdPtr<ComputeShader> irradianceShader;


   ShrdPtr<RasterizerState> m_rasterizerState = nullptr;
   ShrdPtr<DepthStencil> m_defaultDepthStencil = nullptr;
   ShrdPtr<DepthStencil> m_skyboxDepthStencil = nullptr;
   ShrdPtr<DepthStencilView> m_depthStencilView = nullptr;
   
   ShrdPtr<SamplerState> m_defaultSampler;
   ShrdPtr<SamplerState> m_computeSampler;
   ShrdPtr<SamplerState> m_BRDFSampler;

   //This is just temporary BS

   ShrdPtr<FrameBuffer> srcFB;
   ShrdPtr<FrameBuffer> destinationFB;
  
   //Shaders & Input layouts
   ShrdPtr<VertexShader> m_PBRVS = nullptr;
   ShrdPtr<PixelShader> m_PBRPS = nullptr;
   ShrdPtr<InputLayout> m_pbrInputLayout = nullptr;
   ShrdPtr<VertexShader> m_skyboxVS = nullptr;
   ShrdPtr<PixelShader> m_skyboxPS = nullptr;
   ShrdPtr<InputLayout> m_skyboxInputLayout = nullptr;

   ShrdPtr<VertexShader> m_toneMapVS = nullptr;
   ShrdPtr<PixelShader> m_toneMapPS = nullptr;

   ShrdPtr<ComputeShader> m_equirect2CubeCS;
   ShrdPtr<ComputeShader> m_specMapCS;
   
    //Input layout
   ShrdPtr<InputLayout> m_localLayout;
    //Sampler state
   ShrdPtr<SamplerState> m_equirectSampler;

    //Constant buffers
   ShrdPtr<ConstantBuffer<Matrix4>> m_mainCB;
   ShrdPtr<ConstantBuffer<Vector4>> m_shadingCB;
   ShrdPtr<ConstantBuffer<Vector4>> m_specMapCB;

   /////////////////////////////////////////////

   Viewport* m_viewport = nullptr;
   String modelPath = "resources/Models/";
   Win32Window* m_window = nullptr;
   Vector4 ClearColor = { 0.329f, 0.050f, 0.431f, 1.0f };
   int m_nCmdShow = 0;

#pragma endregion PRIVARE_MEMBERS


};

