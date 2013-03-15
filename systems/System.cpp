#include <iostream>
#include <list>
#include "System.h"

System::System(GameManager& gameManager, string n)
             : name(n), gm(gameManager)
{ }

System::~System()
{ }

void System::entityChanged(Entity* e, const list<Component*>& cList)
{
  cout << "Entity changed: " << e->name << endl;
  auto neededIt = neededComponents.begin();
  for(; neededIt != neededComponents.end(); neededIt++){
    auto entityComponentsIt = cList.begin();
    for(; entityComponentsIt != cList.end(); entityComponentsIt++){
      if(*neededIt == (*entityComponentsIt)->getType())
        break; //Found this component
    }
    if(entityComponentsIt == cList.end())
      break; //A neededComponent was not found, can stop searching now
    //else continue to next
  }
  if(neededIt == neededComponents.end()){ //Reached end of loop, pattern matched
    cout << "Match to system: " << e->name << endl;
    if(entities.count(e) == 0){
      entities.insert(e);
      entityAdded(e, cList);
    }
  }else{
    cout << "Non-Match to system: " << e->name << endl;
    if(entities.count(e) == 1){
      entities.erase(e);
      entityRemoved(e, cList);
    }
  }
}

void System::update()
{
  preUpdate();
  auto it = entities.begin();
  while(it != entities.end()){
    updateEntity(**it);
    it++;
  }
  postUpdate();
}

void System::preUpdate() {}
void System::postUpdate() {}
void System::updateEntity(Entity&) {}
void System::entityAdded(Entity*, const std::list<Component*>&) {}
void System::entityRemoved(Entity*, const std::list<Component*>&) {}

GameManager& System::getGameManager()
{
  return gm;
}

string& System::getName()
{
  return name;
}
