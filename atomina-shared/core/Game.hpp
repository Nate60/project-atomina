#pragma once
#include "pch.hpp"
#include "api.hpp"
#include "util/Log.hpp"
#include "ATMAContext.hpp"
#include "OAS/attributes/AttrControllable.hpp"
#include "OAS/attributes/AttrShape.hpp"
#include "OAS/attributes/AttrVelocity.hpp"
#include "OAS/systems/SysController.hpp"
#include "OAS/systems/SysTranslator.hpp"

namespace ATMA
{

    /**
     * App interface to be implemented by the game and called by the
     * engine
     */
    class ATMA_API Game
    {
    public:
        // default constructor
        Game();

        // virtual desconstructor
        virtual ~Game();

        /**
         * Registers all default systems, and attributes, so that
         * it does not need to be done by the game since it may not
         * know all available types
         */
        void initializeContext();

        /**
         * stub virtual function to be extended and implemented by the game
         * and contains the main game loop
         */
        virtual void run();

        /**
         * stub function to be implemented by the game to initiate shutdown
         * and start clean up of the app
         */
        virtual void shutdown();

        bool active = false;
    };

}
