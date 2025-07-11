#include "graphics.hpp"
#include "shader.hpp"

#include <glad/glad.h>
#include <glfw3.h>

#include <iostream>

namespace graphics{

    // Type constructor definitions
    Material::Material(){
        this->shader = baseShader;
    }

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
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindVertexArray(0);

        // Set default material
        this->material = Material();
    }

    void drawMesh(Mesh mesh){
        useShader(mesh.material.shader);
        glBindVertexArray(mesh.VAO);

        // Draw call
        glDrawElements(GL_TRIANGLES, mesh.indexCount, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
    }

    void clearBackground(float r, float g, float b, float a){
        // Clear framebuffer with a defined color
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);
    }
}