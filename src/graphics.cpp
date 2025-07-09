#include "graphics.hpp"

#include <glad/glad.h>
#include <glfw3.h>

namespace graphics{

    void clearBackground(float r, float g, float b, float a){
        // Clear framebuffer with a defined color
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);
    }
}