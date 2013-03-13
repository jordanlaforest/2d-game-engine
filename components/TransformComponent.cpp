#include "TransformComponent.h"

TransformComponent::TransformComponent()
                  : position(0, 0), scale(1, 1), rotation(0)
{
  type = TRANSFORM;
}
