#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <list>
#include <unordered_map>
#include "Entity.h"
#include "Component.h"
#include "System.h"

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
    void addSystem(System&);    //The order they are added is the order
    void removeSystem(System&); //they will run in
    //Gets the (first) component of the specified type from the entity
    Component* getEntityComponent(Entity&, ComponentType) const;

    void stopGame();

    //start the game, doesn't return until game is finished executing
    void run();

  private:
    list<System*> systems;
    unordered_map<Entity*, list<Component*> > entities; //and their components
    unsigned int nextId; //for entities
    bool isRunning;

    //called from the game loop, updates all systems
    void update();
    //lets all the systems know an entity's component list has changed
    void entityChanged(Entity&) const;

};
#endif
