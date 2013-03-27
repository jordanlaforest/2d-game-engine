#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <list>
#include <unordered_map>
#include "Entity.h"
#include "components/Component.h"
#include "systems/System.h"

using namespace std;

/* The actual engine. It manages the systems, entities, and components.
 * entities and components are allocated de-allocated by this class
 * maybe systems should be as well?
 */
class GameManager
{
  public:
    GameManager();
    ~GameManager();

    //Creates an entity and adds it to the game
    //Should be upgraded to take components
    Entity& createEntity(const string& name="");
    /* Adds a component to an entity like so
     * gameManager.addComponentToEntity<Component>(entity); where Component is any subclass of Component
     * The components memory will be managed by this class
     */
    template<class Comp>
    Comp* addComponentToEntity(Entity&);
    // Remove a component from an entity with either a reference or type
    void removeComponentFromEntity(Entity&, Component&);
    void removeComponentFromEntity(Entity&, ComponentType);

    /* Adds a system to be run by the engine
     * systems are run in the order they are added
     */
    void addSystem(System&);
    void removeSystem(System&);
    //Gets the (first) component of the specified type from the entity
    Component* getEntityComponent(Entity&, ComponentType) const;

    //Exit the game loop and return from run()
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

template<class Comp>
Comp* GameManager::addComponentToEntity(Entity& e)
{
  auto it = entities.find(&e);
  if( it != entities.end()){
    Comp* c = new Comp;
    it->second.push_back(c);
    entityChanged(e);
    return c;
  }else{
    //Could not add component
	return NULL;
  }
}

#endif
