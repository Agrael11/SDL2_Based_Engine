#include "Renderer.h"
#include "../../Helper/Logger.h"

using namespace Engine::Helper;
using namespace Engine::Rendering;

#include "glad/glad.h"

bool Renderer::Init(SDL_Window &window, Uint32 flags    )
{
    this->mWindowReference = &window;

    Logger::log(Logger::Level::Info, "Creating context.");
    this->mContext = SDL_GL_CreateContext(&window);
    if (this->mContext == NULL)
    {
        Logger::log(Logger::Level::Error, "Failed to create context. SDL_Error: {}", SDL_GetError());
        return false;
    }

    gladLoadGLLoader(SDL_GL_GetProcAddress);
    Logger::log(Logger::Level::Info, "OpenGL Loaded.");
    Logger::log(Logger::Level::Info, "Vendor:     {}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
    Logger::log(Logger::Level::Info, "Renderer:   {}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
    Logger::log(Logger::Level::Info, "Version:    {}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    int w,h;
    SDL_GetWindowSize(&window, &w, &h);
    SetViewport(0, 0, w, h);
    glClearColor(0.5, 0.5, 0.5, 0);

    return true;
}