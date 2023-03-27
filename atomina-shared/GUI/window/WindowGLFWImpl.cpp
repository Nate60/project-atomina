#ifdef ATMA_USE_GLFW
#    include "pch.hpp"
#    include "WindowGLFWImpl.hpp"

namespace ATMA
{

    using namespace std::placeholders;

    WindowGLFWImpl::WindowGLFWImpl(const std::string &l_name): Window(l_name)
    {
        m_window = glfwCreateWindow(640, 480, l_name.c_str(), NULL, NULL);
        if(m_window == NULL)
        {
            // ATMA_ENGINE_ERROR("GFLW failed to create a window");
            throw InitializationException("GLFW was unable to create a window");
        }
        // ATMA_ENGINE_INFO("Created window with name {0}", l_name);
        m_callback_container.m_parent = this;
    }

    WindowGLFWImpl::WindowGLFWImpl(const Props &l_props, const std::string &l_name = "ATMA_API"):
        Window(l_props, l_name)
    {
        m_window = glfwCreateWindow(640, 480, l_name.c_str(), NULL, NULL);
        m_callback_container.m_parent = this;
    }

    WindowGLFWImpl::~WindowGLFWImpl()
    {
        glfwDestroyWindow(m_window);
    }

    void WindowGLFWImpl::setInputCallback(
        std::function<void(Window *, int, int, int, int)> l_callback
    )
    {
        m_callback_container.m_input = l_callback;
        glfwSetWindowUserPointer(m_window, &m_callback_container);
        glfwSetKeyCallback(
            m_window,
            [](GLFWwindow *window, int key, int scancode, int action, int mods)
            {
                CallbackContainer *inner_data =
                    (CallbackContainer *)glfwGetWindowUserPointer(window);
                (inner_data->m_input)(inner_data->m_parent, key, scancode, action, mods);
            }
        );
    }

    void WindowGLFWImpl::setFrameResizeCallback(std::function<void(Window *, int, int)> l_callback)
    {
        m_callback_container.m_resize = l_callback;
        glfwSetWindowUserPointer(m_window, &m_callback_container);
        glfwSetFramebufferSizeCallback(
            m_window,
            [](GLFWwindow *window, int width, int height)
            {
                CallbackContainer *inner_data =
                    (CallbackContainer *)glfwGetWindowUserPointer(window);
                (inner_data->m_resize)(inner_data->m_parent, width, height);
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

    void WindowGLFWImpl::focusContext(const std::unique_ptr<RenderContext> &l_context)
    {
        glfwMakeContextCurrent(m_window);
        auto result = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        if(!result)
        {
            ATMA_ENGINE_ERROR("GLAD failed to initialize: {0}", result);
            throw InitializationException("GLAD was unable to initialize in this context");
        }
        ATMA_ENGINE_INFO("GLAD Initialized OP with Version {0}", glGetString(GL_VERSION));
        ATMA_ENGINE_INFO("focused new window");
        glDebugMessageCallback(&WindowGLFWImpl::glErrorCallback, m_window);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void WindowGLFWImpl::setWindowShouldClose(bool l_bool)
    {
        glfwSetWindowShouldClose(m_window, GLFW_TRUE);
    }

    bool WindowGLFWImpl::getWindowShouldClose() const
    {
        return glfwWindowShouldClose(m_window);
    }

    Vec2<int> WindowGLFWImpl::getFrameBufferSize() const
    {
        int w, h;
        glfwGetFramebufferSize(m_window, &w, &h);
        return Vec2<int>{w, h};
    }

    void WindowGLFWImpl::glErrorCallback(
        GLenum source,
        GLenum type,
        GLuint id,
        GLenum severity,
        GLsizei length,
        const GLchar *message,
        const void *param
    )
    {
        ATMA_ENGINE_INFO("--[OPENGL]: OpenGL encountered an issue");

        // switch(severity)
        //{
        // case GL_DEBUG_SEVERITY_NOTIFICATION:
        //     ATMA_ENGINE_INFO("--[OPENGL]: {0}", message);
        //     break;
        // case GL_DEBUG_SEVERITY_LOW:
        //     ATMA_ENGINE_WARN("--[OPENGL]: {0}", message);
        //     break;
        // case GL_DEBUG_SEVERITY_MEDIUM:
        //     ATMA_ENGINE_WARN("--[OPENGL]: {0}", message);
        //     break;
        // case GL_DEBUG_SEVERITY_HIGH:
        //     ATMA_ENGINE_ERROR("--[OPENGL]: {0}", message);
        // }
    }

}
#endif