#include "pch.hpp"
#include "AppWindow.hpp"
#include "core/ATMAContext.hpp"
#include "render/Renderer.hpp"
#include "state/StateManager.hpp"

namespace ATMA
{
    AppWindow::AppWindow(ATMAContext *ctx, const Vec2<unsigned int> &l_size, const std::string &l_name)
    {
        m_size = l_size;
        m_name = l_name;
        m_closed = false;
        this->ctx = ctx;
        m_windowHandle = glfwCreateWindow(m_size.x, m_size.y, m_name.c_str(), NULL, NULL);
        glfwSetWindowUserPointer(m_windowHandle, this);
        glfwSetFramebufferSizeCallback(
            m_windowHandle,
            [](GLFWwindow *win, int w, int h)
            {
                AppWindow *appwindow = (AppWindow *)(glfwGetWindowUserPointer(win));
                appwindow->setSize(Vec2<unsigned int>{(unsigned int)w, (unsigned int)h});
                appwindow->ctx->m_renderer->setFrameBufferDimensions(w, h);
            }
        );
        glfwSetKeyCallback(
            m_windowHandle,
            [](GLFWwindow *win, int key, int scancode, int action, int mods)
            {
                AppWindow *appwindow = (AppWindow *)(glfwGetWindowUserPointer(win));
                Props p{};
                p["keycode"] = key;
                p["repeat"] = (action == GLFW_REPEAT);
                WindowEventEnum t;
                if(action == GLFW_PRESS)
                {
                    t = WindowEventEnum::KeyDowned;
                }
                else
                {
                    t = WindowEventEnum::KeyUpped;
                }
                appwindow->ctx->m_stateMan->dispatchWindowEvent(appwindow->ctx, WindowEvent{appwindow, t, p});
            }
        );
    }

    AppWindow::~AppWindow()
    {

        ATMA_ENGINE_INFO("Destroying App Window {0}", m_name);
    }

    const Vec2<unsigned int> &AppWindow::getSize() const
    {
        return m_size;
    }

    void AppWindow::setSize(const Vec2<unsigned int> &l_size)
    {
        glfwSetWindowSize(m_windowHandle, l_size.x, l_size.y);
        m_size = l_size;
    }

    const std::string &AppWindow::getName() const
    {
        return m_name;
    }

    void AppWindow::notifyClose()
    {
        m_closed = true;
        glfwSetWindowShouldClose(m_windowHandle, GLFW_TRUE);
    }

    void AppWindow::show()
    {
        glfwShowWindow(m_windowHandle);
    }

    void AppWindow::poll()
    {
        glfwPollEvents();
    }

    void AppWindow::swapBuffers()
    {
        glfwSwapBuffers(m_windowHandle);
    }

    const bool AppWindow::shouldClose() const
    {
        return glfwWindowShouldClose(m_windowHandle) > 0;
    }

}
