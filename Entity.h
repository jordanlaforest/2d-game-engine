#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include "Component.h"
class GameManager;

class Entity
{
  friend class GameManager;
  //private:
  public:
    Entity(GameManager* gm, unsigned int i, const std::string& n="");
    Entity(); //Disable this because we always want id and gameManager assigned
    unsigned int id;
    GameManager* gameManager; //GameManager manages all entities components,
                              //So this allows it to pass that data along
  public:
    std::string name;

    int getId() const;

    Component* getComponent(ComponentType) const;
};
#endif
