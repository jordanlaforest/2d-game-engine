#ifndef COMPONENT_H
#define COMPONENT_H

enum ComponentType { TRANSFORM, SPRITE };

class Component
{
  protected:
    Component(); //Don't allow this class to be contructed
    ComponentType type;
  public:
    ComponentType getType();
};
#endif
