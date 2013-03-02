#include "Texture.h"

Texture::Texture()
{ }

GLuint Texture::getId()
{
  return id;
}

int Texture::getWidth()
{
  return width;
}

int Texture::getHeight()
{
  return height;
}
