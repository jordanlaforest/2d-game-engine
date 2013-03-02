#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(Sprite* s)
                  : sprite(s), tint(1, 1, 1, 1)
{
  type = SPRITE;
}
