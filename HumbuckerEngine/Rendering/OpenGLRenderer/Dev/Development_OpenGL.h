#pragma once
#include "glm/fwd.hpp"

namespace Rendering_General
{
	struct Mesh;
}

namespace Rendering_GL
{
	// Class for development purposes to prototype and experiment with rendering api features
	class Development_OpenGL
	{
	public:
		static void PrepareBuffers();

		static void DrawMesh(const Rendering_General::Mesh &mesh, const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &projection);

		static void Tick();

	private:
	};
}
