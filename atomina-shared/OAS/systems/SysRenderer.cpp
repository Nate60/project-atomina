#include "pch.hpp"
#include "SysRenderer.hpp"
#include "render/GLAD/RenderContextGLADImpl.hpp"
#include "render/Buffer.hpp"
#include "render/GLAD/BufferGLADImpl.hpp"
#include "resource/graphics/render/ShaderGLADImpl.hpp"
#include "resource/graphics/render/TextureGLADImpl.hpp"
#include "render/GLAD/ShaderProgramGLADImpl.hpp"

namespace ATMA
{

    SysRenderer::SysRenderer(): SysBase(SystemType(System::Renderer), "Renderer")
    {
        m_req.set(AttrType(Attribute::Sprite));
        m_req.set(AttrType(Attribute::Position));
        m_req.set(AttrType(Attribute::Renderable));
    }

    SysRenderer::~SysRenderer() {}

    void SysRenderer::update(const float &l_dt)
    {

        for(auto &id: m_objects)
        {
        }
    }

    void SysRenderer::notify(const ObjectEventContext &l_e) {}
}
