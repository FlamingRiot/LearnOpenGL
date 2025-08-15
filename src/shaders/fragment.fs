#version 330 core

// Input values (from vertex shader);
in vec3 fragColor;

// Custom uniform values
uniform float time;

// Out color buffer
out vec4 finalColor;

void main(){
    float alpha = (sin(time) / 2.0) + 0.5;
    finalColor = vec4(fragColor.xy, alpha, 1.0);
}