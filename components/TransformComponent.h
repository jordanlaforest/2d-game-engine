#ifndef TRANSFORM_COMPONENT_H
#define TRANSFROM_COMPONENT_H

#include "Component.h"
#include <glm/glm.hpp>

class TransformComponent : public Component
{
  public:
    TransformComponent(float x=0, float y=0);
    
    glm::vec2 position;
    glm::vec2 scale; 
    float rotation;
};
#endif
