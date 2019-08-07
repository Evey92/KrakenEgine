#pragma once
#include <kraBaseApplication.h>
#include <windows.h>
#include <string>

//GFX Headers
#include <kraRenderAPIManager.h>
#include <kraRenderTargetView.h>
#include <kraDepthStencil.h>
#include <kraDepthStencilView.h>
#include <kraViewport.h>
#include <kraShader.h>
#include <kraVertexShader.h>
#include <kraInputLayout.h>
#include <kraPixelShader.h>
#include <kraConstantBuffer.h>
#include <kraConstantBufferMatrices.h>

#include <kraVector4.h>
#include <kraMatrix4.h>

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

   WinApp() = default;
   ~WinApp() = default;

#pragma region APP_LIFECYCLE
   
   bool
   startUp(int nCmdShow) override;

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
   setActiveCamera(Camera* newCam);

   void
   RotateWorldMat(int dir);

   void
   strafeCamera(int dir);

   void
   rotateCamera(float angle);

#pragma endregion CAMERA_FUNCTIONS

#pragma region UTILITY_FUNCTIONS
   
   bool
   LoadModel();

   HINSTANCE
   loadDLL();

   void
   CleanupDevice();

#pragma endregion UTILITY_FUNCTIONS

#pragma region PUBLIC_MEMBERS
   Camera* m_activeCam =nullptr;
   kraInputManager* m_inputManager = nullptr;

#pragma endregion PUBLIC_MEMBERS


#pragma region PRIVARE_MEMBERS

 private:
   std::string modelPath = "resources/Models/";
   Win32Window* m_window;
   Viewport* m_viewport = nullptr;
   RenderTargetView* m_mainRenderTarget;
   DepthStencil* m_depthStencil;
   DepthStencylView* m_depthStencilView;
   Vector4 ClearColor;
   UIManager m_UIManager;
#pragma endregion PRIVARE_MEMBERS
};

