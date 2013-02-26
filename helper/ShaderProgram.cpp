#include <iostream>
#include "ShaderProgram.h"

ShaderProgram::ShaderProgram() : program(0)
{
  
}

ShaderProgram::~ShaderProgram()
{
  glDeleteProgram(program); //program == 0 is ignored by OpenGL
}

bool ShaderProgram::addShaderFromString(GLenum shaderType,
                                        const std::string& shaderString)
{
  GLuint shader = glCreateShader(shaderType);
  const char *cString = shaderString.c_str();
  glShaderSource(shader, 1, &cString, NULL);
  glCompileShader(shader);
  GLint status;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if(!status){
    GLint infoLen;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
    GLchar *info = new GLchar[infoLen+1];
    glGetShaderInfoLog(shader, infoLen, NULL, info);

    std::cerr << "Error compiling shader: " << info << std::endl;
    delete[] info;
    return false;
  }

  shaders.push_back(shader);
  return true;
}

bool ShaderProgram::addShaderFromFile(GLenum shaderType,
                                        const std::string& shaderFilename)
{
  //Load file then call addShaderFromString
}

bool ShaderProgram::linkShaders()
{
  if(shaders.size() == 0)
    return false;
  program = glCreateProgram();

  auto it = shaders.begin();
  while(it != shaders.end()){
    glAttachShader(program, *it);
    it++;
  }

  glLinkProgram(program);

  GLint status;
  glGetProgramiv(program, GL_LINK_STATUS, &status);
  if(!status){
    GLint infoLen;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);
    GLchar *info = new GLchar[infoLen+1];
    glGetProgramInfoLog(program, infoLen, NULL, info);
    
    std::cerr << "Error linking program: " << info << std::endl;
    delete[] info;
    program = 0;
    return false;
  }

  it = shaders.begin();
  while(it != shaders.end()){
    glDetachShader(program, *it);
    glDeleteShader(*it);
    it++;
  }

  shaders.clear();

  return true;
}

GLuint ShaderProgram::getProgram()
{
  return program; //Set to zero originally so will be zero until it's ready
}
