#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include <glm/glm.hpp>
#include "Component.h"
#include "helper/rendering/Sprite.h"

class SpriteComponent : public Component
{
  public:
    SpriteComponent(Sprite*);
    Sprite* sprite;
    glm::vec4 tint;
    unsigned int layer;
    
};
#endif
