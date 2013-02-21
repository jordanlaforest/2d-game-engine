#include <list>
#include <map>
#include <string>
#include "GameManager.h"

using namespace std;

GameManager::GameManager() : nextId(0)
{ }

GameManager::~GameManager()
{
  auto it = entities.begin();
  while(it != entities.end()){
    delete it->first;
    it = entities.erase(it);
  }
}

Entity& GameManager::createEntity(const string& name)
{
  list<Component*> emptyList;
  //Currently making assumption that we won't overflow the id
  //that needs to be fixed
  Entity* newEnt = new Entity(this, nextId++, name);
  entities.insert(make_pair(newEnt, emptyList));
  entityChanged(newEnt);
  return *newEnt;
}

void GameManager::addComponentToEntity(const Entity* e, const Component* c)
{
  //add c to map for e
  auto it = entities.find(e);
  if( it != entities.end()){
    it->second.push_back(c);
    entityChanged(e);
  }else{
    //Could not add component
  }
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
  //For testing: 
  //Print each entities name and id
}

void GameManager::update()
{
  //Update each system
}

void GameManager::entityChanged(const Entity* e) const
{
  //loop through each system and call entityChanged
}
