#include <iostream>
#include "SpriteBatch.h"

SpriteBatch::SpriteBatch(unsigned int size)
    : currentTexture(NULL), renderCalls(0),
      bufIndex(0), indIndex(0), drawing(false)
{
  //Make sure size is divisible by VERTEX_SIZE * 4 (num vertices in square)
  //So when loaded to max capacity no space is wasted
  unsigned int actualSize = size - (size % (VERTEX_SIZE * 4));
  vertexBuffer = new GLfloat[actualSize];
  maxIndex = actualSize;

  //(size / (VERTEX_SIZE)) is the number of quads that can be stored
  //6 is the number of indices per quad
  unsigned int indicesSize = 6 * size / (VERTEX_SIZE * 4);
  indices = new GLuint[indicesSize];

  glGenBuffers(1, &vbo);
  
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  glEnableVertexAttribArray(0); //position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                        VERTEX_SIZE * sizeof(GLfloat),
                        (GLvoid*)0);
  glEnableVertexAttribArray(1); //tint
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE,
                        VERTEX_SIZE * sizeof(GLfloat),
                        (GLvoid*)( 3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(2); //texCoord
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
                        VERTEX_SIZE * sizeof(GLfloat),
                        (GLvoid*)( 7 * sizeof(GLfloat)));

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

SpriteBatch::~SpriteBatch()
{
  delete[] vertexBuffer;
  delete[] indices;
}

void SpriteBatch::begin(GLuint program)
{
  //std::cout << "in begin" << std::endl;
  if(drawing){
    std::cout << "You must call end() before calling begin() again." << std::endl;
    return;
  }
  drawing = true;
  bufIndex = 0;
  indIndex = 0;
  glUseProgram(program);
  textureLocation = glGetUniformLocation(program, "tex");
  vpMatLocation = glGetUniformLocation(program, "vpMatrix");
  
}

void SpriteBatch::draw(Sprite* s, glm::vec3 pos,
                  glm::vec2 scale, glm::vec4 tint, float rotation)
{

  checkFlush(s->getTexture());

  int width, height;
  int x, y;
  s->getSize(width, height);
  s->getPosition(x, y);

  glm::mat4 transform(1.0f);
  transform = glm::translate(transform, pos);
  transform = glm::scale(transform,
                         glm::vec3(width * scale.x, height * scale.y, 1.0f));
  transform = glm::rotate(transform, rotation, glm::vec3(0.0f, 0.0f, -1.0f));

  glm::vec4 vertexTL(0.0f, 0.0f, 0.0f, 1.0f);
  glm::vec4 vertexTR(1.0f, 0.0f, 0.0f, 1.0f);
  glm::vec4 vertexBR(1.0f, 1.0f, 0.0f, 1.0f);
  glm::vec4 vertexBL(0.0f, 1.0f, 0.0f, 1.0f);
  vertexTL = transform * vertexTL;
  vertexTR = transform * vertexTR;
  vertexBR = transform * vertexBR;
  vertexBL = transform * vertexBL;

  //Texture dimensions
  float tWidth  = static_cast<float>(currentTexture->getWidth());
  float tHeight = static_cast<float>(currentTexture->getHeight());

  glm::vec2 texTL(x / tWidth,
                  y / tHeight);
  glm::vec2 texTR((x + width) / tWidth,
                  y / tHeight);
  glm::vec2 texBR((x + width) / tWidth,
                  (y + height) / tHeight);
  glm::vec2 texBL(x / tWidth,
                  (y + height) / tHeight);

  addVertexData(vertexTL, tint, texTL);
  addVertexData(vertexTR, tint, texTR);
  addVertexData(vertexBR, tint, texBR);
  addVertexData(vertexBL, tint, texBL);
  addQuadIndices();
  
}

void SpriteBatch::end()
{
  //std::cout << "in end" << std::endl;
  if(!drawing){
    std::cout << "You must call begin() before calling draw()." << std::endl;
    return;
  }
  drawing = false;
  flush();
  glUseProgram(0);
}

void SpriteBatch::checkFlush(Texture* nextTexture)
{
  //std::cout << "in checkFlush" << std::endl;
  if(nextTexture == NULL){
    std::cout << "A texture on a sprite is null" << std::endl;
    return;
  }
  if(currentTexture == NULL){
    currentTexture = nextTexture;
  }
  if(currentTexture->getId() != nextTexture->getId() || bufIndex >= maxIndex){
    flush();
    currentTexture = nextTexture;
  }
  //std::cout << "after checkFlush" << std::endl;
}

void SpriteBatch::flush()
{
  render();
  bufIndex = 0;
  indIndex = 0;
}

void SpriteBatch::render()
{
  //std::cout << "in render" << std::endl;

  if(currentTexture == NULL){
    std::cout << "Warning: NULL texture" << std::endl;
  }else{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, currentTexture->getId());
    glUniform1i(textureLocation, 0);
  }
  glUniformMatrix4fv(vpMatLocation, 1, GL_FALSE, glm::value_ptr(vpMatrix));

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBindVertexArray(vao);
  glBufferData(GL_ARRAY_BUFFER, bufIndex * sizeof(GLfloat), vertexBuffer, GL_DYNAMIC_DRAW);
  //Print vectexData
  std::cout << "Vertex Data:";
  for(int i=0; i < bufIndex; i++){
    if(i % VERTEX_SIZE == 0) std::cout << std::endl;
    std::cout << vertexBuffer[i] << ", ";
  }
  std::cout << std::endl;

  glDrawElements(GL_TRIANGLES, indIndex, GL_UNSIGNED_INT, indices);
  //Print indices
  /*std::cout << "Indices:";
  for(int i=0; i < indIndex; i++){
    if(i % 6 == 0) std::cout << std::endl;
    std::cout << indices[i] << ", ";
  }
  std::cout << std::endl;*/

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void SpriteBatch::addQuadIndices()
{
  //Going for this kind of pattern for indices 0, 1, 2, 2, 3, 0
  unsigned int baseIndex = (indIndex / 6) * 4; //Number of quads drawn
                                               // by vertices per quad
  indices[indIndex++] = baseIndex;
  indices[indIndex++] = baseIndex+1;
  indices[indIndex++] = baseIndex+2;

  indices[indIndex++] = baseIndex+2;
  indices[indIndex++] = baseIndex+3;
  indices[indIndex++] = baseIndex;
}

void SpriteBatch::addVertexData(glm::vec4& pos, glm::vec4& tint,
                                glm::vec2& texCoords)
{
  vertexBuffer[bufIndex++] = pos.x;
  vertexBuffer[bufIndex++] = pos.y;
  vertexBuffer[bufIndex++] = pos.z;

  vertexBuffer[bufIndex++] = tint.x;
  vertexBuffer[bufIndex++] = tint.y;
  vertexBuffer[bufIndex++] = tint.z;
  vertexBuffer[bufIndex++] = tint.w;

  vertexBuffer[bufIndex++] = texCoords.x;
  vertexBuffer[bufIndex++] = texCoords.y;

}

void SpriteBatch::setvpMatrix(glm::mat4& newMatrix)
{
  vpMatrix = newMatrix;
}
