#include <string>
#include "GameManager.h"
#include "Entity.h"

Entity::Entity(unsigned int i, const std::string& n)
               : id(i), name(n)
{ }

int Entity::getId() const
{
  return id;
}
