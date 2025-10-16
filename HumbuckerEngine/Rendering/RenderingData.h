#pragma once
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

#include "glad/glad.h"
#include "Utils/HumbuckerUtils.h"

namespace Rendering_General
{
	struct Shader;
	struct Material;

	struct Mesh
	{
	private:
		std::vector<float> vertices;
		std::vector<unsigned int> indices;
		std::shared_ptr<Material> material;

	public:
		unsigned int VBO;
		unsigned int VAO;
		unsigned int EBO;

		Mesh(std::vector<float> &&vertices, std::vector<unsigned int> &&indices, const std::shared_ptr<Material> &material) : vertices(vertices), indices(indices),
			material(material) {}

		[[nodiscard]] const std::vector<float> &getVertices() const { return vertices; }

		[[nodiscard]] const std::vector<unsigned int> &getIndices() const { return indices; }

		[[nodiscard]] const std::shared_ptr<Material> &getMaterial() const { return material; }
	};

	struct Material
	{
	private:
		std::shared_ptr<Shader> shader;

	public:
		Material(const std::shared_ptr<Shader> &shader) : shader(shader) {}

		[[nodiscard]] const std::shared_ptr<Shader> &getShader() const { return shader; }
	};

	struct Shader
	{
	private:
		std::string vertexShaderSource;

		std::string fragmentShaderSource;

	public:
		unsigned int shaderProgramHandle;

		Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath)
		{
			vertexShaderSource = HumbuckerUtils::GetTextFromFile(vertexShaderPath);
			fragmentShaderSource = HumbuckerUtils::GetTextFromFile(fragmentShaderPath);

			std::cout << vertexShaderSource << std::endl;
			std::cout << fragmentShaderSource << std::endl;
		}

		Shader() {}

		void Use() const
		{
			glUseProgram(shaderProgramHandle);
		}

		[[nodiscard]] std::string getVertexShaderSource() const { return vertexShaderSource; }

		[[nodiscard]] std::string getFragmentShaderSource() const { return fragmentShaderSource; }
		void setVertexShaderSource(const std::string &vertex_shader_source) { vertexShaderSource = vertex_shader_source; }
		void setFragmentShaderSource(const std::string &fragment_shader_source) { fragmentShaderSource = fragment_shader_source; }
	};
}
