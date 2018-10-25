#pragma once
#include "kraPrerequisitesUtil.h"
#include "kraPlatformMath.h"

#if KRA_PLATFORM == KRA_PLATFORM_WIN32
#include "kraWindowsMath.h"
#endif

namespace kraEngineSDK {

#if KRA_PLATFORM == KRA_PLATFORM_WIN32
  using kraMath = kraWindowsMath;
#else
  using kraMath = kraPlatformMath;
#endif

}

