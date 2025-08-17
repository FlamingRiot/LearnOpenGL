#version 330 core

// Input values (from vertex shader);
in vec3 fragColor;
in vec2 fragTexCoord;

// Custom uniform values
uniform float time;
uniform sampler2D texture0;

// Out color buffer
out vec4 finalColor;

void main(){
    float alpha = (sin(time) / 2.0) + 0.5;
    // finalColor = vec4(fragColor.xy, alpha, 1.0);
    vec4 texelColor = texture(texture0, fragTexCoord);
    finalColor = texelColor;
}