#include "math/MathFuncs.hpp"
#include "math/Vec3.hpp"
#include "pch.hpp"
#include "Renderer.hpp"
#include "core/ATMAContext.hpp"
#include "OAS/Attribute.hpp"
#include "OAS/AttributeManager.hpp"
#include "OAS/attributes/AttrRenderable.hpp"
#include "render/Renderable.hpp"
#include "time/StopWatch.hpp"

namespace ATMA
{

    Renderer::Renderer()
    {
        m_ctx = GLRenderContext::getRenderContext();
    }

    Renderer::~Renderer() {}

    void Renderer::toggleBlend(const bool &l_toggle)
    {
        m_ctx->toggleBlend(l_toggle);
    }

    void Renderer::toggleDepthTest(const bool &l_toggle)
    {
        m_ctx->toggleDepthTest(l_toggle);
    }

    void Renderer::setFrameBufferDimensions(const int &w, const int &h)
    {
        m_ctx->setViewPort({0, 0}, {w, h});
    }

    void Renderer::setWindow(std::shared_ptr<AppWindow> l_win)
    {
        static std::once_flag once;
        glfwMakeContextCurrent(l_win->m_windowHandle);
        std::call_once(once, [&]() { m_ctx->init(); });
    }

    void Renderer::startScene(const Camera &l_camera)
    {
        m_ctx->setCamera(l_camera);
    }

    void Renderer::addElement(const unsigned int &l_renderable)
    {
        ATMA_ENGINE_TRACE("Adding element to renderer");
        const short l_z = 0;
        if(auto itr = m_elementContainer.find(l_z); itr != m_elementContainer.end())
        {
            itr->second.emplace_back(l_renderable);
        }
        else
        {
            std::vector<unsigned int> l_list{};
            l_list.emplace_back(l_renderable);
            m_elementContainer[l_z] = l_list;
        }
        ATMA_ENGINE_TRACE("Finished adding element to renderer");
    }

    void Renderer::removeElement(const unsigned int &l_renderable)
    {
        for(auto itr = m_elementContainer.begin(); itr != m_elementContainer.end(); itr++)
        {
            for(auto inner = itr->second.begin(); inner != itr->second.end(); inner++)
            {
                if(*inner == l_renderable)
                {
                    if(itr->second.size() == 1)
                    {
                        m_elementContainer.erase(itr);
                        return;
                    }
                    else
                    {
                        itr->second.erase(inner);
                        return;
                    }
                }
            }
        }
    }

    void Renderer::clearElements()
    {
        m_elementContainer.clear();
    }

    void Renderer::changeElementPriority(const unsigned int &l_renderable, const short &l_z)
    {
        removeElement(l_renderable);
        if(auto itr = m_elementContainer.find(l_z); itr == m_elementContainer.end())
        {
            std::vector<unsigned int> l_list{};
            l_list.emplace_back(l_renderable);
            m_elementContainer[l_z] = l_list;
        }
        else
        {

            m_elementContainer[l_z].emplace_back(l_renderable);
        }
    }

    void Renderer::finishScene(ATMAContext *l_ctx)
    {
        m_ctx->clear();
        const Camera camera = m_ctx->getCamera();
        for(auto itr = m_elementContainer.begin(); itr != m_elementContainer.end(); itr++)
        {
            for(auto inner = itr->second.begin(); inner != itr->second.end(); inner++)
            {
                std::shared_ptr<Renderable> r =
                    l_ctx->m_attrMan->getAttribute<AttrRenderable>(*inner, AttributeType(Attribute::Renderable))
                        ->m_self;
                std::shared_ptr<GLTexture> texture = r->m_texture;
#ifdef _DEBUG
                if(texture == nullptr)
                {
                    ATMA_ENGINE_WARN("render item has no texture");
                    continue;
                }
#endif
                texture->bind();
                for(auto tIter = r->begin(); tIter != r->end(); tIter++)
                {
                    Transform &tt = tIter->second;
                    // set uniforms
                    m_ctx->setUniform("u_camera", camera.getProjectionMatrix());
                    m_ctx->setUniform("u_translate", translationMatrix<float>(tt.m_pos.x, tt.m_pos.y));
                    m_ctx->setUniform("u_scale", scalingMatrix<float>(tt.m_size.x, tt.m_size.y));
                    m_ctx->setUniform("u_rot", rotationMatrix<float>(tt.m_rot));
                    m_ctx->setUniform("u_textureRegion", scalingMatrix<float>(tt.m_selectSize.x, tt.m_selectSize.y));
                    m_ctx->setUniform(
                        "u_texturePos",
                        translationMatrix<float>(
                            tt.m_selectPos.x + tt.m_selectAdv.x, tt.m_selectPos.y + tt.m_selectAdv.y
                        )
                    );
                    m_ctx->setUniform("u_textureCamera", texture->m_texture.proj());
                    m_ctx->getShaderProgram()->exec();
                    m_ctx->drawElements();
                }
            }
        }
    }

}
