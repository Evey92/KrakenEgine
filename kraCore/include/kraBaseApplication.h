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
  {

#pragma region PUBLIC_METHODS
  public:
    BaseApplication() = default;
    ~BaseApplication() = default;

    /**
    * @brief Function to start up the app.
    */
    virtual bool
    startUp(int nCmdShow) = 0;

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

#pragma region PUBLIC_MEMBERS
  public:
    kraInputManager* m_inputManager = nullptr;

#pragma endregion PUBLIC_MEMBERS

#pragma region PROTECTED_MEMBERS
   
   protected:    
    SceneManager* m_sceneManager = nullptr;
    GraphicsAPI* m_gfxAPIInstance = nullptr;
    InputAPI* m_inputAPIInstance = nullptr;
    Texture* m_pBackBuffer = nullptr;
    ShaderResourceView* m_SRV = nullptr;
    RasterizerState* m_rasState = nullptr;
    SamplerState* m_samplerState = nullptr;
    Matrix4 m_world;
    Matrix4 m_projection;

#pragma endregion PROTECTED_MEMBERS

  }; 

}
