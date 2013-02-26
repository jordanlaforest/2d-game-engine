#include <iostream>
#include "RenderSystem.h"
#include "../GameManager.h"

const glm::vec2 SCREEN_SIZE(800, 600); //Temp

RenderSystem::RenderSystem(GameManager& gameManager, const std::string& title)
                          : System(gameManager)
{
  if(!glfwInit()){
    cerr << "glfwInit() failed" << endl;
    exit(1);
  }
  glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
  glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
  if(!glfwOpenWindow(SCREEN_SIZE.x, SCREEN_SIZE.y,
                        8, 8, 8, 8, 0, 0, GLFW_WINDOW)){
    cerr << "glfwOpenWindow() failed. (Need OpenGL 3.2)" << endl;
    exit(1);
  }
  
  if(glewInit() != GLEW_OK){
    cerr << "glewInit() failed" << endl;
    exit(1);
  }
  if(!GLEW_VERSION_3_2){
    cerr << "OpenGL 3.2 API is not available" << endl;
  }

  glfwSetWindowTitle(title.c_str());

  glClearColor(0.3, 0.4, 0.8, 1.0);

  const std::string vertShader("#version 330\n"
                               "layout(location = 0) in vec4 position;\n"
                               "void main()\n"
                               "{\n"
                               "  gl_Position = position;\n"
                               "}\n");

  const std::string fragShader("#version 330\n"
                               "out vec4 outputColor;\n"
                               "void main()\n"
                               "{\n"
                               "  outputColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
                               "}\n");

  shaderProgram.addShaderFromString(GL_VERTEX_SHADER, vertShader);
  shaderProgram.addShaderFromString(GL_FRAGMENT_SHADER, fragShader);
  shaderProgram.linkShaders();


  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPos), vertexPos, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
}

RenderSystem::~RenderSystem()
{
  glfwTerminate();
}

void RenderSystem::update()
{
  if(!glfwGetWindowParam(GLFW_OPENED)){
    getGameManager().stopGame();
    return;
  }
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUseProgram(shaderProgram.getProgram());

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

  glDrawArrays(GL_TRIANGLES, 0, 3);

  glDisableVertexAttribArray(0);
  glUseProgram(0);

  glfwSwapBuffers();
}
