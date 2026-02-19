#pragma once
#include "GUI/WindowEvent.hpp"
#include "core/ATMAContext.hpp"
#include "state/BaseState.hpp"
#include <atomina.hpp>

class GameState: ATMA::BaseState
{
public:
    GameState(ATMA::ATMAContext *l_ctx): BaseState(l_ctx)
    {
        m_playerObj = l_ctx->m_attrMan->createObject();
        m_playerTextureId = l_ctx->m_resMan->registerResource("playerTexture", 0u, "res/Ball.png");
        m_playerAnimId = l_ctx->m_resMan->registerResource("playerAnim", 0u, "res/Ball.anim");
    }

    void activate(ATMA::ATMAContext *l_ctx) override
    {
        l_ctx->m_attrMan->addAttribute(l_ctx, m_playerObj, ATMA::AttributeType(ATMA::Attribute::Renderable));
        auto renderable = l_ctx->m_attrMan->getAttribute<ATMA::Renderable>(
            m_playerObj, ATMA::AttributeType(ATMA::Attribute::Renderable)
        );
        auto texture = l_ctx->m_resMan->loadResource<ATMA::GLTexture>(l_ctx, m_playerTextureId);
        renderable->m_texture = texture;
    }

    void deactivate(ATMA::ATMAContext *l_ctx) override {}

    unsigned int getId() const override
    {

        return ATMA::StateType(ATMA::State::COUNT) + 1;
    }

    void handleInput(ATMA::ATMAContext *l_ctx, const ATMA::WindowEvent &l_e) override {}
protected:
    unsigned int m_playerObj;
    unsigned int m_playerTextureId;
    unsigned int m_playerAnimId;
    std::shared_ptr<ATMA::Renderable> m_playerTransform;
};
