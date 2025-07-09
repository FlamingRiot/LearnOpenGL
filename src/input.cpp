#include "input.hpp"

#include <glad/glad.h>
#include <glfw3.h>

#include "engine.hpp"

namespace input{

    static void checkExitKey(){
        if (glfwGetKey(engine::window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
            glfwSetWindowShouldClose(engine::window, true);
        }
    }

    void process(){
        checkExitKey();
    }
}
