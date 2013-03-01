#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>

class Texture
{
  friend class SpriteManager;

  private:
    Texture();
    GLuint id;
    int width, height;

  public:
    GLuint getId();
};
#endif
