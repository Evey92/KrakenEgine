/******************************************************************************/
/*
* This is the main function to creaty ANY kind of app.
*It has the basic structure every app should have,
*and its virtual functions to be used by the instances.
*/
/******************************************************************************/

#pragma once
#include "kraPrerequisitesCore.h"

namespace kraEngineSdk {
  class KRA_CORE_EXPORT kraBaseApplication
  {
  public:
    kraBaseApplication() = default;
    virtual
     ~kraBaseApplication() {}

    /**
    * @brief Main funtion to execute a program.
    */
    void
    run() {

    }

   private:
    /**
    * @brief Main function to initialize all the main libraries like GFX, network, systems etc.
    */
    void
    Initialize() {

    }
    
    /**
    * @brief Main loop of the app.
    */
    void
      update(float deltaTime) {}
    
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

    /**
    * @brief Main function to destroy all the objects created in the app.
    */
    void
    destroy() {

    }

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

    /**
    * @brief Example function to manage Mouse input.
    */
    /*virtual void
    onMouseMove(float x, float y, buttons) = 0; */

    /**
    * @brief Function to create an specific type of Graphics API.
    */
    void
    CreateGraphicsAPI();

  };
}
