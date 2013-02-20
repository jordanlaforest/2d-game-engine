#ifndef TRANSFORM_COMPONENT_H
#define TRANSFROM_COMPONENT_H

#include "Component.h"

class TransformComponent : public Component
{
  public:
    TransformComponent(float x=0, float y=0);
    float x, y;
};
#endif
