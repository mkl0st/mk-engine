#version 330 core

out vec4 FragColor;

uniform vec3 fillColor;

void main()
{
  FragColor = vec4(fillColor, 1.f);
}
