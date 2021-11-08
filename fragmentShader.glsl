#version 330 core

out vec4 FragColor;

uniform float outRed;
uniform float outGreen;
uniform float outBlue;

void main()
{
    FragColor = vec4(outRed, outGreen, outBlue, 1.0);
}