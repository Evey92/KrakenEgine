#include "kraResourceLoading.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace kraEngineSDK {

  Image::Image()
    : m_width(0)
    , m_height(0)
    , m_channels(0)
    , m_isHDR(false)
  {}
      
  ShrdPtr<Image>
  Image::LoadImageFromFile(const String& filename, int channels)
  {
    ShrdPtr<Image> img{ new Image };
    if (stbi_is_hdr(filename.c_str())) {
      float* hdrImage = stbi_loadf(filename.c_str(), &img->m_width, &img->m_height, &img->m_channels, channels);

      if (hdrImage) {
        img->m_pixels.reset(reinterpret_cast<unsigned char*>(hdrImage));
        img->m_isHDR = true;
        std::cout << "HDR texture loaded successfully\n";
      }
      else {
        std::cout << "Couldn't find texture, loading default texture\n";
        stbi_image_free(hdrImage);
        return nullptr;
      }
    }
    else {
      unsigned char* pixels = stbi_load(filename.c_str(), &img->m_width, &img->m_height, &img->m_channels, channels);
      if (pixels)
      {
        img->m_pixels.reset(pixels);
        img->m_isHDR = false;
      }
      else
      {
        std::cout << "Couldn't find texture: " << filename <<  ". loading default texture\n";
        stbi_image_free(pixels);
        pixels = stbi_load("resources/Textures/missingCheckered.jpg", &img->m_width, &img->m_height, &img->m_channels, channels);
        img->m_pixels.reset(pixels);
      }
    }

    if (channels > 0) {
      img->m_channels = channels;
    }

    if (!img->m_pixels) {
      std::cout << "Failed to load image file: " << filename << std::endl;
    }
    return img;

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
