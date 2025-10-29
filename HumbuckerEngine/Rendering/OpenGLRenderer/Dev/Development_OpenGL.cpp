#include "Development_OpenGL.h"
#include <complex>
#include <iostream>
#include <string>
#include "Rendering/RenderingData.h"
#include "../RenderingPreProcessor_OpenGL.h"
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Utils/Settings.h"
#include "Utils/ShapesLibrary.h"

namespace Rendering_GL
{
	const std::string vertexShaderPath = "HumbuckerEngine/Shaders/DefaultShader.vert";
	const std::string fragmentShaderPath = "HumbuckerEngine/Shaders/DefaultShader.frag";

	Rendering_General::Shader shader = Rendering_General::Shader(vertexShaderPath, fragmentShaderPath);
	Rendering_General::Material material = Rendering_General::Material(std::make_shared<Rendering_General::Shader>(shader));

	Rendering_General::Mesh squareMesh = Rendering_General::Mesh(std::move(Square::Vertices), std::move(Square::Indices), std::make_shared<Rendering_General::Material>(material));
	Rendering_General::Mesh cubeMesh = Rendering_General::Mesh(std::move(Cube::Vertices), std::move(Cube::Indices), std::make_shared<Rendering_General::Material>(material));
	// IMPORTANT: shader and material's ownership is transferred, so don't use them directly, but get to them through the mesh object instead

	void Development_OpenGL::PrepareBuffers()
	{
		RenderingPreProcessor_OpenGL::PreprocessMesh(squareMesh);
		RenderingPreProcessor_OpenGL::PreprocessMesh(cubeMesh);
	}

	void Development_OpenGL::DrawMesh(const Rendering_General::Mesh &mesh, const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &projection)
	{
		Rendering_General::Shader *shader = mesh.getMaterial()->getShader().get();
		// Use our shader program when we want to render an object
		shader->Use();

		shader->setMat4("model", model);
		shader->setMat4("view", view);
		shader->setMat4("projection", projection);

		float colorMultiplier = 1.0f;
		shader->setFloat("colorMultiplier", colorMultiplier);
		// Now draw the object
		glBindVertexArray(mesh.VAO);
		glDrawElements(GL_TRIANGLES, mesh.getIndices().size(), GL_UNSIGNED_INT, 0);
	}


	void Development_OpenGL::Tick()
	{
		float timeValue = glfwGetTime();

		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		glm::mat4 projection = glm::perspective(45.0f, (float) DEFAULT_WINDOW_WIDTH / DEFAULT_WINDOW_HEIGHT, 0.1f, 100.0f);

		// model = glm::translate(model, glm::vec3(0.5f, -0.5f, 0.0f));
		// model = glm::rotate(model, timeValue, glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, timeValue, glm::vec3(0.0f, 0.0f, 1.0f));
		// model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));

		DrawMesh(cubeMesh, model, view, projection);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.5f, -0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.6f, 1.0f, 0.5f));

		DrawMesh(squareMesh, model, view, projection);
	}
}
