#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H

#include <string>
#include <IL/il.h>
#include "helper/rendering/Sprite.h"

//Loads sprites and packs onto the least amount of textures possible
//to avoid having to switch between textures during rendering
class SpriteManager
{
  public:
    SpriteManager();
    ~SpriteManager();
    Sprite* loadSprite(std::string filename);
};
#endif
