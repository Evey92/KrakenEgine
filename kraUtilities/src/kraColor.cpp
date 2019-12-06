#include "kraColor.h"

namespace kraEngineSDK {

  float& 
  Color::operator[](uint32 Index)
  {
    if (Index == 0) {
      return r;
    }
    else if (Index == 1) {
      return g;
    }
    else if (Index == 2) {
      return b;
    }
    else if (Index == 3) {
      return a;
    }
  }

  float 
  Color::operator[](uint32 Index) const
  {
    if (Index == 0) {
      return r;
    }
    else if (Index == 1) {
      return g;
    }
    else if (Index == 2) {
      return b;
    }
    else if (Index == 3) {
      return a;
    }
  }

  const Color Color::Black   = Color(0.0f, 0.0f, 0.0f, 1.0f);
  const Color Color::Blue    = Color(0.0f, 0.0f, 1.0f, 1.0f);
  const Color Color::Clear   = Color(0.0f, 0.0f, 0.0f, 0.0f);
  const Color Color::Cyan    = Color(0.0f, 1.0f, 1.0f, 1.0f);
  const Color Color::Grey    = Color(0.5f, 0.5f, 0.5f, 1.0f);
  const Color Color::Green   = Color(0.0f, 1.0f, 0.0f, 1.0f);
  const Color Color::Magenta = Color(1.0f, 0.0f, 1.0f, 1.0f);
  const Color Color::NeonPink = Color(0.9294f, 0.0352f, 0.5647f, 1.0f);
  const Color Color::Purple  = Color(0.329f, 0.050f, 0.431f, 1.0f);
  const Color Color::Red     = Color(1.0f, 0.0f, 0.0f, 1.0f);
  const Color Color::White   = Color(1.0f, 1.0f, 1.0f, 1.0f);
  const Color Color::Yellow  = Color(1.0f, 0.92f, 0.016f, 1.0f);

}
