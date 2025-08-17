#version 330 core

// Input values (from vertex shader);
in vec3 fragColor;
in vec2 fragTexCoord;

// Custom uniform values
uniform float time;
uniform sampler2D texture0;
uniform sampler2D texture1;

// Out color buffer
out vec4 finalColor;

void main(){
    // Calculate time-relative color modifier
    float alpha = (sin(time) / 2.0) + 0.5;
    vec4 freakyColor = vec4(fragColor.xy, alpha, 1.0);

    // Sample textures
    vec4 texelColor1 = texture(texture0, fragTexCoord);
    vec4 texelColor2 = texture(texture1, fragTexCoord);

    // Return final color
    finalColor = texelColor2;
}