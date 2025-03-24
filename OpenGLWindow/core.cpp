#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>

#include "shapes.h"

void DrawTriangle(Triangle triangle) {
	glBindVertexArray(triangle.VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void DrawRectangle(Rectangle rectangle) {

}