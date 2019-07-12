#pragma once
// Base headers
#include <kraBaseApplication.h>
#include <kraCamera.h>
#include <kraModel.h>
#include <kraMesh.h>
#include <kraMaterial.h>

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
#include <kraVertexBuffer.h>
#include <kraIndexBuffer.h>
#include <kraConstantBuffer.h>
#include <kraConstantBufferMatrices.h>
#include <kraRasterizerState.h>
#include <kraShaderResourceView.h>
#include <kraSampler.h>
#include <kraVector4.h>
#include <kraMatrix4.h>

#include "kraInputAPI.h"
#include "kraInputManager.h"

//Input Headers
//#include <kraInput/include/kraInputAPI.h>

using namespace kraEngineSDK;


class App : public BaseApplication
{
 public:

  App() = default;
  ~App() {}

  void
  run();
  HINSTANCE
  loadDLL();
  bool
  startUp(void* m_hWnd, int nCmdShow);
  bool
  LoadModel();
  void
  render();
  void
  Log(String outputString);
  void 
  CleanupDevice();
  void
  Initialize(int nCmdShow);
  void
  update();
  kraInputManager*
  getInputManager();
  uint32
  createBoolDevice(uint32 type);
  void
  MapBoolDevice(uint32 userBtn, uint32 type, uint32 key);
  Camera*
  getActiveCamera();
  void
  RotateWorldMat(int dir);
  void
  strafeCamera(int dir);
  void
  rotateCamera(float angle);
  void
  destroy();
  
 protected:
  /**
  * @brief Vrtual function used by the actual app to initialize its own libraries.
  */
  void
  preInitialice();

  /**
  * @brief Vrtual function used by the actual app to do stuff ater initialization.
  */
  void
  postInitialice();

  /**
  * @brief Vrtual function used by the actual app to .
  */
  void
  postUpdate();

  /**
  * @brief Main function to visualize the game logic.
  */
  void
  postRender();

  /**
  * @brief Main function to visualize the game logic.
  */
  void
  preDestroy();
  
  kraEngineSDK::Device* m_device;
  RenderTargetView* m_renderTargetView;
  RenderTargetView* m_normalTargetView;
  DepthStencil* m_depthStencil;
  DepthStencylView* m_depthStencilView;
  Viewport* m_viewport;
  VertexShader* m_vertexShader;
  InputLayout* m_inputLayout;
  PixelShader* m_pixelShader;
  VertexBuffer* m_vertBuffer;
  IndexBuffer* m_indexBuffer;
  ConstantBuffer<CBNeverChanges>* m_CBNeverChanges;
  ConstantBuffer<CBChangeOnResize>* m_CBChangesOnResize;
  ConstantBuffer<CBChangesEveryFrame>* m_CBChangesEveryframe;
  ConstantBuffer<Matrix4>* m_mainCB;
  ConstantBuffer<Vector4>* m_lightCB;
  Texture* m_pBackBuffer;
  Texture* m_texture;
  ShaderResourceView* m_SRV;
  RasterizerState* m_rasState;
  SamplerState* m_samplerState;
  RenderAPIManager* apiManager;
  GraphicsAPI* gfxAPIInstance;
  InputAPI* inputAPIInstance;
  Matrix4 m_world;
  Matrix4 m_projection;
  Vector4 color;
  Vector<Model*> m_modelsVec;
  Texture* textureManager;
  Camera mainCam;
  kraInputManager* m_inputManager;
  std::string modelPath = "resources/Models/";

};
