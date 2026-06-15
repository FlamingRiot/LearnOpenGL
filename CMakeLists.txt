cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Link C and CXX compilers from my personal worktree when using Windows
# When on Linux, the compilers are automatically found (this is just and assumption)
if (WIN32)
    set(CMAKE_C_COMPILER "F:\\Programming\\Compilers\\gcc-16.1.0-gdb\\bin\\gcc.exe")
    set(CMAKE_CXX_COMPILER "F:\\Programming\\Compilers\\gcc-16.1.0-gdb\\bin\\g++.exe")
endif (WIN32)

project(ogl VERSION 1.0)
file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(ogl ${SRC_FILES})

# GLFW loading
add_library(glfw STATIC IMPORTED GLOBAL)
set_target_properties(glfw PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/GLFW/libglfw3.a
    INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/lib/GLFW/include
)

# GLAD loading
add_library(glad STATIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/GLAD/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/GLAD/include)

# Library links
target_link_libraries(ogl PRIVATE glad glfw)
# Load specific graphic libraries depending on the operating system used at build
if (WIN32) # Windows
    target_link_libraries(ogl PRIVATE opengl32)
else() # Linux
    target_link_libraries(ogl PRIVATE dl pthread X11 Xrandr Xi Xxf86vm Xcursor GL)
endif()

# Include directories
target_include_directories(ogl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)