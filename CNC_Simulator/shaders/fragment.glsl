#version 330 core

in vec4 fragColor;  // Color passed from the vertex shader
out vec4 FragColor; // Final color output

void main()
{
    FragColor = fragColor;  // Directly pass the color
}
