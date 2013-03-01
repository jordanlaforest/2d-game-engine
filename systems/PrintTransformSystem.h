#ifndef PRINT_TRANSFORM_SYSTEM
#define PRINT_TRANSFORM_SYSTEM

#include "System.h"

//A test system that will just print out the position of each entity
//and its name
class PrintTransformSystem : public System
{
  public:
    PrintTransformSystem(GameManager&);
  protected:
    void updateEntity(Entity& e);
    void preUpdate();
    void postUpdate();
    void entityAdded(Entity*, const list<Component*>&);
    void entityRemoved(Entity*, const list<Component*>&);
};
#endif
