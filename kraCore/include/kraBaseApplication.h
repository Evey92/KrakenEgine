/******************************************************************************/
/*
* This is the main function to creaty ANY kind of app.
*It has the basic structure every app should have,
*and its virtual functions to be used by the instances.
*/
/******************************************************************************/

#pragma once
#include <kraVector4.h>
#include <kraMatrix4.h>

#include "kraPrerequisitesCore.h"
#include <kraModule.h>
#include "kraWindow.h"
#include "kraSceneManager.h"

//GFX Headers
#include "kraGraphicsAPI.h"
#include "kraRasterizerState.h"
#include "kraShaderResourceView.h"
#include "kraSampler.h"

//Input headers
#include "kraInputAPI.h"
#include "kraInputManager.h"

//Renderer headers
#include "kraRenderPipeline.h"

namespace kraEngineSDK {
  
  namespace Button
  {
    enum E
    {
      Dkey = 0,
      AKey,
      WKey,
      SKey,
      SPACEKey,
      CTRLKey,
      QKey,
      EKey,
      MouseX,
      MouseY,
    };
  }

  namespace DeviceType
  {
    enum E {
      Mouse = 0,
      Keyboard,
      Gamepad,
    };
  }
  class KRA_CORE_EXPORT BaseApplication
    : public Module<BaseApplication>
  {

#pragma region PUBLIC_METHODS
  public:
    BaseApplication() = default;
    ~BaseApplication() = default;

    /**
    * @brief Main function to execute a program.
    */
    virtual void
    run() = 0;
    /**
    * @brief Main function to initialize all the main libraries like GFX, network, systems etc.
    */
    virtual bool
    Initialize() = 0;
    
    /**
    * @brief Main loop of the app.
    */
    virtual void
    update() = 0;

    /**
    * @brief Main loop of the app.
    */
    virtual void
    update(float deltaTime) = 0;
    
    /**
    * @brief Main function to visualize the game logic.
    */
    virtual void
    render() = 0;

    void
    Log(String outputString) {
      std::cout << outputString << std::endl;
    }

    /**
    * @brief Main function to destroy all the objects created in the app.
    */
    virtual void
    destroy() = 0;
#pragma endregion PUBLIC_METHODS

#pragma region PROTECTED_METHODS
   protected:
    /**
    * @brief Virtual function used by the actual app to initialize its own libraries.
    */
    virtual void
    preInitialice() = 0;
    
    /**
    * @brief Virtual function used by the actual app to do stuff after initialization.
    */
    virtual void
    postInitialice() = 0;

    /**
   * @brief Virtual function used by the actual app to .
   */
    virtual void
    preUpdate() = 0;
    
    /**
    * @brief Virtual function used by the actual app to .
    */
    virtual void
    postUpdate() = 0;
    
    /**
    * @brief Main function to visualize the game logic.
    */
    virtual void
    postRender() = 0;
    
    /**
    * @brief Main function to visualize the game logic.
    */
    virtual void
    preDestroy() = 0;

#pragma endregion PROTECTED_METHODS

#pragma region UTILITY_FUNCTIONS
  public:

    virtual bool
    loadModel() = 0;

    /*virtual HINSTANCE
    loadDLL() = 0;*/

    virtual void
    CleanupDevice() = 0;

#pragma endregion UTILITY_FUNCTIONS

#pragma region PRIVATE_MEMBERS
   private:
   /**
   * @brief On start up, it executes itself just after being created
   */
    void
    onStartUp() override;

    void
    onShutdown() override;

#pragma endregion PRIVATE_MEMBERS

#pragma region PUBLIC_MEMBERS
  public:
    //TODO: This should be a module
    kraInputManager* m_inputManager = nullptr;

#pragma endregion PUBLIC_MEMBERS

#pragma region PROTECTED_MEMBERS
   
   protected:    

    SceneManager* m_sceneManager = nullptr;
    GraphicsAPI* m_gfxAPIInstance = nullptr;
    InputAPI* m_inputAPIInstance = nullptr;
    RenderPipeline* m_renderPipeInstance = nullptr;
    Matrix4 m_world = Matrix4::IDENTITY;
    Matrix4 m_projection = Matrix4::ZERO;
    Matrix4 m_skyprojection = Matrix4::ZERO;
    ShrdPtr<Texture> m_textureManager = nullptr;

#pragma endregion PROTECTED_MEMBERS

  }; 

}
