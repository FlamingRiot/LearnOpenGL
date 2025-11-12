#version 330 core

layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec3 vertexColor;
layout (location = 2) in vec2 vertexTexCoord;

uniform mat4 transform;

out vec3 fragColor;
out vec2 fragTexCoord;

void main(){
    // Set fragment shader values
    fragColor = vertexColor;
    fragTexCoord = vertexTexCoord;

    // Set final vertex position
    gl_Position = transform * vec4(vertexPos, 1.0);
}