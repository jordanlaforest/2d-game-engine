#include <list>
#include <map>
#include <string>
#include <iostream>
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
  entityChanged(*newEnt);
  return *newEnt;
}

void GameManager::addComponentToEntity(Entity& e, Component& c)
{
  auto it = entities.find(&e);
  if( it != entities.end()){
    it->second.push_back(&c);
    entityChanged(e);
  }else{
    //Could not add component
  }
}

void GameManager::removeComponentFromEntity(Entity& e, Component& c)
{
  auto it = entities.find(&e);
  if( it != entities.end()){
    auto listIt = it->second.begin();
    for(; listIt != it->second.end(); listIt++){
      if(*listIt == &c)
        break;
    }
    if(listIt != it->second.end()){
      it->second.erase(listIt);
    }else{
      //Could not find component
    }
  }else{
    //Could not find entity
  }
  //remove c from map for e
  //call entityChanged
}

Component* GameManager::getEntityComponent(const Entity& e, ComponentType t) const
{
  //loop through component list in map
  //return specified component
}

void GameManager::run()
{
  //start the game (game loop, etc)
  //For testing: 
  //Print each entities name and id
  for(auto it = entities.begin(); it != entities.end(); it++){
    cout << "Entity name: " << it->first->name << ", id: "
         << it->first->getId() << endl;
    cout << "Components:" << endl;
    for(auto listIt = it->second.begin(); listIt != it->second.end(); listIt++){
      cout << "\t" << (*listIt)->getType() << endl;
    }
  }
}

void GameManager::update()
{
  //Update each system
}

void GameManager::entityChanged(const Entity& e) const
{
  //loop through each system and call entityChanged
}
