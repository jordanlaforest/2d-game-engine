#include <iostream>

#include "GameManager.h"
#include "helper/rendering/SpriteManager.h"
#include "Entity.h"
#include "components/Component.h"
#include "components/TransformComponent.h"
#include "components/SpriteComponent.h"
#include "systems/PrintTransformSystem.h"
#include "systems/RenderSystem.h"

using namespace std;

int main()
{
  GameManager gm;
  RenderSystem rs(gm);
  SpriteManager sm;
  Sprite* s = sm.loadSprite("data/sprites/HorrifyingSmiley.png");
  Sprite* s2 = sm.loadSprite("data/sprites/Circle.png");
  cout << "TextureId: " << s->getTextureId() << endl;
  PrintTransformSystem pts(gm);
  //gm.addSystem(pts);
  gm.addSystem(rs);
  TransformComponent tc(100, 100); //player
  SpriteComponent    sc(s); //player
  sc.tint.g = 0.0f;
  TransformComponent tc3(500, 150);//test2
  SpriteComponent    sc3(s);
  Entity& player = gm.createEntity("player");
  Entity& test2 = gm.createEntity("test2");
  gm.addComponentToEntity(player, tc);
  gm.addComponentToEntity(player, sc);
  gm.addComponentToEntity(test2, tc3);
  gm.addComponentToEntity(test2, sc3);

  for(int i =0; i < 10; i++){
    Entity& e = gm.createEntity("whatevs");
    gm.addComponentToEntity(e, *(new TransformComponent((i * 100) % 800,
                                                        (i * 100) % 600)));
    SpriteComponent* spr;
    if(i % 2 == 0)
      spr = new SpriteComponent(s2);
    else
      spr = new SpriteComponent(s);
    spr->layer = i;
    gm.addComponentToEntity(e, *spr);
  }
  /*Component* c = gm.getEntityComponent(testEnt, TRANSFORM);
  if(c != NULL)
    cout << "Found. " << ((TransformComponent*)c)->position.x << endl;
  //gm.removeComponentFromEntity(testEnt, tc2);
  //gm.removeComponentFromEntity(testEnt, *c);
  gm.removeComponentFromEntity(testEnt, TRANSFORM);*/
  gm.run();
}
