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

    //Should be upgraded to take components
    Entity& createEntity(const string& name="");
    void addComponentToEntity(Entity&, Component&);
    void removeComponentFromEntity(const Entity&, const Component&);
    Component* getEntityComponent(const Entity&, ComponentType) const;

    void run();

  private:
    list<System*> systems;
    unordered_map<Entity*, list<Component*> > entities;
    unsigned int nextId;

    void update();
    void entityChanged(const Entity&) const;

};
#endif
