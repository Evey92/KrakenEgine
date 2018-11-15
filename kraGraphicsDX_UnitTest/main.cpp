#include <iostream>
#include <gtest/gtest.h>
#include <kraPrerequisitesGFX.h>
#include <kraD3D11GraphicsAPI.h>

namespace kraEngineSDK {
  int main(int argc, char **argv)
  {
    std::cout << "Testing GraphicsDX API\n";
    GraphicsAPI gfxAPI;

    gfxAPI.initializeAPI();
    gfxAPI.Render();

      return 0;

  }
}