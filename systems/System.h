#ifndef SYSTEM_H
#define SYSTEM_H

#include <unordered_set>
#include <list>
using namespace std;

#include "../Entity.h"
#include "../components/Component.h"

class System
{
  public:
    explicit System(GameManager&);
    //This is where the system does it's work on each entity
    virtual void update()=0;
    //When an entity gains/loses a compononent this will update the list
    void entityChanged(Entity*, const list<Component*>&);

  protected:
    unordered_set<Entity*> entities; //List of relevant entities for the system
    list<ComponentType> neededComponents; //Defines what components are used
    GameManager& getGameManager();

  private:
    GameManager& gm; //So it can get info on the entities
};
#endif
