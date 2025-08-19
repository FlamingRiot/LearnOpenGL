#pragma once

#include "shader.hpp"
#include "textures.hpp"

namespace graphics{

    // Variables
    inline Shader baseShader;
    inline unsigned int baseVertexShader;
    inline unsigned int baseFragmentShader;

    // Rendering related functions
    void clearBackground(float r, float g, float b, float a);

    // Shader related functions
    void loadDefaultShaders();
}