#include "pch.hpp"
#include "GLRenderable.hpp"
#ifdef ATMA_OPENGL
#    include "renderImpl/OpenGL/GLRenderableOpenGLImpl.hpp"
#    define __ATMAMAKEGLRENDERABLE()                                                       \
        std::make_shared<GLRenderableOpenGLImpl>()
#else
#    include "renderImpl/Dummy/GLRenderableDummyImpl.hpp"
#    define __ATMAMAKEGLRENDERABLE()                                                       \
        std::make_shared<GLRenderableDummyImpl>()
#endif

namespace ATMA
{
        std::shared_ptr<GLRenderable> GLRenderable::makeRenderable(
            const Vec2<float> &l_size,
            std::shared_ptr<GLTexture> l_texture,
            std::shared_ptr<GLProgram> l_prog,
            const Vec2<float> &l_pos,
            const short &l_stackPos,
            const float &l_rot
        )
        {
            std::shared_ptr<GLRenderable> r = __ATMAMAKEGLRENDERABLE();
            r->m_size = l_size;
            r->m_texture = l_texture;
            r->m_prog = l_prog;
            r->m_pos = l_pos;
            r->m_stackPos = l_stackPos;
            r->m_rot = l_rot;
            return r;
        }

        bool GLRenderableCompare::operator()(const std::shared_ptr<GLRenderable> &a, const std::shared_ptr<GLRenderable> &b)
        {
            return a->m_stackPos > b->m_stackPos;
        }
}