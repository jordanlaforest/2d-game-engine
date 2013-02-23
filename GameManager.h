#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <list>
#include <unordered_map>
#include "Entity.h"
#include "components/Component.h"
#include "systems/System.h"

using namespace std;

class GameManager
{
  public:
    GameManager();
    ~GameManager();

    //Creates an entity and adds it to the game
    //Should be upgraded to take components
    Entity& createEntity(const string& name="");
    void addComponentToEntity(Entity&, Component&);
    void removeComponentFromEntity(Entity&, Component&);
    void removeComponentFromEntity(Entity&, ComponentType);
    //Gets the (first) component of the specified type from the entity
    Component* getEntityComponent(Entity&, ComponentType) const;

    //start the game, doesn't return until game is finished executing
    void run();

  private:
    list<System*> systems;
    unordered_map<Entity*, list<Component*> > entities; //and their components
    unsigned int nextId; //for entities

    //called from the game loop, updates all systems
    void update();
    //lets all the systems know an entity's component list has changed
    void entityChanged(const Entity&) const;

};
#endif
