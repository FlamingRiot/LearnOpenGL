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

    Mesh::Mesh(float* vertices, size_t count){

        this->verticesCount = count / 3;

        // Generate VAO
        glGenVertexArrays(1, &(this->VAO));        
        glBindVertexArray(this->VAO);

        // Generate VBO
        glGenBuffers(1, &(this->VBO));
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), vertices, GL_STATIC_DRAW);

        // Finalize VAO
        glVertexAttribPointer(0, this->verticesCount, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Set default material
        this->material = Material();
    }

    void drawMesh(Mesh mesh){
        useShader(mesh.material.shader);
        glBindVertexArray(mesh.VAO);
        glDrawArrays(GL_TRIANGLES, 0, mesh.verticesCount);
        glBindVertexArray(0);
    }

    void clearBackground(float r, float g, float b, float a){
        // Clear framebuffer with a defined color
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);
    }
}