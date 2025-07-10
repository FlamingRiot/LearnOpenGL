#pragma once

#include "shader.hpp"

namespace graphics{

    // Variables
    inline Shader baseShader;

    // Rendering related functions
    void clearBackground(float r, float g, float b, float a);

    // Shader related functions
    void loadDefaultShaders();
}