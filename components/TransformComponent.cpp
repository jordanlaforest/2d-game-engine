#include "TransformComponent.h"

TransformComponent::TransformComponent(float x, float y)
                  : position(x, y), scale(1, 1), rotation(0)
{
  type = TRANSFORM;
}
