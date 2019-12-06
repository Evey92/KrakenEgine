#pragma once
#include "kraPrerequisitesUtil.h"
#include "kraVector4.h"

namespace kraEngineSDK {

  class KRA_UTILITY_EXPORT Color {

   public:
     Color() = default;
     Color(float _r,
           float _g,
           float _b,
           float _a) 
     : r(_r), g(_g), b(_b), a(_a) {}

     Color(float _r,
           float _g,
           float _b) 
     : r(_r), g(_g), b(_b), a(1.0f) {}

     Color(Vector4 colorVal) 
     : r(colorVal[0]), g(colorVal[1]), b(colorVal[2]), a(colorVal[3]) {}

     ~Color() = default;

     float&
     operator[](uint32 Index);

     float
     operator[](uint32 Index) const;

     static const Color Black;
     static const Color Blue;
     static const Color Clear;
     static const Color Cyan;
     static const Color Grey;
     static const Color Green;
     static const Color Magenta;
     static const Color NeonPink;
     static const Color Purple;
     static const Color Red;
     static const Color White;
     static const Color Yellow;
     
     float r;
     float g;
     float b;
     float a;
  };

}
