#pragma once

#include "shader.hpp"
#include <cstddef>

namespace graphics{

    class Material{
        public:
            Shader shader;

        Material();
    };

    class Mesh{
        public:
            unsigned int verticesCount;
            unsigned int VBO;
            unsigned int VAO;
            Material material;

        Mesh(float* vertices, size_t count);
    };

    // Variables
    inline Shader baseShader;
    inline unsigned int baseVertexShader;
    inline unsigned int baseFragmentShader;

    // Rendering related functions
    void clearBackground(float r, float g, float b, float a);

    // Shader related functions
    void loadDefaultShaders();

    // Mesh related functions
    void drawMesh(Mesh mesh);
}