#pragma once
#include "../RenderingData.h"

namespace Rendering_GL
{
	class RenderingPreProcessor
	{
	public:
		static void PreprocessMesh(Rendering_General::Mesh &mesh);

		static void InitVertexBuffers(Rendering_General::Mesh &mesh);

		static void CompileShaders(Rendering_General::Shader &shader);

	private:
		static void CheckShaderCompilationStatus(const unsigned int &shaderHandle);

		static void CheckShaderProgramLinkStatus(const unsigned int &shaderProgramHandle);
	};
}
