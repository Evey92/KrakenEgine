#include "kraModel.h"

namespace kraEngineSDK {
  void
  Model::load(const std::string& fileName) {
    std::vector<Vertex> tmpVerts;
    std::vector<unsigned short> tmpIndex;

    m_vertexBurffer->add(tmpVerts);
    m_indexBuffer->add(tmpIndex);
  }
}