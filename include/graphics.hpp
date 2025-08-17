#pragma once

#include "shader.hpp"
#include "textures.hpp"
#include <cstddef>

namespace graphics{

    class Mesh{
        public:
            unsigned int VBO;
            unsigned int VAO;
            unsigned int EBO = 0;
            
            size_t vertexCount = 0;
            size_t indexCount = 0;
            
            Material material;

            Mesh(float* vertices, size_t vertexCount, unsigned int* indices, size_t indexCount);
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