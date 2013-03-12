#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include "components/Component.h"
class GameManager;

class Entity
{
  friend class GameManager;
  private:
    Entity(unsigned int i, const std::string& n="");
    Entity(); //Disable this because we always want id assigned
    unsigned int id;
    GameManager* gameManager; //GameManager manages all entities components,
                              //So this allows it to pass that data along
  public:
    std::string name;

    int getId() const;
};
#endif
