#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include <glm/glm.hpp>
#include "Component.h"
#include "helper/rendering/Sprite.h"
class GameManager;

class SpriteComponent : public Component
{
  friend class GameManager;
  private:
    SpriteComponent();
  public:
    Sprite* sprite;
    glm::vec4 tint;
    unsigned int layer;
    
};
#endif
