cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(ogl VERSION 1.0)
add_executable(ogl main.cpp lib/GLAD/glad.c)

# Library loading
find_library(GLFW glfw ${CMAKE_CURRENT_SOURCE_DIR}/lib/GLFW/libglfw3.a)

# GLAD loading
add_library(glad STATIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/GLAD/glad.c)
target_include_directories(glad PUBLIC 
${CMAKE_CURRENT_SOURCE_DIR}/lib/GLAD/include)

# Library links
target_link_libraries(ogl PUBLIC ${glfw})
target_link_libraries(ogl PRIVATE glad)
target_link_libraries(ogl PRIVATE dl pthread X11 Xrandr Xi Xxf86vm Xcursor GL)

# Include directories
target_include_directories(ogl PUBLIC 
${CMAKE_CURRENT_SOURCE_DIR}/lib/GLFW/include
${CMAKE_CURRENT_SOURCE_DIR}/include
)