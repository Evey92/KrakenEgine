#pragma once
#include "kraPrerequisitesGFX.h"
#include "kraMatrix4.h"

namespace kraEngineSDK {
  
  struct CBNeverChanges {
   public:
    CBNeverChanges() = default;
    CBNeverChanges(const CBNeverChanges& constMatt)
    {
      m_view = constMatt.m_view;
    }

    Matrix4 m_view;
  };

  struct CBChangeOnResize {
  
   public:
    CBChangeOnResize() = default;
    CBChangeOnResize(const CBChangeOnResize& constMatt)
    {
      m_projection = constMatt.m_projection;
    }

    Matrix4 m_projection;

  };

  struct CBChangesEveryFrame {
   public: 
    CBChangesEveryFrame() = default;

    CBChangesEveryFrame(const CBChangesEveryFrame& constMatt)
    {
      m_world = constMatt.m_world;
      m_vMeshColor = constMatt.m_vMeshColor;
    }

    Matrix4 m_world;
    Vector4 m_vMeshColor;
  };
}