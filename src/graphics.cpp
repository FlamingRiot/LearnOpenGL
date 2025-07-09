#include "graphics.hpp"

#include <glad/glad.h>
#include <glfw3.h>

namespace graphics{

    void clearBackground(){
        // Clear framebuffer with a defined color
        glClearColor(0.8f, 1.0f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
}