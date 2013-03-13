#ifndef TRANSFORM_COMPONENT_H
#define TRANSFROM_COMPONENT_H

#include "Component.h"
#include <glm/glm.hpp>
class GameManager;

class TransformComponent : public Component
{
  friend class GameManager;
  private:
    TransformComponent();
  public:
    glm::vec2 position;
    glm::vec2 scale; 
    float rotation;
};
#endif
