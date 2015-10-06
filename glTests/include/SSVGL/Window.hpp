// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVGL_WINDOW
#define SSVGL_WINDOW

#include "SSVGL/Common.hpp"

namespace ssvgl
{
    class Window
    {
    private:
        GLFWwindow* glfwWindow{nullptr};

        std::size_t width{640}, height{480};
        std::string title;
        bool fullscreen{false};

    public:
        inline Window(std::size_t mWidth, std::size_t mHeight,
            std::string mTitle, bool mFullscreen)
            : width{mWidth}, height{mHeight}, title{std::move(mTitle)},
              fullscreen{mFullscreen}
        {
            if(!Internal::isInitialized()) Internal::initialize();
            SSVU_ASSERT(Internal::isInitialized());

            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

            glfwWindow = glfwCreateWindow(width, height, title.c_str(),
                fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);
            if(!glfwWindow)
            {
                glfwTerminate();
                std::terminate();
            }

            glfwMakeContextCurrent(glfwWindow);
            SSVU_ASSERT(glfwGetCurrentContext() == glfwWindow);

            glewInit();
        }

        inline ~Window() { glfwDestroyWindow(glfwWindow); }

        inline GLFWwindow* getGLFWWindow() noexcept { return glfwWindow; }

        inline void display() noexcept { glfwSwapBuffers(glfwWindow); }
        inline void close() noexcept
        {
            glfwSetWindowShouldClose(glfwWindow, GL_TRUE);
        }

        inline bool shouldClose() const noexcept
        {
            return glfwWindowShouldClose(glfwWindow);
        }
    };
}

#endif
