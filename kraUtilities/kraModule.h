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
         cout<<"Trying to acces module but it hasn't started" // TODO: Should acces module
       }

       if (!isDestroyed()) {
         cout << "Trying to acces a destroyed Module" // TODO: Should acces module
       }

       return *_instance();

     }

     static T*
     instancePtr() {
       if (!isStartedUp()) {
         cout << "Trying to acces module but it hasn't started\n"; // TODO: Should acces module
       }

       if (!isDestroyed()) {
         cout << "Trying to acces a destroyed Module\n"; // TODO: Should acces module
       }

       return _instance();

     }

     template<class... Args>
     static void
     startUp(Args&& ...args) {
       if (isStartedUp()) {
         cout << "Trying to start an already started module\n";
       }

       _instance() = new T(std::forward<Args>(args)...);

       isStartedUp() = true;

       static_cast<Module*>(_instance())->onStartUp();
     }

     template<class SubType, class... Args>
     static void
     startUp(Args&& ...args) {
       static_assert(std::is_base_of<T, SubType>::value, "Provided type isn't derived from the type the Module is initialized\n");
       
       if (isStartedUp()) {
         cout << "Trying to start an already started module\n";
       }

       _instance() = new SubType(std::forward<Args>(args)...);

       isStartedUp() = true;

       static_cast<Module*>(_instance())->onStartUp();
     }

     static void
     shutDown() {
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
     Module = default;

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