#include <iostream>

#include "GameManager.h"
#include "Entity.h"
#include "components/Component.h"
#include "components/TransformComponent.h"
#include "systems/PrintTransformSystem.h"
#include "systems/RenderSystem.h"

using namespace std;

int main()
{
  GameManager gm;
  PrintTransformSystem pts(gm);
  RenderSystem rs(gm);
  gm.addSystem(pts);
  //gm.addSystem(rs);
  TransformComponent tc(10, 10);
  TransformComponent tc2(30, 30);
  TransformComponent tc3(5, 15);
  Entity& player = gm.createEntity("player");
  Entity& testEnt = gm.createEntity("test");
  Entity& testNoComp = gm.createEntity("testNoComp");
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
