#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>
// #include <glad/glad.h> Already included with OpenGL

int main(){
    std::cout << "Hello World, Evan, I'm using GLFW Now, and GLAD !\n";

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window;

    return 0;
}