#include <list>
#include <map>
#include <string>
#include "GameManager.h"
#include "Entity.h"
#include "Component.h"
#include "System.h"

GameManager::GameManager()
{
  
}

Entity GameManager::createEntity(const std::string& name)
{
  //add entity to map
  //call entityChanged
}

void GameManager::addComponentToEntity(const Entity* e, const Component* c)
{
  //add c to map for e
  //call entityChanged
}

void GameManager::removeComponentFromEntity(const Entity*, const Component* c)
{
  //remove c from map for e
  //call entityChanged
}

Component* GameManager::getEntityComponent(const Entity* e, ComponentType t)
{
  //loop through component list in map
  //return specified component
}

void GameManager::run()
{
  //start the game (game loop, etc)
}

void GameManager::update()
{
  //Update each system
}

void GameManager::entityChanged(Entity*)
{
  //loop through each system and call entityChanged
}
