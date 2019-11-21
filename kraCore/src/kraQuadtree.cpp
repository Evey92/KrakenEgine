#include "kraQuadtree.h"
#include "kraGameObject.h"

namespace kraEngineSDK {
  
  
  void 
  Quadtree::insert(const ShrdPtr<GameObject>& node)
  {
    if (node == nullptr) {
      return;
    }

    Vector2 pos = Vector2(node->getComponent<Transform>().getPosition().x,
                          node->getComponent<Transform>().getPosition().y);

    if (!isInBoundary(pos)) {
      return;
    }

    //Check if this quad can be subdivided anymore
    if (kraMath::abs(topLeft.x - bottomRight.x) &&
        kraMath::abs(topLeft.y - bottomRight.y)) {
      
      if (m_node == nullptr) {
        m_node = node;
        return;
      }
    }

    if ((topLeft.x + bottomRight.x) / 2 >= pos.x) {
      
      //It's topLeftTree
      if ((topLeft.y + bottomRight.y) / 2 >= pos.y) {
        
        if (topLeftTree == nullptr) {

          topLeftTree = make_shared<Quadtree>(Vector2(topLeft.x, topLeft.y),
                                              Vector2((topLeft.x, bottomRight.x) / 2,
                                              (topLeft.y + bottomRight.y) / 2));

          topLeftTree->insert(node);
        }
      }
      //It's botLeftTree
      else {
        if (bottomLeftTree == nullptr) {

          bottomLeftTree = make_shared<Quadtree>(Vector2(topLeft.x, (topLeft.y + bottomRight.y) / 2),
                                                 Vector2((topLeft.x, bottomRight.x) / 2,
                                                 bottomRight.y));
          bottomLeftTree->insert(node);
        }
      }
    }
    else {
      //It's topRightTree
      if ((topLeft.y + bottomRight.y) / 2 >= pos.y) {
        if (topRightTree == nullptr) {
          topRightTree = make_shared<Quadtree>(Vector2((topLeft.x + bottomRight.x) / 2,
                                               topLeft.y),
                                               Vector2(bottomRight.x,
                                               (topLeft.y + bottomRight.y) / 2));
          topRightTree->insert(node);
        }
      }
      //It's bottomRightTree
      else {
        if (bottomRightTree == nullptr) {
          bottomRightTree = make_shared<Quadtree>(Vector2((topLeft.x + bottomRight.x) / 2,
                                                  (topLeft.y + bottomRight.y) / 2),
                                                  Vector2(bottomRight.x,
                                                  bottomRight.y));
          bottomRightTree->insert(node);
        }
      }
    }

  }

  ShrdPtr<GameObject> 
  Quadtree::search(Vector2 position)
  {
    if (!isInBoundary(position)) {
      return nullptr;
    }

    if (m_node != nullptr) {
      return m_node;
    }

    if ((topLeft.x + bottomRight.x) / 2 >= position.x) {

      //Top Left Tree
      if ((topLeft.y + bottomRight.y) / 2 >= position.y) {
        
        if (topLeftTree == nullptr) {
          return nullptr;
        }

        return topLeftTree->search(position);
      }
      //Bottom Left Tree
      else {

        if (bottomLeftTree == nullptr) {
          return nullptr;
        }
        return bottomLeftTree->search(position);
      }

    }
    else {
      //Top Right Tree
      if ((topLeft.y + bottomRight.y) / 2 >= position.y) {
        if (topRightTree == nullptr) {
          return nullptr;
        }
        return topRightTree->search(position);
      }
      //Bottom Right Tree
      else {
        if (bottomRightTree == nullptr) {
          return nullptr;
        }
        bottomRightTree->search(position);
      }
    }
  }

  bool 
  Quadtree::isInBoundary(Vector2 position)
  {
    return (position.x >= topLeft.x &&
            position.x <= bottomRight.x&&
            position.y >= topLeft.y &&
            position.y <= bottomRight.y);
  }

}
