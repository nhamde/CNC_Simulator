#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

uniform mat4 modelView;
uniform mat4 projection;

out vec3 fragNormal;      // Normal in view space
out vec3 fragPosition;    // Position in view space

void main() {
    fragPosition = vec3(modelView * vec4(position, 1.0));
    fragNormal = normalize(mat3(transpose(inverse(modelView))) * normal);
    gl_Position = projection * vec4(fragPosition, 1.0);
}
