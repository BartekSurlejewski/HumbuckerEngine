#include "RenderingPreProcessor_OpenGL.h"
#include <iostream>
#include "glad/glad.h"
#include "../RenderingData.h"


namespace Rendering_GL
{
	void RenderingPreProcessor_OpenGL::PreprocessMesh(Rendering_General::Mesh &mesh)
	{
		InitVertexBuffers(mesh);
		CompileShaders(*mesh.getMaterial()->getShader());
	}

	void RenderingPreProcessor_OpenGL::InitVertexBuffers(Rendering_General::Mesh &mesh)
	{
		// Done once unless the object changes frequently
		// Generate vertex buffer and pass it to GPU
		//TODO: Create a mesh/renderable object class/struct and a system for passing the data to gpu
		glGenVertexArrays(1, &mesh.VAO);
		glGenBuffers(1, &mesh.VBO);
		glGenBuffers(1, &mesh.EBO);

		std::vector<float> vertices = mesh.getVertices();
		std::vector<unsigned int> indices = mesh.getIndices();

		// 1. bind Vertex Array Object
		glBindVertexArray(mesh.VAO);
		// 2. copy our vertices array in a buffer for OpenGL to use
		glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

		// 3. then set the vertex attributes pointers (for positions and colors)
		// TODO: Add handling various shaders inputs to be able to handle shaders with and without colors

		// Set vertices positions
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
		glEnableVertexAttribArray(0);

		// Set vertices colors
		// A color appears every 6 floats and its stride is the size of 3 floats from the beginning of an array
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		// 4. Bind Element Buffer Object (EBO)
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);
	}

	void RenderingPreProcessor_OpenGL::CompileShaders(Rendering_General::Shader &shader)
	{
		std::string vertexSrcStr = shader.getVertexShaderSource();
		std::string fragmentSrcStr = shader.getFragmentShaderSource();

		const char *vertexSrc = vertexSrcStr.c_str();
		const char *fragmentSrc = fragmentSrcStr.c_str();

		// Declare vertex shader and compile it
		//TODO: create a shader class/struct and a system for shader compilation
		unsigned int vertexShaderHandle = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShaderHandle, 1, &vertexSrc, NULL);
		glCompileShader(vertexShaderHandle);
		// Check if shader was compiled successfully
		CheckShaderCompilationStatus(vertexShaderHandle);

		// Compile fragment shader
		unsigned int fragmentShaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShaderHandle, 1, &fragmentSrc, NULL);
		glCompileShader(fragmentShaderHandle);
		CheckShaderCompilationStatus(fragmentShaderHandle);

		shader.shaderProgramHandle = glCreateProgram();
		glAttachShader(shader.shaderProgramHandle, vertexShaderHandle);
		glAttachShader(shader.shaderProgramHandle, fragmentShaderHandle);
		glLinkProgram(shader.shaderProgramHandle);

		// Delete shader objects as they are not needed after being linked into the program
		glDeleteShader(vertexShaderHandle);
		glDeleteShader(fragmentShaderHandle);
	}

	void RenderingPreProcessor_OpenGL::CheckShaderCompilationStatus(const unsigned int &shaderHandle)
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

	void RenderingPreProcessor_OpenGL::CheckShaderProgramLinkStatus(const unsigned int &shaderProgramHandle)
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
}
