/******************************************************************************/
/*
* This is the main function to creaty ANY kind of app.
*It has the basic structure every app should have,
*and its virtual functions to be used by the instances.
*/
/******************************************************************************/

#pragma once
#include "kraPrerequisitesCore.h"
#include "kraWin32Window.h"

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
  public:
    BaseApplication() = default;
    ~BaseApplication() = default;

    /**
    * @brief Function to start up the app.
    */
    void
    StartUp() {

    }

    /**
    * @brief Main funtion to execute a program.
    */
    virtual void
    run() = 0;
    /**
    * @brief Main function to initialize all the main libraries like GFX, network, systems etc.
    */
     virtual void
     Initialize(int nCmdShow) = 0;
    
    /**
    * @brief Main loop of the app.
    */
    void
    update(float deltaTime) {
      float dt = deltaTime;
      dt = dt * 4;
    }
    
    /**
    * @brief Main function to visualize the game logic.
    */
    void
    render() {
      /*
      begin();
      postRender();
      end();
      swap();
      */
    }

    void
    Log(String outputString) {

    }

    /**
    * @brief Main function to destroy all the objects created in the app.
    */
    void
    destroy() {

    }

    Win32Window* m_window;

   protected:
    /**
    * @brief Vrtual function used by the actual app to initialize its own libraries.
    */
    virtual void
    preInitialice() = 0;
    
    /**
    * @brief Vrtual function used by the actual app to do stuff ater initialization.
    */
    virtual void
    postInitialice() = 0;
    
    /**
    * @brief Vrtual function used by the actual app to .
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

  };


  

}
