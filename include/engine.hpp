#pragma once 

#include <glad/glad.h>
#include <glfw3.h>

namespace engine {

    // Constants
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;
    const float WAYLAND_SCALE_RATIO = 1.5f;

    // Variables
    inline GLFWwindow* window;

    // Functions
    void run();
}