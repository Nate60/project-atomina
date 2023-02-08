#ifdef ATMA_USE_GLFW
#    include "pch.hpp"
#    include "WindowGLFWImpl.hpp"

namespace ATMA
{

    using namespace std::placeholders;

    WindowGLFWImpl::WindowGLFWImpl(const std::string &l_name): Window(l_name)
    {
        m_window = glfwCreateWindow(640, 480, l_name.c_str(), NULL, NULL);
        m_callback_container.m_parent = this;
    }

    WindowGLFWImpl::WindowGLFWImpl(const Props &l_props, const std::string &l_name = "ATMA_API"):
        Window(l_props, l_name)
    {
        m_window = glfwCreateWindow(640, 480, l_name.c_str(), NULL, NULL);
        m_callback_container.m_parent = this;
    }

    void WindowGLFWImpl::setInputCallback(
        std::function<void(Window *, int, int, int, int)> l_callback
    )
    {
        m_callback_container.m_self = l_callback;
        glfwSetWindowUserPointer(m_window, &m_callback_container);
        glfwSetKeyCallback(
            m_window,
            [](GLFWwindow *window, int key, int scancode, int action, int mods)
            {
                CallbackContainer *inner_data =
                    (CallbackContainer *)glfwGetWindowUserPointer(window);
                (inner_data->m_self)(inner_data->m_parent, key, scancode, action, mods);
            }
        );
    }

    void WindowGLFWImpl::swapBuffers()
    {
        glfwSwapBuffers(m_window);
    }

    void WindowGLFWImpl::pollEvents()
    {
        glfwPollEvents();
    }

    void WindowGLFWImpl::focus()
    {
        glfwMakeContextCurrent(m_window);
    }

    void WindowGLFWImpl::setWindowShouldClose(bool l_bool)
    {
        glfwSetWindowShouldClose(m_window, GLFW_TRUE);
    }

    bool WindowGLFWImpl::getWindowShouldClose() const
    {
        return glfwWindowShouldClose(m_window);
    }

}
#endif