#include "pch.hpp"
#include "SysRenderer.hpp"
#include "render/GLAD/RenderContextGLADImpl.hpp"
#include "render/Buffer.hpp"
#include "render/GLAD/BufferGLADImpl.hpp"
#include "resource/graphics/Shader.hpp"
#include "resource/graphics/Texture.hpp"

namespace ATMA
{

    SysRenderer::SysRenderer():
        SysBase(SystemType(System::Renderer), "Renderer"),
        m_ctx(ATMAContext::getContext())
    {
        m_renderer = m_ctx.getRenderer();
        m_req.set(AttrType(Attribute::Sprite));
        m_req.set(AttrType(Attribute::Shape));
        m_req.set(AttrType(Attribute::Renderable));
    }

    SysRenderer::~SysRenderer() {}

    void SysRenderer::update(const float &l_dt)
    {
        for(auto &id: m_objects)
        {
            auto sprite = m_ctx.getAttribute<AttrSprite>(id, AttrType(Attribute::Sprite));
            auto position = m_ctx.getAttribute<AttrShape>(id, AttrType(Attribute::Shape));
            auto render = m_ctx.getAttribute<AttrRenderable>(id, AttrType(Attribute::Renderable));
            render->m_program->exec();
            render->m_program->setUniformMat3f(
                "u_transform",
                translationMatrix(position->m_pos.x, position->m_pos.y)
                    * scalingMatrix(position->m_size.x, position->m_size.y)
                    * rotationMatrix(position->m_rot)
            );
            m_renderer->draw(sprite->m_texture, render->m_program);
        }
    }

    void SysRenderer::notify(const ObjectEventContext &l_e) {}
}
