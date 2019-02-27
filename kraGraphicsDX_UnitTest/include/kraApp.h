#pragma once
#include <kraBaseApplication.h>
#include <kraRenderAPIManager.h>
#include <kraGraphicsAPI.h>
#include <kraPrerequisitesCore.h>
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
#include <kraShaderResourceView.h>
#include <kraSampler.h>


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
  int
  startUp(void* m_hWnd);
  void
  RenderTriangle();
  void
  render();

 private:
  
  void
  Initialize();
  void
  update(float deltaTime);
  
  
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
  Device* m_device;
  RenderTargetView* m_renderTargetView;
  DepthStencil* m_depthStencil;
  DepthStencylView* m_depthStencilView;
  Viewport* m_viewport;
  VertexShader* m_vertexShader;
  InputLayout* m_inputLayout;
  PixelShader* m_pixelShader;
  VertexBuffer<Vertex>* m_vertBuffer;
  IndexBuffer<unsigned short>* m_indexBuffer;
  Texture* m_pBackBuffer;
  Texture* m_texture;
  ShaderResourceView* m_SRV;
  SamplerState* m_samplerState;
  RenderAPIManager* apiManager;
  GraphicsAPI* gfxAPIInstance;
  
};
