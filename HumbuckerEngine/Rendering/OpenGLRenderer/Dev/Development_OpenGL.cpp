#include "Development_OpenGL.h"

#include <iostream>
#include <ostream>
#include <string>

#include "glad/glad.h"
#include "Rendering/RenderingData.h"
#include "Rendering/RenderingPreProcessor.h"

namespace Rendering_GL
{
	std::vector<float> vertices =
	{
		0.5f, 0.5f, 0.0f, // top right
		0.5f, -0.5f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, // bottom left
		-0.5f, 0.5f, 0.0f // top left
	};
	std::vector<unsigned int> indices =
	{
		0, 1, 3, // First triangle
		1, 2, 3 // Second triangle
	};

	// Vertices and shader handles
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;

	unsigned int vertexShaderHandle;
	unsigned int fragmentShaderHandle;
	unsigned int shaderProgramHandle; // Vertex and fragment shaders combined

	// const char *vertexShaderSource = "#version 330 core\nlayout (location = 0) in vec3 aPos;\nvoid main()\n{\ngl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n}\0";
	std::string vertexShaderSource = "#version 330 core\nlayout (location = 0) in vec3 aPos;\nvoid main()\n{\ngl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n}\0";

	// const char *fragmentShaderSource = "#version 330 core\nout vec4 FragColor;\nvoid main()\n{\nFragColor = vec4(0.6f, 0.9f, 0.4f, 1.0f);\n}\0";
	std::string fragmentShaderSource = "#version 330 core\nout vec4 FragColor;\nvoid main()\n{\nFragColor = vec4(0.6f, 0.9f, 0.4f, 1.0f);\n}\0";

	Rendering_General::Shader shader = Rendering_General::Shader(vertexShaderSource, fragmentShaderSource);
	Rendering_General::Material material = Rendering_General::Material(std::make_shared<Rendering_General::Shader>(shader));
	Rendering_General::Mesh mesh = Rendering_General::Mesh(std::move(vertices), std::move(indices), std::make_shared<Rendering_General::Material>(material));
	// IMPORTANT: shader and material's ownership is transferred, so don't use them directly, but get to them through the mesh object instead

	void Development_OpenGL::PrepareBuffers()
	{
		Rendering_General::RenderingPreProcessor::PreprocessMesh(mesh);
	}

	void Development_OpenGL::RenderTriangle()
	{
		// Use our shader program when we want to render an object
		glUseProgram(mesh.getMaterial()->getShader()->shaderProgramHandle);

		// Now draw the object
		glBindVertexArray(mesh.VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}
