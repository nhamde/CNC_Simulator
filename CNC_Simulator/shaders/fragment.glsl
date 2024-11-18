#version 330 core

in vec3 fragNormal;      // Normal passed from the vertex shader
in vec3 fragPosition;    // Position passed from the vertex shader

uniform vec3 lightPosition;  // Position of the light in view space
uniform vec3 lightColor;     // Color of the light
uniform vec3 objectColor;    // Color of the object

out vec4 FragColor;

void main() {
    // Calculate the direction of the light
    vec3 lightDir = normalize(lightPosition - fragPosition);

    // Calculate the diffuse component
    float diff = max(dot(fragNormal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Final color (diffuse lighting only)
    vec3 result = diffuse * objectColor;

    FragColor = vec4(result, 1.0);
}
