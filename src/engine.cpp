#include "engine.hpp"

#include <glad/glad.h>
#include <glfw3.h>

#include "input.hpp"
#include "graphics.hpp"
#include <iostream>

namespace engine {

// Callback functions declaration
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

static void loadWindow(){
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(
        WINDOW_WIDTH / WAYLAND_SCALE_RATIO, 
        WINDOW_HEIGHT / WAYLAND_SCALE_RATIO, 
        "LearnOpenGL", NULL, NULL);

    if (window == NULL){
        std::cout << "[GLFW] INFO : Failed to create window\n";
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "[GLAD] ERROR : Failed to initialize\n" << std::endl;
        glfwTerminate();
    }

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    std::cout << "[GLFW] INFO : Window created successfully\n";
}

static void updateWindow(){

    // The code below and before render loop is to be run once
    // Define vertices
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    // Generate Vertex Buffer Object
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    // Bind VBO to the Array Buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Copy the defined data to the Array Buffer (which is linked to our current VBO)
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Define vertex attribute
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window)){
        // Input
        input::process();

        // Render commands
        graphics::clearBackground(0.0f, 0.0f, 0.0f, 1.0f);

        // Single VBO rendering
        glUseProgram(graphics::defaultShaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap buffers and check/call events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

static void closeWindow(){
    
    glfwTerminate();
}

void run(){
    // Load Engine
    loadWindow();
    graphics::loadDefaultShaders();

    // Update engine
    updateWindow();

    // Close and unload engine
    closeWindow();
}

static void setCallbackFunctions(){

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

// Callback functions definitions
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    glViewport(0, 0, w, h);
    std::cout << "Framebuffer changed : " << w << ' ' << h << '\n';
}

}