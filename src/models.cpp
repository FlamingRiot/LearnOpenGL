#include "models.hpp"
#include "shader.hpp"

#include <glad/glad.h>
#include <glfw3.h>

#include <iostream>

namespace graphics{

     Mesh::Mesh(float* vertices, size_t vertexCount, unsigned int* indices, size_t indexCount){

        this->vertexCount = vertexCount / 3;
        this->indexCount = indexCount;

        // Generate VAO
        glGenVertexArrays(1, &(this->VAO));        
        glBindVertexArray(this->VAO);

        // Generate VBO
        glGenBuffers(1, &(this->VBO));
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float), vertices, GL_STATIC_DRAW);

        // Generate EBO
        glGenBuffers(1, &(this->EBO));
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

        // Finalize VAO
        // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        // Color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        // Texture coordinates attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glBindVertexArray(0);

        // Set default material
        this->material = Material();

        // Set identity transform matrix
        // this->transform = glm::mat4(1.0f);
    }

    void drawMesh(Mesh mesh){
        useShader(mesh.material.shader);

        // Bind VBO attributes
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mesh.material.texture.ID);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, mesh.material.texture1.ID);

        glBindVertexArray(mesh.VAO);

        // Draw call
        glDrawElements(GL_TRIANGLES, mesh.indexCount, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
    }
}