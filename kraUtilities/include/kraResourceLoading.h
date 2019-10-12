#pragma once
#include <windows.h>

#include "kraPrerequisitesUtil.h"

namespace kraEngineSDK {
  
  struct Image {
    int m_height = 0;
    int m_width = 0;
    bool m_isHDR = false;
    int channels = 4;
    unsigned char* pixels = nullptr;
  };

  class KRA_UTILITY_EXPORT EngineUtility
  {
   
   public:
    static bool
    LoadImageFromFile(String filename, Image* img);

    static String
    loadFile(String filetypes, HWND hWnd);

   private:

    String m_missingTexture = "resources/Textures/missingChecker.png";


  };
}