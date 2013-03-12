#include <iostream>
#include "RenderSystem.h"
#include "GameManager.h"
#include "components/TransformComponent.h"
#include "components/SpriteComponent.h"

const glm::vec2 SCREEN_SIZE(800, 600); //Temp

RenderSystem::RenderSystem(GameManager& gameManager,
                           const std::string& title,
                           unsigned int numLayers)
                          : System(gameManager, "RenderSystem")
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
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  spriteBatch = new SpriteBatch(32 * 100);
  numDrawLayers = numLayers;
  //We need one less then that amount of vectors because we will draw layer 0
  //While populating these vectors
  drawLayers  = new std::vector<Entity*>[numDrawLayers-1];
  
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

  spriteBatch->setvpMatrix(vpMatrix);
}

RenderSystem::~RenderSystem()
{
  delete[] drawLayers;
  delete spriteBatch;
  glfwTerminate();
}

void RenderSystem::update()
{
  preUpdate();

  //Loop through each entity, placing the ones that are on the screen
  //in the list for its layer
  auto it = entities.begin();
  while(it != entities.end()){
    Entity& e = **it;
    TransformComponent* transform = static_cast<TransformComponent*>(
                         getGameManager().getEntityComponent(e, TRANSFORM));
    SpriteComponent* spriteComponent = static_cast<SpriteComponent*>(
                         getGameManager().getEntityComponent(e, SPRITE));

    int x = transform->position.x;
    int y = transform->position.y;
    int width, height;
    spriteComponent->sprite->getSize(width, height);
 
    width  *= transform->scale.x;
    height *= transform->scale.y;
 
    if(x <= SCREEN_SIZE.x && y <= SCREEN_SIZE.y
       && x + width >= 0 && y + height >= 0){
      if(spriteComponent->layer == 0){  //Might as well draw the first layer now
        spriteBatch->draw(spriteComponent->sprite, transform->position,
                          transform->scale, spriteComponent->tint,
                          transform->rotation);
      }else{
        if(spriteComponent->layer >= numDrawLayers - 1){ //clamp e.layer
          //We've already drawn layer 0 so we use -2 to fill the 0th position
          drawLayers[numDrawLayers-2].push_back(&e);
        }else{
          //-1 to fill in 0th position
          drawLayers[spriteComponent->layer-1].push_back(&e);
        }
      }
    }
    it++;
  }
  
  //Loop through each layer drawing each entity in each
  for(unsigned int i=0; i < numDrawLayers-1; i++){
    auto it = drawLayers[i].begin();
    while(it != drawLayers[i].end()){
      Entity& e = **it;
      TransformComponent* transform = static_cast<TransformComponent*>(
                           getGameManager().getEntityComponent(e, TRANSFORM));
      SpriteComponent* spriteComponent = static_cast<SpriteComponent*>(
                           getGameManager().getEntityComponent(e, SPRITE));
      spriteBatch->draw(spriteComponent->sprite, transform->position,
                           transform->scale, spriteComponent->tint,
                           transform->rotation);
      it++;
    }
    //Done with this layer
    drawLayers[i].clear();
  }
  postUpdate();

  GLuint err = glGetError();
  if (err != GL_NO_ERROR){
    std::cerr << "OpenGL Error: " << std::hex << err << std::endl;
    exit(1);
  }
}

void RenderSystem::preUpdate()
{
  if(!glfwGetWindowParam(GLFW_OPENED)){
    getGameManager().stopGame();
  }
  glClear(GL_COLOR_BUFFER_BIT);

  spriteBatch->begin(shaderProgram.getProgram());
}

void RenderSystem::postUpdate()
{
  spriteBatch->end();
  glfwSwapBuffers();
}
