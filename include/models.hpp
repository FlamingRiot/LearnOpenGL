#pragma once

#include "textures.hpp"

// GLM
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

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
            // glm::mat4 transform;

            Mesh(float* vertices, size_t vertexCount, unsigned int* indices, size_t indexCount);
    };

    // Mesh related functions
    void drawMesh(Mesh mesh);
}