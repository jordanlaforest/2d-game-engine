#include <iostream>
#include "PrintTransformSystem.h"
#include "Component.h"
#include "TransformComponent.h"
#include "GameManager.h"

PrintTransformSystem::PrintTransformSystem(GameManager& gameManager)
                                           : System(gameManager)
{
  //Set up the neededComponents list to be used as a pattern
  neededComponents.push_back(TRANSFORM);
}

void PrintTransformSystem::entityAdded(Entity*, const list<Component*>&)
{

}
void PrintTransformSystem::entityRemoved(Entity*, const list<Component*>&)
{

}

void PrintTransformSystem::preUpdate()
{

}

void PrintTransformSystem::updateEntity(Entity& e)
{
    TransformComponent* transform = static_cast<TransformComponent*>(getGameManager().getEntityComponent(e, TRANSFORM));
    cout << e.name << ",\tx: " << transform->position.x << " y: " << transform->position.y << endl;
}

void PrintTransformSystem::postUpdate()
{

}
