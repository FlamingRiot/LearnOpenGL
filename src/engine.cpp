#include "engine.hpp"

#include <glad/glad.h>
#include <glfw3.h>

#include "input.hpp"
#include "graphics.hpp"
#include <iostream>
#include <cmath>

namespace engine {

using namespace graphics;

// Callback functions declaration
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

static void loadWindow(){
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /*
        The tweak applied below on the window's dimensions is 
        due to a compatibility issue between GLFW and Wayland.
        For some reason, Wayland applies a scaling of 1.5 to its
        windows. This scaling is only communicated to GLFW after
        the first render loop iteration, thus creating on offset
        between the OpenGL drawing context and the framebuffer.
        Although some callback functions should be executed after
        this scaling, it seems there are not. Which is why the 
        best option in terms of performance is to scale down the 
        window at creation, so that it later gets its desired 
        dimensions. This way, the OpenGL context and the 
        framebuffer perfectly match. 
    */
    bool isWayland = std::getenv("WAYLAND_DISPLAY");
    float scale = WAYLAND_SCALE_RATIO - !isWayland * (WAYLAND_SCALE_RATIO - 1);
    window = glfwCreateWindow(WINDOW_WIDTH / scale, WINDOW_HEIGHT / scale, "LearnOpenGL", NULL, NULL);

    // Check for window creation, terminate if failed
    if (window == NULL){
        std::cout << "[GLFW] INFO : Failed to create window\n";
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);

    // Check GLAD loader, terminate if failed
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "[GLAD] ERROR : Failed to initialize\n" << std::endl;
        glfwTerminate();
    }
    // We can now access OpenGL functions

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    std::cout << "[GLFW] INFO : Window created successfully\n";
}

static void updateWindow(){

    // Fragment shader
    const char *fragmentShaderA = "#version 330 core\n"
    "uniform float time;"
    "out vec4 finalColor;\n"
    "in vec3 fragColor;\n"
    "void main()\n"
    "{\n"
    "float alpha = (sin(time) / 2.0) + 0.5;\n"
    "finalColor = vec4(fragColor.xy, alpha, 1.0);"
    "}\n";

    Shader shaderA = Shader(NULL, "src/shaders/fragment.fs");

    float vertices[] = {
        0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // top right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
       -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom left
       -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, // top left
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    // Create quad
    size_t vertexCount = sizeof(vertices) / sizeof(vertices[0]);
    size_t indexCount = sizeof(indices) / sizeof(indices[0]);
    Mesh quad = Mesh(vertices, vertexCount, indices, indexCount);
    quad.material.shader = shaderA;

    while (!glfwWindowShouldClose(window)){
        // Input
        input::process();

        // Render commands
        clearBackground(0.0f, 0.0f, 0.0f, 1.0f);

        // Shader manipulation
        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        int timeLocation = getShaderLocation(shaderA, "time");
        glUseProgram(shaderA.id);
        glUniform1f(timeLocation, timeValue);

        // Single VBO rendering
        drawMesh(quad);

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

    // Load base shader
    graphics::loadGlShaders();

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