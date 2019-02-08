#pragma once
#include <kraMatrix4.h>
#include "kraPrerequisitesGFX.h"

namespace kraEngineSDK {
  class Matrix4;

  struct CBNeverChangesDX {
   public:
    CBNeverChangesDX() = default;
    CBNeverChangesDX(const CBNeverChangesDX& constMatt)
    {
      m_view = constMatt.m_view;
    }

    Matrix4 m_view;
  };

  struct CBChangeOnResizeDX {
  
   public:
    CBChangeOnResizeDX() = default;
    CBChangeOnResizeDX(const CBChangeOnResizeDX& constMatt)
    {
      m_projection = constMatt.m_projection;
    }

    Matrix4 m_projection;

  };

  struct CBChangesEveryFrameDX {
   public: 
    CBChangesEveryFrameDX() = default;

    CBChangesEveryFrameDX(const CBChangesEveryFrameDX& constMatt)
    {
      m_world = constMatt.m_world;
      m_vMeshColor = constMatt.m_vMeshColor;
    }

    Matrix4 m_world;
    Vector4 m_vMeshColor;
  };
}