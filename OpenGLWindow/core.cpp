#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>

#include "shapes.h"

void DrawTriangle(Triangle triangle) {
	glBindVertexArray(triangle.VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}

void DrawRectangle(Rectangle rectangle) {
	glBindVertexArray(rectangle.VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rectangle.EBO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}