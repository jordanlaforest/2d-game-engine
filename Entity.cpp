#include <string>
#include "GameManager.h"
#include "Entity.h"

Entity::Entity(GameManager* gm, unsigned int i, const std::string& n)
               : gameManager(gm), id(i), name(n)
{ }

int Entity::getId() const
{
  return id;
}

Component* Entity::getComponent(ComponentType type) const
{
  //return gameManager->getEntityComponent(this, type);
  return NULL;
}


size_t EntityHash::operator()(Entity* const& e) const
{
  return e->getId();
}
