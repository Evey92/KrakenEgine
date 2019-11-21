#pragma once

#include "kraPrerequisitesUtil.h"
#include "kraVector4.h"
#include "kraVector2.h"

namespace kraEngineSDK {
  class GameObject;

  class KRA_UTILITY_EXPORT Quadtree
  {
    
   public:
   
     Quadtree() = default;
     Quadtree(Vector2 topL, Vector2 botR) 
     : topLeft(topL), bottomRight(botR) {}

     ~Quadtree() = default;
    
     void 
     insert(GameObject* node);
    
     ShrdPtr<GameObject>
     search(Vector2 position);
    
     bool
     isInBoundary(Vector2 pos);
    
    
    
   private:

    ShrdPtr<Quadtree> topLeftTree = nullptr;
    ShrdPtr<Quadtree> topRightTree = nullptr;
    ShrdPtr<Quadtree> bottomLeftTree = nullptr;
    ShrdPtr<Quadtree> bottomRightTree = nullptr;
    ShrdPtr<GameObject> m_node = nullptr;
    Vector2 topLeft = Vector2::ZERO;
    Vector2 bottomRight = Vector2::ZERO;


  };
}