#include "SpriteComponent.h"

SpriteComponent::SpriteComponent()
                  : sprite(0), tint(1, 1, 1, 1), layer(0)
{
  type = SPRITE;
}
