#include "pch.hpp"
#include "GLText.hpp"
#ifdef ATMA_OPENGL
#    include "renderImpl/OpenGL/GLTextOpenGLImpl.hpp"
#    define __ATMAMAKEGLTEXT() std::make_shared<GLTextOpenGLImpl>()
#else
#    include "renderImpl/Dummy/GLTextDummyImpl.hpp"
#    define __ATMAMAKEGLTEXT() std::make_shared<GLTextDummyImpl>()
#endif

namespace ATMA
{

    std::shared_ptr<GLText> GLText::makeText(
        const std::string &l_text,
        const Vec2<float> &l_size,
        std::shared_ptr<GLTexture> l_texture,
        std::shared_ptr<GLProgram> l_prog,
        const Vec2<float> &l_pos,
        const short &l_stackPos,
        const float &l_rot
    )
    {
        std::shared_ptr<GLText> t = __ATMAMAKEGLTEXT();
        t->m_text = l_text;
        t->m_size = l_size;
        t->m_texture = l_texture;
        t->m_prog = l_prog;
        t->m_pos = l_pos;
        t->m_stackPos = l_stackPos;
        t->m_rot = l_rot;
        return t;
    }

}