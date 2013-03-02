#version 330
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 in_texCoord;
uniform mat4 mvpMatrix;

out vec2 texCoord;
void main()
{
  texCoord = in_texCoord;
  gl_Position = mvpMatrix * position;
}
