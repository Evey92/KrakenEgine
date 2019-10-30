#include "kraResourceLoading.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace kraEngineSDK {
      
  bool
  EngineUtility::LoadImageFromFile(String filename, Image* img)
  {
    if (stbi_is_hdr(filename.c_str())) {
      float* hdrImage = stbi_loadf(filename.c_str(), &img->m_width, &img->m_height, &img->channels, 4);

      if (hdrImage) {
        img->pixels = reinterpret_cast<unsigned char*>(hdrImage);
        img->m_isHDR = true;
        std::cout << "HDR texture loaded successfully\n";
        return true;
      }
      else {
        std::cout << "Couldn't find texture, loading default texture\n";
        stbi_image_free(hdrImage);
        return false;
      }
    }
    else {
      unsigned char* pixels = stbi_load(filename.c_str(), &img->m_width, &img->m_height, &img->channels, 4);
      if (pixels)
      {
        img->pixels = pixels;
        return true;
      }
      else
      {
        std::cout << "Couldn't find texture, loading default texture\n";
        stbi_image_free(pixels);
        pixels = stbi_load("resources/Textures/missingChecker.png", &img->m_width, &img->m_height, &img->channels, 4);
        img->pixels = pixels;
        return true;
      }
    }
  }

  String 
  EngineUtility::loadFile(String filetypes, HWND hWnd = nullptr)
  {
    char filename[MAX_PATH];
    memset(&filename, 0, sizeof(filename));

    OPENFILENAME ofn;
    memset(&ofn, 0, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hWnd;
    //ofn.lpstrFilter = filetypes.c_str();
    ofn.lpstrFilter = "Any File\0*.*\0";
    ofn.lpstrFile = filename;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrTitle = "Choose a File!";
    ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

    if (GetOpenFileName(&ofn))
    {
      std::cout << "You chose the file \"" << filename << "\"\n";
      return filename;
    }
    else
    {
      std::cout << "There was an error and the file couldn't be opened";
      return "";
    }
  }

  
}
