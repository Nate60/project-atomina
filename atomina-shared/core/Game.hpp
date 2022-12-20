#pragma once
#include "api.hpp"
#include "util/Log.hpp"
#include "ATMAContext.hpp"
#include "OAS/attributes/AttrAnimation.hpp"
#include "OAS/attributes/AttrControllable.hpp"
#include "OAS/attributes/AttrGraphic.hpp"
#include "OAS/attributes/AttrMouseRegion.hpp"
#include "OAS/attributes/AttrMouseTrigger.hpp"
#include "OAS/attributes/AttrPosition.hpp"
#include "OAS/attributes/AttrVelocity.hpp"
#include "OAS/systems/SysAnimator.hpp"
#include "OAS/systems/SysController.hpp"
#include "OAS/systems/SysGUI.hpp"
#include "OAS/systems/SysRenderer.hpp"
#include "OAS/systems/SysTranslator.hpp"

namespace ATMA
{

    class ATMA_API Game
    {
    public:
        Game();
        virtual ~Game();
        void initializeContext();
        virtual void run();
        virtual void shutdown();

        bool active = false;
    };

}

