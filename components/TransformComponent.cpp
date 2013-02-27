#include "TransformComponent.h"

TransformComponent::TransformComponent(float x, float y, float z)
                  : position(x, y, z), scale(1, 1), rotation(0)
{
  type = TRANSFORM;
}
