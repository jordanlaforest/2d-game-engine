#include <iostream>

#include "GameManager.h"
#include "Entity.h"
#include "Component.h"
#include "TransformComponent.h"
#include "PrintTransformSystem.h"
#include "RenderSystem.h"

using namespace std;

int main()
{
  GameManager gm;
  PrintTransformSystem pts(gm);
  RenderSystem rs(gm);
  //gm.addSystem(pts);
  gm.addSystem(rs);
  TransformComponent tc(100, 100);
  TransformComponent tc2(300, 300);
  TransformComponent tc3(500, 150);
  Entity& player = gm.createEntity("player");
  Entity& testEnt = gm.createEntity("test");
  Entity& test2 = gm.createEntity("test2");
  gm.addComponentToEntity(player, tc);
  gm.addComponentToEntity(testEnt, tc2);
  gm.addComponentToEntity(test2, tc3);
  Component* c = gm.getEntityComponent(testEnt, TRANSFORM);
  if(c != NULL)
    cout << "Found. " << ((TransformComponent*)c)->position.x << endl;
  //gm.removeComponentFromEntity(testEnt, tc2);
  //gm.removeComponentFromEntity(testEnt, *c);
  gm.removeComponentFromEntity(testEnt, TRANSFORM);
  gm.run();
  //cout << "player: " << player.name << " " << player.getId() << endl;
}
