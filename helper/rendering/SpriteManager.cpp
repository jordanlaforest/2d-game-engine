#include <iostream>
#include <GL/glew.h>
#include <GL/glfw.h>
#include "SpriteManager.h"

SpriteManager::SpriteManager()
{
  if(ilGetInteger(IL_VERSION_NUM) < IL_VERSION)
  {
    std::cerr << "Wrong DevIL version" << std::endl;
    exit(1);
  }
  ilInit();
}

SpriteManager::~SpriteManager()
{ }

Sprite* SpriteManager::loadSprite(std::string filename)
{
  ILuint texId;
  ilGenImages(1, &texId);
  ilBindImage(texId);
  ILboolean success = ilLoadImage((const ILstring)filename.c_str());
  if(!success){
    std::cerr << "Error loading image: " << filename << std::endl;
    return NULL;
  }
  success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
  if(!success){
    std::cerr << "Error converting image: " << filename << std::endl;
    return NULL;
  }

  GLuint tex;
  glGenTextures(1, &tex);

  Texture* t = new Texture();
  t->id      = tex;
  t->width   = ilGetInteger(IL_IMAGE_WIDTH);
  t->height  = ilGetInteger(IL_IMAGE_HEIGHT);
  
  Sprite* s  = new Sprite();
  s->texture = t;
  s->x       = 0;
  s->y       = 0;
  s->width   = t->width;
  s->height  = t->height;

  glBindTexture(GL_TEXTURE_2D, tex);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, t->width, t->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, ilGetData());
  glBindTexture(GL_TEXTURE_2D, 0);

  ilDeleteImages(1, &texId);

  GLuint err = glGetError();
	if (err != GL_NO_ERROR)
		std::cerr << "OpenGL Error: " << std::hex << err << std::endl; 

  return s; 
}
