#ifndef RENDER_SYSTEM
#define RENDER_SYSTEM

#include <string>
#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include "System.h"
#include "../helper/ShaderProgram.h"

class RenderSystem : public System
{
  public:
    RenderSystem(GameManager&, const std::string& title="Game Window");
    ~RenderSystem();
    void update();
  private:
    ShaderProgram shaderProgram;
    float vertexPos[12] = { 0.75f, 0.75f, 0.0f, 1.0f,
                          0.75f, -0.75f, 0.0f, 1.0f,
                          -0.75f, -0.75f, 0.0f, 1.0f };
    GLuint vbo;
    GLuint vao;
};
#endif
