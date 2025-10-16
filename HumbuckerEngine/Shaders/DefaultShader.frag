#version 330 core
out vec4 FragColor;
in vec3 vecColor;

uniform float colorMultiplier;

void main()
{
    FragColor = colorMultiplier * vec4(vecColor, 1.0);
}