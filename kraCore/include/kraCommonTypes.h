#pragma once

namespace kraEngineSDK {
  
  namespace INPUT_DEVICE {
    enum class E {
      kraMOUSE,
      kraKEYBOARD,
      kraGAMEPAD,
      kraTOUCH,
      kraCUSTOM,
    };
  }
    
    namespace TEXTURE_ADRESS {
      enum class E {

      };
    }

    namespace TEXTURE_TYPE{
      enum class E
      {
        BASECOLOR,
        METALNESS,
        SPECULAR,
        ROUGHNESS,
        EMISSIVE,
        NORMAL,
        AMBIENT,

      };
    }
}