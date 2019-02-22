#pragma once
#include "kraBaseApplication.h"
#include "kraRenderAPIManager.h"
#include "kraGraphicsAPI.h"

using namespace kraEngineSDK;

class App : public BaseApplication
{
 
 public:
  void startUp(GraphicsAPI* APIInstance);

  RenderAPIManager* apiManager;
  
};
