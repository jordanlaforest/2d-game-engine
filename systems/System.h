#ifndef SYSTEM_H
#define SYSTEM_H

#include <list>
using namespace std;

#include "../Entity.h"
#include "../components/Component.h"

class System
{
  protected:
    list<Entity*> entities; //List of relevant entities for the system
    list<ComponentType> neededComponents; //Defines what components are used
  public:
    virtual void update()=0;
    void entityChanged(const Entity*, const list<Component*>&);

};
#endif
