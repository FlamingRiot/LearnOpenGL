#include "engine.hpp"

#include <glad/glad.h>
#include <glfw3.h>

#include "input.hpp"
#include "graphics.hpp"
#include <iostream>

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

    // Vertex shader 
    const char *vertexShaderA = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

    // Fragment shader
    const char *fragmentShaderA = "#version 330 core\n"
    "out vec4 fragColor;\n"
    "void main()\n"
    "{\n"
    "fragColor = vec4(5.0f, 0.0f, 1.0f, 1.0);"
    "}\n";

    // Fragment shader
    const char *fragmentShaderB = "#version 330 core\n"
    "out vec4 fragColor;\n"
    "void main()\n"
    "{\n"
    "fragColor = vec4(0.0f, 1.0f, 0.5f, 1.0);"
    "}\n";

    Shader shaderA = Shader(&vertexShaderA, &fragmentShaderA);
    Shader shaderB = Shader(&vertexShaderA, &fragmentShaderB);

    // Exercise (Two VBOs and two shaders)
    float verticesA[] = {
        0.5f,  0.3f, 0.0f, 
        0.5f, -0.5f, 0.0f,
       -0.3f, -0.5f, 0.0f,
    };

    float verticesB[] = {
       -0.5f,  0.5f, 0.0f, 
        0.3f,  0.5f, 0.0f,
       -0.5f, -0.3f, 0.0f,
    };

    // First mesh
    size_t countA = sizeof(verticesA) / sizeof(verticesA[0]);
    Mesh triangleA = Mesh(verticesA, countA);
    triangleA.material.shader = shaderA;

    // Second mesh
    size_t countB = sizeof(verticesB) / sizeof(verticesB[0]);
    Mesh triangleB = Mesh(verticesB, countB);
    triangleB.material.shader = shaderB;

    // -----------------------------------

    float vertices[] = {
        0.5f,  0.5f, 0.0f, // top right
        0.5f, -0.5f, 0.0f, // bottom right
       -0.5f, -0.5f, 0.0f, // bottom left
       -0.5f,  0.5f, 0.0f // top left
    };

    // Define vertex attribute [VAO]
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generate Vertex Buffer Object [VBO]
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    // Bind VBO to the Array Buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Copy the defined data to the Array Buffer (which is linked to our current VBO)
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    // Generate Element Buffer Object [EBO]
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    // Bind EBO to the Element Array Buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // // Then set vertex attribute pointers [VAO]
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window)){
        // Input
        input::process();

        // Render commands
        clearBackground(0.0f, 0.0f, 0.0f, 1.0f);

        // Single VBO rendering
        graphics::useBaseShader();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        drawMesh(triangleA);
        drawMesh(triangleB);

        glBindVertexArray(0);

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