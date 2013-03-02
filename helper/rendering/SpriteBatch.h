#ifndef SPRITE_BATCH_H
#define SPRITE_BATCH_H

#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Sprite.h"

//Number of floats per vertex
#define VERTEX_SIZE 9

class SpriteBatch
{
  public:
    SpriteBatch(unsigned int size);
    ~SpriteBatch();
    void begin(GLuint program);
    void draw(Sprite* s, glm::vec3 pos,
                        glm::vec2 scale,
                        glm::vec4 tint,
                        float rotation);
    void end();
    void flush();

    void setvpMatrix(glm::mat4& newMatrix);

  private:
    void checkFlush(Texture*);
    void render();
    void addVertexData(glm::vec4& pos, glm::vec4& tint, glm::vec2& texCoords);
    void addQuadIndices();

    Texture* currentTexture;
    int renderCalls;
    GLfloat* vertexBuffer;
    unsigned int bufIndex;
    GLuint*  indices;
    unsigned int indIndex;
    bool drawing;
    unsigned int maxIndex;
    glm::mat4 vpMatrix;
    GLint vpMatLocation;
    GLint textureLocation;
    GLint positionLocation;
    GLint texCoordLocation;
    
    GLuint vbo;
    GLuint vao;
};
#endif
