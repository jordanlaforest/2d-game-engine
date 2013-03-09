#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include <string>
#include <vector>
#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "System.h"
#include "ShaderProgram.h"
#include "SpriteBatch.h"

class RenderSystem : public System
{
  public:
    RenderSystem(GameManager&,
                 const std::string& title="Game Window",
                 unsigned int numLayers=8);
    ~RenderSystem();
    void update(); //We wan't more control over this
  protected:
    void preUpdate();
    void postUpdate();
    void entityAdded(Entity*, const list<Component*>&);
    void entityRemoved(Entity*, const list<Component*>&);
  private:
    unsigned int numDrawLayers;
    std::vector<Entity*>* drawLayers;
    ShaderProgram shaderProgram;
    SpriteBatch* spriteBatch;
    GLuint vbo;
    GLuint vao;
    glm::mat4 vpMatrix;
};
#endif
