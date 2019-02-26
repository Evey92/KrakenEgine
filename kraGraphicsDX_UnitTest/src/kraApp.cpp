#include <windows.h>
#include <string>
#include "kraApp.h"
 
  void App::startUp(GraphicsAPI* apiInstance) {
    
    apiInstance = apiManager->initializeGraphicsAPI();

  }

  HINSTANCE
  App::loadDLL() {
    HINSTANCE GFXDLL;
    char currDirect[300];
    GetWindowsDirectoryA(currDirect, 300);

    std::string DLLPath(currDirect);
    DLLPath = DLLPath.append("\\").append("kraGraphicsDXd.dll");
  
    GFXDLL = LoadLibraryEx(DLLPath.c_str(), nullptr, LOAD_WITH_ALTERED_SEARCH_PATH);
  
    return GFXDLL;
  }