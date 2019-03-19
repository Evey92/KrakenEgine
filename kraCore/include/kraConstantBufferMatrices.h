#pragma once
#include <kraMatrix4.h>
#include "kraPrerequisitesCore.h"

namespace kraEngineSDK {
  class Matrix4;

  struct CBNeverChanges {

    Matrix4 m_view;
  
  };

  struct CBChangeOnResize {
    
    Matrix4 m_projection;

  };

  struct CBChangesEveryFrame {
    Matrix4 m_world;
  };
}