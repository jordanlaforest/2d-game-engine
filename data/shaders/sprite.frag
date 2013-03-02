#version 330
uniform sampler2D tex;
in vec2 texCoord;
out vec4 outputColor;
void main()
{
  outputColor = texture2D(tex, texCoord);
}
