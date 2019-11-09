#pragma once
#include <windows.h>

#include "kraPrerequisitesUtil.h"

namespace kraEngineSDK {
  
  //Helper class to extract raw data from images using Stb_Image
  class KRA_UTILITY_EXPORT Image {
   public:

    static ShrdPtr<Image>
    LoadImageFromFile(const String& filename, int channels = 4);

    int getWidth() const { return m_width; }
     
    int getHeight() const { return m_height; }
     
    int getChannels() const { return m_channels; }
    
    int bytesPerPixel() const { return m_channels * (m_isHDR ? sizeof(float) : sizeof(unsigned char)); }

    int getPitch() const { return m_width * bytesPerPixel(); }

    uint32 getLevels() const { return m_levels; }
     
     //Function to get raw pixel data as a pointer of given type (Usually void*)
     template<typename T>
     const T* getPixels() const { 
       return reinterpret_cast<const T*>(m_pixels.get()); 
     }

  
          
     bool isHDR() const { return m_isHDR; }
     

   private:
     Image();

    UnqPtr<unsigned char> m_pixels = nullptr;
    int m_height = 0;
    int m_width = 0;
    int m_channels = 4;
    uint32 m_levels =  0;
    bool m_isHDR = false;
  };

  class KRA_UTILITY_EXPORT EngineUtility
  {
   
   public:
    

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