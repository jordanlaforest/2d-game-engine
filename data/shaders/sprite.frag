#version 330
uniform sampler2D tex;

in vec2 f_texCoord;
in vec4 f_colour;

out vec4 outputColor;
void main()
{
  outputColor = texture2D(tex, f_texCoord) * f_colour;
}
