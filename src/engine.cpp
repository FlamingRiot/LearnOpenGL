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
    window = glfwCreateWindow(
        WINDOW_WIDTH / (WAYLAND_SCALE_RATIO - !isWayland * 0.5), 
        WINDOW_HEIGHT / (WAYLAND_SCALE_RATIO - !isWayland * 0.5), 
        "LearnOpenGL", NULL, NULL);

    // Check for window creation
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