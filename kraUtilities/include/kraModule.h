#pragma once
#include "kraPrerequisitesUtil.h"
#include <iostream>

namespace kraEngineSDK{
  using std::cout;

  template<class T>
  class Module
  {
   public:

     static T&
     instance() {
       if (!isStartedUp()) {
         std::cout << "Trying to access module but it hasn't started\n"; 
       }

       if (isDestroyed()) {
         std::cout << "Trying to access a destroyed Module\n"; 
       }

       return *_instance();

     }

     static T*
     instancePtr() {
       if (!isStartedUp()) {
         std::cout << "Trying to access module but it hasn't started\n";
       }

       if (isDestroyed()) {
         std::cout << "Trying to access a destroyed Module\n"; 
       }

       return _instance();

     }

     template<class... Args>
     static void
     StartUp(Args&& ...args) {
       if (isStartedUp()) {
         cout << "Trying to start an already started module\n";
       }

       _instance() = new T(std::forward<Args>(args)...);

       isStartedUp() = true;
       isDestroyed() = false;

       static_cast<Module*>(_instance())->onStartUp();
     }

     template<class SubType, class... Args>
     static void
     StartUp(Args&& ...args) {
       static_assert(std::is_base_of<T, SubType>::value, "Provided type isn't derived from the type the Module is initialized\n");
       
       if (isStartedUp()) {
         cout << "Trying to start an already started module\n";
       }

       _instance() = new SubType(std::forward<Args>(args)...);

       isStartedUp() = true;
       isDestroyed() = false;

       static_cast<Module*>(_instance())->onStartUp();
     }

     static void
     ShutDown() {
       if (isDestroyed()) {
         cout << "Trying to shut down an already shut down module\n";
       }

       if (!isStartedUp()) {
         cout << "Trying to shut down a module that was never started\n";
       }

       static_cast<Module*>(_instance())->onShutdown();

       delete(_instance());
       isDestroyed() = true;
     }

     static bool
     isStarted() {
       return isStartedUp() && !isDestroyed();
     }

   protected:
     Module() = default;

     virtual
     ~Module() = default;

     Module(Module&&) = delete;

     Module(const Module&) = delete;
     
     Module&
     operator = (Module&&) = delete;

     Module&
     operator=(const Module&) = delete;

     virtual void
     onStartUp() {}

     virtual void
     onShutdown() {}

     static T*&
       _instance() {
       static T* inst = nullptr;

       return inst;
     }

     static bool&
     isDestroyed() {
       static bool inst = false;
       return inst;
     }

     static bool&
     isStartedUp() {
       static bool inst = false;
       return inst;
     }

  };

}