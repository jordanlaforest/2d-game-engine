#include <list>
#include <map>
#include <string>
#include "GameManager.h"

using namespace std;

GameManager::GameManager()
{
  
}

GameManager::~GameManager()
{
  auto it = entities.begin();
  while(it != entities.end()){
    delete it->first;
    //free all components in components list
    it = entities.erase(it);
  }
}

Entity& GameManager::createEntity(const string& name)
{
  list<Component*> emptyList;
  Entity* newEnt = new Entity(this, 0, name);
  entities.insert(make_pair(newEnt, emptyList));
  entityChanged(*newEnt);
  return *newEnt;
}

void GameManager::addComponentToEntity(const Entity* e, const Component* c)
{
  //add c to map for e
  //call entityChanged
}

void GameManager::removeComponentFromEntity(const Entity* e, const Component* c)
{
  //remove c from map for e
  //call entityChanged
}

Component* GameManager::getEntityComponent(const Entity* e, ComponentType t) const
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

void GameManager::entityChanged(const Entity&) const
{
  //loop through each system and call entityChanged
}
