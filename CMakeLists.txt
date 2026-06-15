# Define CMake requirements
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Link C and CXX compilers from my personal build system when using Windows
# When on Linux, the compilers are automatically found (probably due to the
# standardisation of the linux ecosystem)
if (WIN32)
    set(CMAKE_C_COMPILER "C:\\msys64\\mingw64\\bin\\gcc.exe")
    set(CMAKE_CXX_COMPILER "C:\\msys64\\mingw64\\bin\\g++.exe")
endif (WIN32)

# Project definition and files integration
project(ogl VERSION 1.0)
file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(ogl ${SRC_FILES})


# GLFW loading from an external source
# This prevents from having a humongous library source code lying in the project files
# (The probability of having to use a modified GLFW version is near null)
include(FetchContent)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)
FetchContent_MakeAvailable(glfw)

# GLAD loading
# The library being relatively small, it appeared to be easier to just 
# compile the source files locally, thus avoiding a FetchContent and keeping
# its build independant from any system. 
add_library(glad STATIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/GLAD/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/GLAD/include)

# Link GLFW and GLAD to the project
target_link_libraries(ogl PRIVATE glad glfw)

# Load specific graphic libraries depending on the operating system used at build
if (WIN32) # Windows
    target_link_libraries(ogl PRIVATE opengl32)
else() # Linux
    target_link_libraries(ogl PRIVATE dl pthread X11 Xrandr Xi Xxf86vm Xcursor GL)
endif()

# Specify the include directories of the project
target_include_directories(ogl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)