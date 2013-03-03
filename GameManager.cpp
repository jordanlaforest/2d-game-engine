#include <list>
#include <map>
#include <string>
#include <iostream>
#include <GL/glfw.h>
#include "GameManager.h"
#include "PrintTransformSystem.h"

using namespace std;

GameManager::GameManager() : nextId(0), isRunning(false)
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
  Entity* newEnt = new Entity(nextId++, name);
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
      entityChanged(e);
    }else{
      //Could not find component
    }
  }else{
    //Could not find entity
  }
}

void GameManager::removeComponentFromEntity(Entity& e, ComponentType t)
{
  auto it = entities.find(&e);
  if( it != entities.end()){
    auto listIt = it->second.begin();
    for(; listIt != it->second.end(); listIt++){
      if((*listIt)->getType() == t)
        break;
    }
    if(listIt != it->second.end()){
      it->second.erase(listIt);
      entityChanged(e);
    }else{
      //Could not find component
    }
  }else{
    //Could not find entity
  }
}

void GameManager::addSystem(System& sys)
{
  systems.push_back(&sys);
  auto it = entities.begin();
  while(it != entities.end()){
    sys.entityChanged(it->first, it->second);
    it++;
  }
}
void GameManager::removeSystem(System& sys)
{
  auto it = systems.begin();
  while(it != systems.end()){
    if(*it == &sys){
      systems.erase(it);
    }
    it++;
  }
}

Component* GameManager::getEntityComponent(Entity& e, ComponentType t) const
{
  auto it = entities.find(&e);
  if( it != entities.end()){
    auto listIt = it->second.begin();
    for(; listIt != it->second.end(); listIt++){
      if((*listIt)->getType() == t)
        return *listIt;
    }
    //Could not find component
  }else{
    //Could not find entity
  }
  return NULL;
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

  isRunning = true;
  while(isRunning){
    double beforeTime = glfwGetTime();
    update();
    double timeTaken = glfwGetTime() - beforeTime;
    cout << "Frame took " << timeTaken * 1000 << " ms which is "
         << 1 / timeTaken << " fps" << endl;
  }
}

void GameManager::stopGame()
{
  isRunning = false;
}

void GameManager::update()
{
  auto it = systems.begin();
  while(it != systems.end()){
    double beforeTime = glfwGetTime(); //Requires having called glfwInit
    (*it)->update();
    double timeTaken = glfwGetTime() - beforeTime;
    cout << (*it)->getName() << " took " << timeTaken * 1000 << " ms" << endl;
    it++;
  }
}

void GameManager::entityChanged(Entity& e) const
{
  auto it = systems.begin();
  const list<Component*>& list = entities.find(&e)->second;
  while(it != systems.end()){
    (*it)->entityChanged(&e, list);
    it++;
  }
}
