#pragma once

namespace graphics{

    // Variables
    inline unsigned int defaultShaderProgram;

    // Rendering related functions
    void clearBackground(float r, float g, float b, float a);

    // Shader related functions
    void loadDefaultShaders();

    class Shader{
        unsigned int id;
        
    }
}