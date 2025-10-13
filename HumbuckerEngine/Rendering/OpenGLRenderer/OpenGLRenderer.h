#pragma once
#include <memory>

#include "GL_Window.h"
#include "../../EngineModules/IRenderer.h"

namespace Rendering_GL
{
    class OpenGLRenderer : public IRenderer
    {
    public:
        int Init() override;
        void Render() override;
        void Terminate() override;
        bool ShouldClose() override;
        std::string GetInfo() override;

    private:
        std::unique_ptr<GL_Window> window;
    };
}
