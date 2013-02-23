#include <iostream>
#include "PrintTransformSystem.h"
#include "../components/Component.h"
#include "../components/TransformComponent.h"
#include "../GameManager.h"

PrintTransformSystem::PrintTransformSystem(GameManager& gameManager)
                                           : System(gameManager)
{
  //Set up the neededComponents list to be used as a pattern
  cout << "push_back" << endl;
  neededComponents.push_back(TRANSFORM);
  cout << neededComponents.size() << endl;
}

void PrintTransformSystem::update()
{
  auto it = entities.begin();
  while(it != entities.end()){
    Entity& e = **it;
    TransformComponent* transform = static_cast<TransformComponent*>(getGameManager().getEntityComponent(e, TRANSFORM));
    cout << e.name << ",\tx: " << transform->x << " y: " << transform->y << endl;
    it++;
  }
}
