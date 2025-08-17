#include "pch.hpp"
#include "Server.hpp"
#include "OAS/AttributeManager.hpp"
#include "OAS/SystemManager.hpp"
#include "render/GLRenderer.hpp"
#include "resource/ResourceManager.hpp"
#include "state/StateManager.hpp"
#include "event/ObjectEventManager.hpp"
#include "sound/AudioManager.hpp"
#include "GUI/WindowManager.hpp"
#include "event/ObjectEventManager.hpp"
#include "network/NetworkManager.hpp"
#include "render/GLRenderer.hpp"

namespace ATMA
{

    Server::Server() {}

    Server::~Server() {}

    ATMAContext *Server::initializeContext()
    {
        //--SETUP--//

        ATMAContext *ctx = new ATMAContext();

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
        ctx->m_attrMan->registerAttributeType<AttrCollidable>(AttributeType(Attribute::Collidable));

        // system registration
        ctx->m_sysMan->addSystemType<SysController>(ctx, SystemType(System::Controller));
        ctx->m_sysMan->addSystemType<SysTranslator>(ctx, SystemType(System::Translator));
        ctx->m_sysMan->addSystemType<SysCollider>(ctx, SystemType(System::Collider));
        return ctx;
    }

    void Server::destoryContext(ATMAContext *l_ctx)
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

    void Server::setup(ATMAContext *l_ctx) {}

    void Server::update(ATMAContext *l_ctx, const long long &l_dt) {}

    void Server::shutdown(ATMAContext *l_ctx) {}
}
