#include <iostream>
#include <list>
#include "System.h"

System::System(GameManager& gameManager) : gm(gameManager)
{ }

void System::entityChanged(Entity* e, const list<Component*>& list)
{
  cout << "Entity changed: " << e->name << endl;
  auto neededIt = neededComponents.begin();
  for(; neededIt != neededComponents.end(); neededIt++){
    auto entityComponentsIt = list.begin();
    for(; entityComponentsIt != list.end(); entityComponentsIt++){
      if(*neededIt == (*entityComponentsIt)->getType())
        break; //Found this component
    }
    if(entityComponentsIt == list.end())
      break; //A neededComponent was not found, can stop searching now
    //else continue to next
  }
  if(neededIt == neededComponents.end()){ //Reached end of loop, pattern matched
    cout << "Match to system: " << e->name << endl;
    if(entities.count(e) == 0){
      entities.insert(e);
      //entityAdded
    }
  }else{
    cout << "Non-Match to system: " << e->name << endl;
    if(entities.count(e) == 1){
      entities.erase(e);
      //entityRemoved
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

GameManager& System::getGameManager()
{
  return gm;
}
