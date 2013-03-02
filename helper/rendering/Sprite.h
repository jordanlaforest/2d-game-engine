#ifndef SPRITE_H
#define SPRITE_H

#include <GL/glew.h>
#include "Texture.h"

class SpriteManager;

class Sprite
{
  friend class SpriteManager;

  private:
    Sprite();
    Texture* texture;
    int x, y; //On the texture, not in the world
    int width, height;

  public:
    void getPosition(int& outX, int& outY);
    void getSize(int& outWidth, int& outHeight);
    GLuint getTextureId();
    Texture* getTexture();
};
#endif
