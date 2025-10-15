#include "RenderingPreProcessor.h"

#include <iostream>

#include "glad/glad.h"

namespace Rendering_General
{
	void RenderingPreProcessor::PreprocessMesh(Mesh &mesh)
	{
		InitVertexBuffers(mesh);
		CompileShaders(*mesh.getMaterial()->getShader());
	}

	void RenderingPreProcessor::InitVertexBuffers(Mesh &mesh)
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

		// 3. then set the vertex attributes pointers
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
		glEnableVertexAttribArray(0);

		// 4. Bind Element Buffer Object (EBO)
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);
	}

	void RenderingPreProcessor::CompileShaders(Shader &shader)
	{
		std::string vertexSrcStr = shader.getVertexShaderSource();
		std::string fragmentSrcStr = shader.getFragmentShaderSource();

		const char* vertexSrc = vertexSrcStr.c_str();
		const char* fragmentSrc = fragmentSrcStr.c_str();

		// Declare vertex shader and compile it
		//TODO: create a shader class/struct and a system for shader compilation
		shader.vertexShaderHandle = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(shader.vertexShaderHandle, 1, &vertexSrc, NULL);
		glCompileShader(shader.vertexShaderHandle);
		// Check if shader was compiled successfully
		CheckShaderCompilationStatus(shader.vertexShaderHandle);

		// Compile fragment shader
		shader.fragmentShaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(shader.fragmentShaderHandle, 1, &fragmentSrc, NULL);
		glCompileShader(shader.fragmentShaderHandle);
		CheckShaderCompilationStatus(shader.fragmentShaderHandle);

		shader.shaderProgramHandle = glCreateProgram();
		glAttachShader(shader.shaderProgramHandle, shader.vertexShaderHandle);
		glAttachShader(shader.shaderProgramHandle, shader.fragmentShaderHandle);
		glLinkProgram(shader.shaderProgramHandle);

		// Delete shader objects as they are not needed after being linked into the program
		glDeleteShader(shader.vertexShaderHandle);
		glDeleteShader(shader.fragmentShaderHandle);
	}

	void RenderingPreProcessor::CheckShaderCompilationStatus(const unsigned int &shaderHandle)
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

	void RenderingPreProcessor::CheckShaderProgramLinkStatus(const unsigned int &shaderProgramHandle)
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
