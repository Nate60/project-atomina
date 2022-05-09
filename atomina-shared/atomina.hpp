
#pragma once
#include "pch.hpp"
//Client facing header file that has all the includes needed,
//so that only this file needs to be included

#include "core/api.hpp"

//Util
#include "util/AtominaException.hpp"
#include "util/Log.hpp"
#include "util/ATConst.hpp"
#include "util/Worker.hpp"

//Math
#include "math/RandomGenerator.hpp"
#include "math/MathFuncs.hpp"

//Core
#include "core/Game.hpp"
#include "core/Entry.hpp"
#include "core/ATMAContext.hpp"

//Messaging
#include "message/Communicator.hpp"
#include "message/MessageHandler.hpp"
#include "message/Observer.hpp"

//File
#include "file/FileHandler.hpp"
#include "file/FileFuncs.hpp"

//Network

#include "network/NetworkClient.hpp"
#include "network/NetworkHost.hpp"

//Events
#include "event/Event.hpp"
#include "event/EventContext.hpp"
#include "event/EventManager.hpp"

//States

#include "state/State.hpp"
#include "state/BaseState.hpp"
#include "state/states/DummyState.hpp"
#include "state/StateManager.hpp"

//OAS
#include "OAS/Attribute.hpp"
#include "OAS/System.hpp"
#include "OAS/AttrBase.hpp"
#include "OAS/attributes/AttrTranslatable.hpp"
#include "OAS/attributes/AttrControllable.hpp"
#include "OAS/attributes/AttrDrawable.hpp"
#include "OAS/SysBase.hpp"
#include "OAS/systems/SysTranslator.hpp"
#include "OAS/systems/SysRenderer.hpp"
#include "OAS/systems/SysController.hpp"
#include "OAS/ObjectMessage.hpp"
#include "OAS/ObjectManager.hpp"
#include "OAS/SystemManager.hpp"


//Graphic
#include "graphics/Window.hpp"
#include "graphics/SpriteSheet.hpp"
#include "graphics/AnimBase.hpp"
#include "graphics/animation/AnimIdle.hpp"

//Sound
#include "sound/SoundManager.hpp"
#include "sound/SoundProperties.hpp"

