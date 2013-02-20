#include "TransformComponent.h"

TransformComponent::TransformComponent(float x, float y)
                     : x(x), y(y)
{
  type = TRANSFORM;
}
