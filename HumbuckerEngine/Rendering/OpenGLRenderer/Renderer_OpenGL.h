#pragma once
#include <memory>
#include "Window_OpenGL.h"
#include "EngineModules/IRenderer.h"
#include "Utils/Settings.h"

class IInputManager;

namespace Rendering_GL
{
    static unsigned int CurrentWindowWidth = 100;
    static unsigned int CurrentWindowHeight = 100;

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
