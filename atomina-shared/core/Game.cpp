#include "pch.hpp"
#include "Game.hpp"

namespace ATMA
{

    Game::Game() {}

    Game::~Game() {}

    void Game::initializeContext()
    {
        auto &ctx = ATMAContext::getContext();
            //--SETUP--//

        // attribute registration
        ctx.registerAttributeType<AttrAnimation>(AttributeType(Attribute::Animation));
        ctx.registerAttributeType<AttrControllable>(
            AttributeType(Attribute::Controllable)
        );
        ctx.registerAttributeType<AttrGraphic>(AttributeType(Attribute::Graphic));
        ctx.registerAttributeType<AttrMouseRegion>(
            AttributeType(Attribute::MouseRegion)
        );
        ctx.registerAttributeType<AttrMouseTrigger>(
            AttributeType(Attribute::MouseTrigger)
        );
        ctx.registerAttributeType<AttrPosition>(AttributeType(Attribute::Position));
        ctx.registerAttributeType<AttrVelocity>(AttributeType(Attribute::Velocity));

        // system registration
        ctx.addSystemType<SysAnimator>(SystemType(System::Animator));
        ctx.addSystemType<SysController>(SystemType(System::Controller));
        ctx.addSystemType<SysGUI>(SystemType(System::GUI));
        ctx.addSystemType<SysRenderer>(SystemType(System::Renderer));
        ctx.addSystemType<SysTranslator>(SystemType(System::Translator));

        // link systems to events
        auto guiSystem = ctx.getSystem<SysGUI>(SystemType(System::GUI));
        ctx.addObjectEventListener(ObjectEventType(ObjectEvent::MouseOver), guiSystem);
        ctx.addObjectEventListener(ObjectEventType(ObjectEvent::MousePressed), guiSystem);
        ctx.addObjectEventListener(ObjectEventType(ObjectEvent::MouseReleased), guiSystem);
    }

    void Game::run()
    {

        active = true;
    }

    void Game::shutdown() {}
}