#include "shader.hpp"
#include "graphics.hpp"

#include <glad/glad.h>
#include <glfw3.h>

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>

namespace graphics{

    // Default shaders definition
    // Vertex shader 
    const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aCol;\n"
    "out vec3 fragColor;\n"
    "void main()\n"
    "{\n"
    " fragColor = aCol;\n"
    " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

    // Fragment shader
    const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 finalColor;\n"
    "in vec3 fragColor;\n"
    "void main()\n"
    "{\n"
    "finalColor = vec4(fragColor, 1.0);"
    "}\n";

    // Debug functions
    static void checkShaderCompileStatus(unsigned int shaderId);
    static void checkProgramLinkStatus(unsigned int programId);

    // Internal functions
    static void compileShader(unsigned int shader, const char** shaderTxt);
    static std::string readCodeFromFile(const char* codePath);

    Shader::Shader() {}

    Shader::Shader(const char* vertexFile, const char* fragmentFile){
        // Create vertex shader
        unsigned int vertexShader;
        if (vertexFile != NULL){
            vertexShader = glCreateShader(GL_VERTEX_SHADER);
            // Retrieve shader data from file
            std::string vertexCode = readCodeFromFile(vertexFile);
            const char* cVertexCode = vertexCode.c_str();
            if (vertexCode != "") compileShader(vertexShader, &cVertexCode);
            else vertexShader = baseVertexShader;
        }
        else vertexShader = baseVertexShader;

        // Create fragment shader
        unsigned int fragmentShader;
        if (fragmentFile != NULL){
            fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            // Retrieve shader data from file
            std::string fragmentCode = readCodeFromFile(fragmentFile);
            const char* cFragmentCode = fragmentCode.c_str();
            if (fragmentCode != "") compileShader(fragmentShader, &cFragmentCode);
            else fragmentShader = baseFragmentShader;
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
         if (vertexFile != NULL) glDeleteShader(vertexShader);
         if (fragmentFile != NULL) glDeleteShader(fragmentShader);
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

    int getShaderLocation(Shader shader, const char* uniform){
        return glGetUniformLocation(shader.id, uniform);
    }

    static void compileShader(unsigned int shader, const char** shaderTxt){
            glShaderSource(shader, 1, shaderTxt, NULL);
            glCompileShader(shader);
            checkShaderCompileStatus(shader);  
    }

    static std::string readCodeFromFile(const char* codePath){
        std::string code;
        std::ifstream codeFile;
        // Ensure ifstream can throw exceptions
        codeFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        try{
            // Open file
            codeFile.open(codePath);
            std::stringstream codeStream;
            codeStream << codeFile.rdbuf();
            codeFile.close();
            code = codeStream.str();
            return code;
        }
        catch (std::ifstream::failure e){
            std::cout << "[FILE] Path to the file : " << codePath << std::endl;
            std::cerr << "[SHADER] INFO : Shader file could not be read : " << strerror(errno) << std::endl;
            return "";
        }
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