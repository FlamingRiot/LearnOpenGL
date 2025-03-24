#include <iostream>
// Here order matters
#include <glad/glad.h>
#include <glfw3.h>
// Custom
#include "shapes.h";

#define ERROR_LOG_SIZE 512

// Callback functions' signatures
void framebuffer_resize_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window);

// Other object generation functions
int loadDefaultShaders();

// Vertex shader
const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

// Fragment shader
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 fragColor;\n"
"void main()\n"
"{\n"
" fragColor = vec4(1.0f, 0.0f, 1.0f, 1.0f);\n"
"}\0";

/// <summary>Represents the program's entrypoint.</summary>
/// <returns>Exit code of the program.</returns>
int main() {

	// Set GLFW window configurations
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create GLFW window object
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "ERROR: Failed to create GLFW window\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	std::cout << "INFO: Window was created successfully\n";

	// Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "ERROR: Failed to initialize GLAD\n"; 
		return -1;
	}

	// Set OpenGL viewport specifications
	glViewport(0, 0, 800, 600);

	// Create triangle to draw
	Triangle shape;

	// Load shader program
	int shaderProgram = loadDefaultShaders();

	// Register window-resize callback function to GLFW
	// The callback functions are registered after window creation and before render loop
	glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);

	// Specifies the values used by glClear to clear the color buffer
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Render loop
	while (!glfwWindowShouldClose(window)) {
		// Process the window's inputs
		process_input(window);

		// Clear the color buffer using the specified values from glClearColor
		glClear(GL_COLOR_BUFFER_BIT);

		// Rendering commands
		glUseProgram(shaderProgram);
		glBindVertexArray(shape.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Swaps the front and back buffers (avoids potential flickering)
		glfwSwapBuffers(window);
		// Checks if events are triggered, updates the window state and calls the corresponding functions which can be registered throught callbacks
		glfwPollEvents();
	}
	// Cleans the resources that were allocated by GLFW in the first place
	glfwTerminate();
	std::cout << "INFO: Window was closed successfully\n";

	return 0;
}

/// <summary>Resizes a GLFW viewport.</summary>
/// <param name="window">GLFW window to resize.</param>
/// <param name="width">New width.</param>
/// <param name="height">New height.</param>
void framebuffer_resize_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

/// <summary>Processes all the inputs of the window.</summary>
/// <param name="window">Window to process input in.</param>
void process_input(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		std::cout << "INFO: Window was closed successfully\n";
		glfwSetWindowShouldClose(window, true);
	}
}

/// <summary>Loads the default shader objects and activates the generated program.</summary>
int loadDefaultShaders() {

	int success;
	char infoLog[ERROR_LOG_SIZE];

	// Vertex shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(vertexShader, ERROR_LOG_SIZE, NULL, infoLog);
		std::cout << "ERROR: [SHADER] Default vertex shader compilation failed\n" << infoLog << '\n';
	}
	else std::cout << "INFO: [SHADER] Default vertex shader compiled successfully\n";

	// Fragment shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(fragmentShader, ERROR_LOG_SIZE, NULL, infoLog);
		std::cout << "ERROR: [SHADER] Default fragment shader compilation failed\n" << infoLog << '\n';
	}
	else std::cout << "INFO: [SHADER] Default fragment shader compiled successfully\n";

	// Create linked program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		// Send linking error
		glGetProgramInfoLog(shaderProgram, ERROR_LOG_SIZE, NULL, infoLog);
		std::cout << "ERROR: [SHADER] Failed to link default shader\n";
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	std::cout << "INFO: [SHADER] " << shaderProgram << " Shader program created successfully\n";

	return shaderProgram;
}