#ifndef SYSTEM_H
#define SYSTEM_H

#include <unordered_set>
#include <list>
using namespace std;

#include "Entity.h"
#include "Component.h"

class System
{
  public:
    System(GameManager&, string n);
    //This is where the system does it's work on each entity
    void update();
    //When an entity gains/loses a compononent this will update the list
    void entityChanged(Entity*, const list<Component*>&);
    string& getName();

  protected:
    //Called before looping through each entity
    virtual void preUpdate()=0;
    //Called after looping through each entity
    virtual void postUpdate()=0;
    //Called for each entity
    virtual void updateEntity(Entity& e)=0;
    //Called when an entity is added or removed from the systems list
    // of entities (so when the entity becomes relevant (or irrelevant))
    virtual void entityAdded(Entity*, const list<Component*>&)=0;
    virtual void entityRemoved(Entity*, const list<Component*>&)=0;

    GameManager& getGameManager();

    unordered_set<Entity*> entities; //List of relevant entities for the system
    list<ComponentType> neededComponents; //Defines what components are used
    string name; //Used when reporting information like time taken to update

  private:
    GameManager& gm; //So it can get info on the entities
};
#endif
