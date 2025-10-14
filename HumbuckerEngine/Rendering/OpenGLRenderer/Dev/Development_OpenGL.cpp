#include "Development_OpenGL.h"

#include <iostream>
#include <ostream>
#include <string>

#include "glad/glad.h"

namespace Rendering_GL
{
	constexpr float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	// Vertices and shader handles
	unsigned int VBO;
	unsigned int VAO;

	unsigned int vertexShaderHandle;
	unsigned int fragmentShaderHandle;
	unsigned int shaderProgramHandle; // Vertex and fragment shaders combined

	const char *vertexShaderSource =
			"#version 330 core\nlayout (location = 0) in vec3 aPos;\nvoid main()\n{\ngl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n}\0";

	const char *fragmentShaderSource =
			"#version 330 core\nout vec4 FragColor;\nvoid main()\n{\nFragColor = vec4(0.6f, 0.9f, 0.4f, 1.0f);\n}\0";

	void CheckShaderCompilationStatus(unsigned int &shaderHandle)
	{
		int success;
		char infoLog[512];
		glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shaderHandle, 512, NULL, infoLog);
			std::cout << "ERROR: Shader compilation failed\n" << infoLog << std::endl;
		}
		else
		{
			std::cout << "Shader compilation successful " << shaderHandle << std::endl;
		}
	}

	void CheckShaderProgramLinkStatus(unsigned int &shaderProgramHandle)
	{
		int success;
		char infoLog[512];
		glGetProgramiv(shaderProgramHandle, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shaderProgramHandle, 512, NULL, infoLog);
			std::cout << "ERROR: Shader link failed\n" << infoLog << std::endl;
		}
		else
		{
			std::cout << "Shader link successful " << shaderProgramHandle << std::endl;
		}
	}

	void InitVertexData()
	{
		// Done once unless the object changes frequently
		// Generate vertex buffer and pass it to GPU
		//TODO: Create a mesh/renderable object class/struct and a system for passing the data to gpu
		glGenBuffers(1, &VBO);
		glGenVertexArrays(1, &VAO);

		// 1. bind Vertex Array Object
		glBindVertexArray(VAO);
		// 2. copy our vertices array in a buffer for OpenGL to use
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// 3. then set the vertex attributes pointers
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
		glEnableVertexAttribArray(0);
	}

	void CompileShaders()
	{
		// Declare vertex shader and compile it
		//TODO: create a shader class/struct and a system for shader compilation
		vertexShaderHandle = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShaderHandle, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShaderHandle);
		// Check if shader was compiled successfully
		CheckShaderCompilationStatus(vertexShaderHandle);

		// Compile fragment shader
		fragmentShaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShaderHandle, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShaderHandle);
		CheckShaderCompilationStatus(fragmentShaderHandle);

		shaderProgramHandle = glCreateProgram();
		glAttachShader(shaderProgramHandle, vertexShaderHandle);
		glAttachShader(shaderProgramHandle, fragmentShaderHandle);
		glLinkProgram(shaderProgramHandle);

		// Delete shader objects as they are not needed after being linked into the program
		glDeleteShader(vertexShaderHandle);
		glDeleteShader(fragmentShaderHandle);
	}

	void Development_OpenGL::PrepareBuffers()
	{
		InitVertexData();
		CompileShaders();
	}

	void Development_OpenGL::RenderTriangle()
	{
		// Use our shader program when we want to render an object
		glUseProgram(shaderProgramHandle);

		// Now draw the object
		// Use the VAO (vertex array object)
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
}
