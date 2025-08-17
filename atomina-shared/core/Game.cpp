#include "event/ObjectEventManager.hpp"
#include "network/NetworkManager.hpp"
#include "pch.hpp"
#include "Game.hpp"
#include "core/ATMAContext.hpp"
#include "OAS/attributes/AttrControllable.hpp"
#include "OAS/attributes/AttrShape.hpp"
#include "OAS/attributes/AttrVelocity.hpp"
#include "OAS/attributes/AttrRenderable.hpp"
#include "OAS/attributes/AttrText.hpp"
#include "OAS/attributes/AttrSprite.hpp"
#include "OAS/attributes/AttrCollidable.hpp"
#include "OAS/systems/SysController.hpp"
#include "OAS/systems/SysTranslator.hpp"
#include "OAS/systems/SysRenderer.hpp"
#include "OAS/systems/SysCollider.hpp"
#include "OAS/AttributeManager.hpp"
#include "OAS/SystemManager.hpp"
#include "render/GLRenderer.hpp"
#include "resource/ResourceManager.hpp"
#include "state/StateManager.hpp"
#include "event/ObjectEventManager.hpp"
#include "sound/AudioManager.hpp"
#include "GUI/WindowManager.hpp"

namespace ATMA
{

    Game::Game() {}

    Game::~Game() {}

    ATMAContext *Game::initializeContext()
    {

        ATMAContext *ctx = new ATMAContext{};
        ctx->m_attrMan = new AttributeManager{};
        ctx->m_sysMan = new SystemManager{};
        ctx->m_resMan = new ResourceManager{};
        ctx->m_stateMan = new StateManager{};
        ctx->m_eventMan = new ObjectEventManager{};
        ctx->m_audioMan = new AudioManager{};
        ctx->m_winMan = new WindowManager{};
        ctx->m_netMan = new NetworkManager{};
        ctx->m_renderer = new GLRenderer{};

        GLContext::init();
        // attribute registration
        ctx->m_attrMan->registerAttributeType<AttrControllable>(AttributeType(Attribute::Controllable));
        ctx->m_attrMan->registerAttributeType<AttrShape>(AttributeType(Attribute::Shape));
        ctx->m_attrMan->registerAttributeType<AttrVelocity>(AttributeType(Attribute::Velocity));
        ctx->m_attrMan->registerAttributeType<AttrRenderable>(AttributeType(Attribute::Render));
        ctx->m_attrMan->registerAttributeType<AttrText>(AttributeType(Attribute::Text));
        ctx->m_attrMan->registerAttributeType<AttrSprite>(AttributeType(Attribute::Sprite));
        ctx->m_attrMan->registerAttributeType<AttrCollidable>(AttributeType(Attribute::Collidable));

        // system registration
        ctx->m_sysMan->addSystemType<SysController>(ctx, SystemType(System::Controller));
        ctx->m_sysMan->addSystemType<SysTranslator>(ctx, SystemType(System::Translator));
        ctx->m_sysMan->addSystemType<SysRenderer>(ctx, SystemType(System::Renderer));
        ctx->m_sysMan->addSystemType<SysCollider>(ctx, SystemType(System::Collider));
        return ctx;
    }

    void Game::destoryContext(ATMAContext *l_ctx)
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

    void Game::setup(ATMAContext *l_ctx) {}

    void Game::update(ATMAContext *l_ctx, const long long &l_dt) {}

    void Game::shutdown(ATMAContext *l_ctx) {}
}
