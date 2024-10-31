#include "pch.hpp"
#include "GLSprite.hpp"
#ifdef ATMA_OPENGL
#    include "renderImpl/OpenGL/GLSpriteOpenGLImpl.hpp"
#    define __ATMAMAKEGLSPRITE() std::make_shared<GLSpriteOpenGLImpl>()
#else
#    include "renderImpl/Dummy/GLSpriteDummyImpl.hpp"
#    define __ATMAMAKEGLSPRITE() std::make_shared<GLSpriteDummyImpl>()
#endif

namespace ATMA
{

    std::shared_ptr<GLSprite> GLSprite::makeSprite(
        const Vec2<float> &l_selectSize,
        const Vec2<float> &l_size,
        std::shared_ptr<GLTexture> l_texture,
        std::shared_ptr<GLProgram> l_prog,
        const Vec2<float> &l_pos,
        const Vec2<float> &l_selectPos,
        const short &l_stackPos,
        const float &l_rot
    )
    {
        std::shared_ptr<GLSprite> t = __ATMAMAKEGLSPRITE();
        t->m_selectSize = l_selectSize;
        t->m_size = l_size;
        t->m_texture = l_texture;
        t->m_prog = l_prog;
        t->m_pos = l_pos;
        t->m_selectPos = l_selectPos;
        t->m_stackPos = l_stackPos;
        t->m_rot = l_rot;
        return t;
    }

}