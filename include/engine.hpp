#pragma once 

#include <glad/glad.h>
#include <glfw3.h>

namespace engine {

    const int WINDOW_WIDTH = 400;
    const int WINDOW_HEIGHT = 300;

    inline GLFWwindow* window;

    void run();
}