#include "pch.hpp"
#include "GLRenderer.hpp"

namespace ATMA
{

    void GLRenderer::setFrameBufferDimensions(const int &w, const int &h)
    {
        glViewport(0, 0, w, h);
    }

    void GLRenderer::setWindow(std::shared_ptr<AppWindow> l_win)
    {
        static std::once_flag once;
        glfwMakeContextCurrent(l_win->m_windowHandle);
        std::call_once(
            once,
            []()
            {
                GLenum err = glewInit();
                if(GLEW_OK != err)
                {
                    /* Problem: glewInit failed, something is seriously wrong. */
                    std::string errString =
                        std::string(reinterpret_cast<const char *>(glewGetErrorString(err)));
                    ATMA_ENGINE_ERROR("Error: {}", errString);
                    return;
                }

                ATMA_ENGINE_INFO("GLEW INIT OK!");
            }
        );
    }

    void GLRenderer::startScene(const GLCamera &l_camera)
    {
        m_camera = l_camera;
    }

    void GLRenderer::addElement(std::shared_ptr<GLRenderable> l_renderable)
    {
        m_elementStack.push(l_renderable);
    }

    void GLRenderer::finishScene()
    {
        Props p{};
        p["u_camera"] = m_camera.getProjectionMatrix();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        while(!m_elementStack.empty())
        {
            auto &element = m_elementStack.top();
            element->draw(p);
            m_elementStack.pop();
        }
    }

}