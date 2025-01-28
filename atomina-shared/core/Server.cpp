#include "pch.hpp"
#include "Server.hpp"

namespace ATMA
{

    Server::Server() {}

    Server::~Server() {}

    void Server::initializeContext()
    {
        //--SETUP--//

        auto &ctx = ATMAContext::getContext();

        GLContext::init();
        // attribute registration
        ctx.registerAttributeType<AttrControllable>(AttributeType(Attribute::Controllable));
        ctx.registerAttributeType<AttrShape>(AttributeType(Attribute::Shape));
        ctx.registerAttributeType<AttrVelocity>(AttributeType(Attribute::Velocity));
        ctx.registerAttributeType<AttrCollidable>(AttributeType(Attribute::Collidable));

        // system registration
        ctx.addSystemType<SysController>(SystemType(System::Controller));
        ctx.addSystemType<SysTranslator>(SystemType(System::Translator));
        ctx.addSystemType<SysCollider>(SystemType(System::Collider));
    }

    void Server::setup(ATMAContext &l_ctx) {}

    void Server::update(ATMAContext &l_ctx) {}

    void Server::shutdown(ATMAContext &l_ctx) {}
}