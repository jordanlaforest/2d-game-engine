#include <iostream>
#include "SpriteManager.h"

SpriteManager::SpriteManager()
{ }

SpriteManager::~SpriteManager()
{ }

Sprite& SpriteManager::loadSprite(std::string filename)
{
  std::cout << "Loading: " << filename << std::endl;

  return *(new Sprite()); //Oh god, just compile
}
