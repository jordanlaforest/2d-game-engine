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

GLuint getTextureId()
{
  return texture->getId();
}
