#include "shader.hpp"
#include "graphics.hpp"

#include <glad/glad.h>
#include <glfw3.h>

#include <iostream>

namespace graphics{

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
    "fragColor = vec4(1.0f, 1.0f, 1.0f, 1.0);"
    "}\n";

    // Debug functions
    static void checkShaderCompileStatus(unsigned int shaderId);
    static void checkProgramLinkStatus(unsigned int programId);

    // Internal functions
    static void compileShader(unsigned int shader, const char** shaderTxt);

    Shader::Shader() {}

    Shader::Shader(const char** vertexShaderTxt, const char** fragmentShaderTxt){
        // Create vertex shader
        unsigned int vertexShader;
        if (vertexShaderTxt != NULL){
            vertexShader = glCreateShader(GL_VERTEX_SHADER);
            compileShader(vertexShader, vertexShaderTxt);   
        }
        else vertexShader = baseVertexShader;

        // Create fragment shader
        unsigned int fragmentShader;
        if (fragmentShaderTxt != NULL){
            fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            compileShader(fragmentShader, fragmentShaderTxt);
        }
        else fragmentShader = baseFragmentShader;

        // Link to shader program
        int programId = glCreateProgram();
        glAttachShader(programId, vertexShader);
        glAttachShader(programId, fragmentShader);
        glLinkProgram(programId);
        checkProgramLinkStatus(programId);
        this->id = programId;

        // Clean single shaders
         if (vertexShaderTxt != NULL) glDeleteShader(vertexShader);
         if (fragmentShaderTxt != NULL) glDeleteShader(fragmentShader);
    }

    void loadGlShaders(){
        // Base vertex shader
        baseVertexShader = glCreateShader(GL_VERTEX_SHADER);
        compileShader(baseVertexShader, &vertexShaderSource);

        // Base fragment shader
        baseFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        compileShader(baseFragmentShader, &fragmentShaderSource);

        baseShader = Shader(NULL, NULL);
    }

    void useShader(Shader shader){
        glUseProgram(shader.id);
    }

    void useBaseShader(){
        glUseProgram(baseShader.id);
    }

    static void compileShader(unsigned int shader, const char** shaderTxt){
            glShaderSource(shader, 1, shaderTxt, NULL);
            glCompileShader(shader);
            checkShaderCompileStatus(shader);  
    }

    /*
        The following functions are used for Debug purposes
        and are related to shaders compilation. 
    */

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