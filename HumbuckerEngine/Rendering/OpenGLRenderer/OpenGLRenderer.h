#pragma once
#include "../../EngineModules/IRenderer.h"

namespace OpenGLRenderer
{
    class OpenGLRenderer : public IRenderer
    {
    public:
        void Render() override;
    };
}
