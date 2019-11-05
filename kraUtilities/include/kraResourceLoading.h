#pragma once
#include <windows.h>

#include "kraPrerequisitesUtil.h"

namespace kraEngineSDK {
  
  struct Image {
    int m_height = 0;
    int m_width = 0;
    uint32 m_levels =  0;
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

    template<typename T> static T
    numMipLevels(T width, T height) {

      T levels = 1;
      while ((width | height) >> levels) {
        ++levels;
      }

      return levels;
    }

   private:

    String m_missingTexture = "resources/Textures/missingChecker.png";


  };
}