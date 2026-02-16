#include "pch.hpp"
#include "GLRenderContext.hpp"
#ifdef ATMA_OPENGL
#    include "renderImpl/OpenGL/GLRenderContextOpenGLImpl.hpp"
#    define __ATMAMAKEGLRENDERCONTEXT() std::make_shared<GLRenderContextOpenGLImpl>()
#else
#    include "renderImpl/Dummy/GLRenderContextDummyImpl.hpp"
#    define __ATMAMAKEGLRENDERCONTEXT() std::make_shared<GLRenderContextDummyImpl>()
#endif

namespace ATMA
{

    GLRenderContext::GLRenderContext() {}

    GLRenderContext::~GLRenderContext() {}

    std::shared_ptr<GLRenderContext> GLRenderContext::getRenderContext()
    {
        static std::once_flag flag{};
        static std::shared_ptr<GLRenderContext> renderCtx;
        std::call_once(flag, [&]() { renderCtx = __ATMAMAKEGLRENDERCONTEXT(); });
        return renderCtx;
    }

    void GLRenderContext::setCamera(const Camera &l_camera)
    {
        m_camera = l_camera;
    }

    const Camera &GLRenderContext::getCamera() const
    {
        return m_camera;
    }

    void GLRenderContext::setShaderProgram(std::shared_ptr<GLProgram> l_prog)
    {
        m_prog = l_prog;
        m_prog->exec();
    }

    template<>
    void GLRenderContext::setUniform<Mat3<float>>(const std::string &l_name, const Mat3<float> &l_uni)
    {
        m_prog->setUniformMat3f(l_name, l_uni);
    }

    template<>
    void GLRenderContext::setUniform<float>(const std::string &l_name, const float &l_uni)
    {
        m_prog->setUniformf(l_name, l_uni);
    }

    std::shared_ptr<GLProgram> GLRenderContext::getShaderProgram()
    {
        return m_prog;
    }
}
