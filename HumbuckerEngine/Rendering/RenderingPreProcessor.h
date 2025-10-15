#pragma once
#include "RenderingData.h"

namespace Rendering_General
{
	class RenderingPreProcessor
	{
	public:
		static void PreprocessMesh(Mesh &mesh);

		static void InitVertexBuffers(Mesh &mesh);

		static void CompileShaders(Shader &shader);

	private:
		static void CheckShaderCompilationStatus(const unsigned int &shaderHandle);

		static void CheckShaderProgramLinkStatus(const unsigned int &shaderProgramHandle);
	};
}
