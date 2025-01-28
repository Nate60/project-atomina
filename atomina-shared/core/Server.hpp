#pragma once
#include "pch.hpp"
#include "api.hpp"
#include "util/Log.hpp"
#include "ATMAContext.hpp"
#include "render/GLContext.hpp"
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

namespace ATMA
{

    /**
     * App interface to be implemented by the server and called by the
     * engine
     */
    class Server
    {
    public:
        // default constructor
        Server();

        // virtual desconstructor
        virtual ~Server();

        /**
         * Registers all default systems, and attributes, so that
         * it does not need to be done by the game since it may not
         * know all available types
         */
        void initializeContext();

        /**
        * use for any pre game-loop setup as it will be executed before
        * creating the game loop
        */
        virtual void setup(ATMAContext &l_ctx);

        /**
         * stub virtual function to be extended and implemented by the game
         * and contains the main game loop
         */
        virtual void update(ATMAContext &l_ctx);

        /**
         * stub function to be implemented by the game to initiate shutdown
         * and start clean up of the app
         */
        virtual void shutdown(ATMAContext &l_ctx);

        bool active = false;
    };

}
