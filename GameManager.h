#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <list>
#include <map>
#include "Entity.h"
#include "components/Component.h"
#include "systems/System.h"

using namespace std;

class GameManager
{
  public:
    GameManager();

    //Should be upgraded to take components
    Entity* createEntity(const string& name="");
    void addComponentToEntity(const Entity*, const Component*);
    void removeComponentFromEntity(const Entity*, const Component*);
    Component* getEntityComponent(const Entity*, ComponentType) const;

    void run();

  private:
    list<System*> systems;
    map<Entity*, list<Component*> > components;

    void update();
    void entityChanged(Entity*);

};
#endif
