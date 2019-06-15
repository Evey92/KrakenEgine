#pragma once
#include <kraMatrix4.h>
#include "kraPrerequisitesCore.h"

namespace kraEngineSDK {
  class Matrix4;

  struct CBNeverChanges {

    Matrix4 m_view;
    Vector3 m_lightPosition;

  };

  struct CBChangeOnResize {
    
    Matrix4 m_projection;

  };

  struct CBChangesEveryFrame {
    Matrix4 m_world;
    Vector3 m_camPosition;
  };
}