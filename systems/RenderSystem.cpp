#include <iostream>
#include "RenderSystem.h"
#include "GameManager.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"

const glm::vec2 SCREEN_SIZE(800, 600); //Temp

RenderSystem::RenderSystem(GameManager& gameManager, const std::string& title)
                          : System(gameManager)
{
  //Component pattern
  neededComponents.push_back(TRANSFORM);
  neededComponents.push_back(SPRITE);

  //Init
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
  
  //Shader setup
  shaderProgram.addShaderFromFile(GL_VERTEX_SHADER, "data/shaders/render2d.vert");
  shaderProgram.addShaderFromFile(GL_FRAGMENT_SHADER, "data/shaders/sprite.frag");
  shaderProgram.linkShaders();

  //Matrix setup
  vpMatrix = glm::ortho<float>(0.0f, SCREEN_SIZE.x, SCREEN_SIZE.y, 0.0f);
  glm::vec3 eye = glm::vec3(0.0f, 0.0f, 1.0f);
  glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0f);
  glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
  vpMatrix *= glm::lookAt(eye, center, up);
  mvpLocation = glGetUniformLocation(shaderProgram.getProgram(),
                                            "mvpMatrix");
  //VBO setup
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

void RenderSystem::entityAdded(Entity* e, const list<Component*>& /*list*/)
{
  std::cout << "Entity added to RenderSystem: " << e->name << std::endl;
}
void RenderSystem::entityRemoved(Entity* e, const list<Component*>& /*list*/)
{
  std::cout << "Entity removed from RenderSystem: " << e->name << std::endl;
}

void RenderSystem::preUpdate()
{
  if(!glfwGetWindowParam(GLFW_OPENED)){
    getGameManager().stopGame();
    return;
  }
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUseProgram(shaderProgram.getProgram());

}

void RenderSystem::updateEntity(Entity& e)
{

  TransformComponent* transform = static_cast<TransformComponent*>(
                       getGameManager().getEntityComponent(e, TRANSFORM));
  SpriteComponent* spriteComponent = static_cast<SpriteComponent*>(
                       getGameManager().getEntityComponent(e, SPRITE));

  //These will be replaced with data from each entity
  int iWidth, iHeight;
  spriteComponent->sprite->getSize(iWidth, iHeight);
  float  width = iWidth;
  float height = iHeight;
  float rotation = 0;

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, spriteComponent->sprite->getTextureId());

  GLint textureLocation = glGetUniformLocation(shaderProgram.getProgram(),
                                                             "tex");
  glUniform1i(textureLocation, 0);

  glm::mat4 transformMatrix(1.0f);
  transformMatrix = glm::translate(transformMatrix, transform->position);
  transformMatrix = glm::scale(transformMatrix,
                               glm::vec3(width, height, 1.0f));
  transformMatrix = glm::rotate(transformMatrix,
                                rotation, glm::vec3(0.0f, 0.0f, -1.0f));

  glm::mat4 mvpMatrix = vpMatrix * transformMatrix;

  glUniformMatrix4fv(mvpLocation, 1,
                     GL_FALSE, glm::value_ptr(mvpMatrix));

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat),
                                               (char*)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat),
                                               (char*)0 + 3*sizeof(GLfloat));

  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glBindTexture(GL_TEXTURE_2D, 0);

  GLuint err = glGetError();
        if (err != GL_NO_ERROR)
                std::cerr << "OpenGL Error: " << std::hex << err << std::endl;

}

void RenderSystem::postUpdate()
{
  glUseProgram(0);
  glfwSwapBuffers();
}
