#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(Sprite& s)
                  : tint(1, 1, 1, 1), sprite(s)
{
  type = SPRITE;
}
