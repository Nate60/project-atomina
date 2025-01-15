#include "pch.hpp"
#include "GLRenderContextOpenGLImpl.hpp"

namespace ATMA
{

    // default constructor
    GLRenderContextOpenGLImpl::GLRenderContextOpenGLImpl() {}

    // default deconstructor
    GLRenderContextOpenGLImpl::~GLRenderContextOpenGLImpl() {}

    void GLRenderContextOpenGLImpl::init()
    {
        GLenum err = glewInit();
        if(GLEW_OK != err)
        {
            /* Problem: glewInit failed, something is seriously wrong. */
            std::string errString = std::string(reinterpret_cast<const char *>(glewGetErrorString(err)));
            ATMA_ENGINE_ERROR("Error: {}", errString);
            return;
        }

        ATMA_ENGINE_INFO("GLEW INIT OK!");
    }

    void GLRenderContextOpenGLImpl::setViewPort(const Vec2<int> &l_pos, const Vec2<int> &l_size)
    {
        glViewport(l_pos.x, l_pos.y, l_size.x, l_size.y);
    }

    void GLRenderContextOpenGLImpl::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void GLRenderContextOpenGLImpl::toggleBlend(const bool &l_toggle)
    {
        if(l_toggle)
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }
        else
        {
            glDisable(GL_BLEND);
        }
    }

}