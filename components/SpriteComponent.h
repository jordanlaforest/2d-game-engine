#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include "Sprite.h"

class SpriteComponent : public Component
{
  public:
    SpriteComponent();
    Sprite& sprite;
    vec4 tint;
    
};
#endif
