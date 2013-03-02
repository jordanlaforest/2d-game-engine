#version 330
layout(location = 0) in vec4 v_position;
layout(location = 1) in vec4 v_tint;
layout(location = 2) in vec2 v_texCoord;
uniform mat4 vpMatrix;

out vec2 f_texCoord;
out vec4 f_colour;
void main()
{
  f_colour = v_tint;
  f_texCoord = v_texCoord;
  gl_Position = vpMatrix * v_position;
}
