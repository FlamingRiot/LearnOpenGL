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

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL){
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
    }

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    std::cout << "[GLFW] Window successfully created\n";
}

static void updateWindow(){

    while (!glfwWindowShouldClose(window)){
        // Input
        input::process();

        // Render commands
        graphics::clearBackground(0.8f, 1.0f, 0.8f, 1.0f);

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
    glViewport(0, 0, width, height);
}

}