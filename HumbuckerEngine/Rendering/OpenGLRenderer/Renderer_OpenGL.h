#pragma once
#include <memory>
#include "Window_OpenGL.h"
#include "EngineModules/IRenderer.h"

class IInputManager;

namespace Rendering_GL
{
    class Renderer_OpenGL : public IRenderer
    {
    public:
        int Init() override;
        void Tick() override;
        void Terminate() override;
        bool ShouldClose() override;
        std::string getInfo() override;
        [[nodiscard]] Window_OpenGL& getWindow() const
        {
            return *window;
        }

        IInputManager* CreateInputManager() const;

    private:
        std::unique_ptr<Window_OpenGL> window;
    };
}
