#include "Sprite.h"

Sprite::Sprite()
{ }

void Sprite::getPosition(int& outX, int& outY)
{
  outX = x;
  outY = y;
}

void Sprite::getSize(int& outWidth, int& outHeight)
{
  outWidth = width;
  outHeight = height;
}

GLuint Sprite::getTextureId()
{
  return texture->getId();
}
