#pragma once
#include <atomina.hpp>
#include <gtest/gtest.h>

[[nodiscard]] static inline ATMA::ATMAContext *makeContext()
{
    ATMA::ATMAContext *ctx = new ATMA::ATMAContext{};
    ctx->m_attrMan = new ATMA::AttributeManager{};
    ctx->m_sysMan = new ATMA::SystemManager{};
    ctx->m_resMan = new ATMA::ResourceManager{};
    ctx->m_stateMan = new ATMA::StateManager{};
    ctx->m_eventMan = new ATMA::ObjectEventManager{};
    ctx->m_audioMan = new ATMA::AudioManager{};
    ctx->m_winMan = new ATMA::WindowManager{};
    ctx->m_netMan = new ATMA::NetworkManager{};
    ctx->m_renderer = new ATMA::GLRenderer{};
    return ctx;
}

static inline void destroyContext(ATMA::ATMAContext *l_ctx)
{
    delete l_ctx->m_attrMan;
    delete l_ctx->m_sysMan;
    delete l_ctx->m_resMan;
    delete l_ctx->m_stateMan;
    delete l_ctx->m_eventMan;
    delete l_ctx->m_audioMan;
    delete l_ctx->m_winMan;
    delete l_ctx->m_netMan;
    delete l_ctx->m_renderer;

    delete l_ctx;
}
