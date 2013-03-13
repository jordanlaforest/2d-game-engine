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
  Entity& player = gm.createEntity("player");
  TransformComponent* tc = gm.addComponentToEntity<TransformComponent>(player);
  tc->position.x = 100;
  tc->position.y = 100;
  SpriteComponent* sc = gm.addComponentToEntity<SpriteComponent>(player);
  sc->sprite = s;

  Entity& test2 = gm.createEntity("test2");
  //Might as well reuse these
  tc = gm.addComponentToEntity<TransformComponent>(test2);
  tc->position.x = 500;
  tc->position.y = 150;
  sc = gm.addComponentToEntity<SpriteComponent>(test2);
  sc->sprite = s2;

  for(int i =0; i < 1000; i++){
    Entity& e = gm.createEntity("whatevs");
    TransformComponent* tComp = gm.addComponentToEntity<TransformComponent>(e);
    tComp->position.x = (i * 100);// % 800;
    tComp->position.y = (i * 100);// % 600;
    SpriteComponent* spr = gm.addComponentToEntity<SpriteComponent>(e);
    if(i % 2 == 0)
      spr->sprite = s2;
    else
      spr->sprite = s;
    spr->layer = i;
  }
  gm.run();
}
