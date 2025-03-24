#pragma once

#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>

class Triangle
{
	public:unsigned int VBO;
	public:unsigned int VAO;

	public:Triangle() {
		// Define shape vertices
		const float vertices[] = {
			-0.5f, -0.5f, 0.0f, 
			 0.5f, -0.5f, 0.0f,  
			 0.0f,  0.5f, 0.0f
		};

		// 1. Generate VAO & VBO
		glGenVertexArrays(1, &VAO); // (This specifies the lines below that the vertex attribute pointer initialization should be passed to that specific VAO address
		glGenBuffers(1, &VBO); // Creates a "reservation" for a future buffer
		// 2. Bind VAO & VBO
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO); // Sets the "reserved" buffer as the current working Array Buffer in the OpenGl-State
		/*
			Note : GL_STATIC_DRAW specifies to the GPU what kind of use we'll be doing of the passed data
			and thus gives it a better idea of where to place it in its memory (e.g. fast-write locations
			for GL_DYNAMIC_DRAW)
		*/
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// 3. Configure VAO
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		std::cout << "INFO: [VAO] " << VAO << ", [VBO] " << VBO << " created successfully\n";
	}
};