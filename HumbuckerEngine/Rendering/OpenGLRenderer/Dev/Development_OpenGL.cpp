#include "Development_OpenGL.h"

#include <complex>
#include <iostream>
#include <string>

#include "glad/glad.h"
#include "Rendering/RenderingData.h"
#include "../RenderingPreProcessor.h"
#include "GLFW/glfw3.h"

namespace Rendering_GL
{
	std::vector<float> vertices =
	{
		// positions	  // colors
		0.5f, 0.5f, 0.0f, 1.0, 0.0, 0.0, // top right
		0.5f, -0.5f, 0.0f, 0.0, 1.0, 0.0, // bottom right
		-0.5f, -0.5f, 0.0f, 0.0, 0.0, 1.0, // bottom left
		-0.5f, 0.5f, 0.0f, 1.0, 1.0, 1.0 // top left
	};
	std::vector<unsigned int> indices =
	{
		0, 1, 3, // First triangle
		1, 2, 3 // Second triangle
	};

	std::string vertexShaderSource =
			"#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"layout (location = 1) in vec3 aColor;\n"
			"out vec3 vecColor;\n"
			"void main()\n"
			"{\n"
			"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
			"vecColor = aColor;\n"
			"}\0";

	std::string fragmentShaderSource =
			"#version 330 core\n"
			"out vec4 FragColor;\n"
			"in vec3 vecColor;\n"
			"uniform float colorMultiplier;"
			"void main()\n"
			"{\n"
			"FragColor = colorMultiplier * vec4(vecColor, 1.0);\n"
			// "FragColor = vec4(vecColor, 1.0);\n"
			"}\0";

	const std::string vertexShaderPath = "../HumbuckerEngine/Shaders/DefaultShader.vert";
	const std::string fragmentShaderPath = "../HumbuckerEngine/Shaders/DefaultShader.frag";

	Rendering_General::Shader shader = Rendering_General::Shader(vertexShaderPath, fragmentShaderPath);
	Rendering_General::Material material = Rendering_General::Material(std::make_shared<Rendering_General::Shader>(shader));
	Rendering_General::Mesh mesh = Rendering_General::Mesh(std::move(vertices), std::move(indices), std::make_shared<Rendering_General::Material>(material));
	// IMPORTANT: shader and material's ownership is transferred, so don't use them directly, but get to them through the mesh object instead

	void Development_OpenGL::PrepareBuffers()
	{
		RenderingPreProcessor::PreprocessMesh(mesh);
	}

	void Development_OpenGL::Tick()
	{
		Rendering_General::Shader *shader = mesh.getMaterial()->getShader().get();
		// Use our shader program when we want to render an object
		shader->Use();

		float timeValue = glfwGetTime();
		float colorMultiplier = std::sin(timeValue);
		shader->setFloat("colorMultiplier", colorMultiplier);
		// Now draw the object
		glBindVertexArray(mesh.VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}
