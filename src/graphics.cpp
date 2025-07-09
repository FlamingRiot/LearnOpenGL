#include "graphics.hpp"

#include <glad/glad.h>
#include <glfw3.h>

#include <iostream>

namespace graphics{

    static void checkShaderCompileStatus(unsigned int shaderId);
    static void checkProgramLinkStatus(unsigned int programId);

    // Default shaders definition
    // Vertex shader 
    const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

    // Fragment shader
    const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 fragColor;\n"
    "void main()\n"
    "{\n"
    "fragColor = vec4(1.0f, 0.5f, 0.2f, 1.0);"
    "}\n";

    void clearBackground(float r, float g, float b, float a){
        // Clear framebuffer with a defined color
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void loadDefaultShaders(){
        // Load vertex shader
        unsigned int vertexShader;
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        checkShaderCompileStatus(vertexShader);

        // Load fragment shader
        unsigned int fragmentShader;
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);
        checkShaderCompileStatus(fragmentShader);

        // Link to shader program
        defaultShaderProgram = glCreateProgram();
        glAttachShader(defaultShaderProgram, vertexShader);
        glAttachShader(defaultShaderProgram, fragmentShader);
        glLinkProgram(defaultShaderProgram);
        checkProgramLinkStatus(defaultShaderProgram);
    }

    static void checkShaderCompileStatus(unsigned int shaderId){

        int success;
        char infoLog[512];
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

        if (!success){
            glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
            std::cout << "[SHADER] ERROR : Shader " << shaderId << " compilation failed : \n" << infoLog << '\n';
        }
        else{
            std::cout << "[SHADER] INFO : Shader " << shaderId << " compiled successfully\n";
        }
    }

    static void checkProgramLinkStatus(unsigned int programId){

        int success;
        char infoLog[512];
        glGetProgramiv(programId, GL_LINK_STATUS, &success);
        if (!success){
            glGetProgramInfoLog(programId, 512, NULL, infoLog);
            std::cout << "[SHADER] INFO : Failed to link program " << programId << '\n';
        }
        else{
            std::cout << "[SHADER] INFO : Program " << programId << " linked successfully\n";
        }
    }
}