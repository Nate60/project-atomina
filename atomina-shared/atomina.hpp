
#pragma once
#include "pch.hpp"
// Client facing header file that has all the includes needed,
// so that only this file needs to be included

#include "core/api.hpp"

// Util
#include "util/AtominaException.hpp"
#include "util/Log.hpp"
#include "util/ATConst.hpp"
#include "util/Worker.hpp"
#include "util/Props.hpp"

// Math
#include "math/RandomGenerator.hpp"
#include "math/MathFuncs.hpp"

// Core
#include "core/Game.hpp"
#include "core/Entry.hpp"
#include "core/ATMAContext.hpp"

// File
#include "file/FileHandler.hpp"
#include "file/FileFuncs.hpp"

// Network

#include "network/NetworkClient.hpp"
#include "network/NetworkHost.hpp"

// Events
#include "event/ObjectEventContext.hpp"
#include "event/ObjectEvent.hpp"
#include "event/WindowEvent.hpp"

// States

#include "state/State.hpp"
#include "state/BaseState.hpp"
#include "state/states/DummyState.hpp"

// OAS
#include "OAS/Attribute.hpp"
#include "OAS/System.hpp"
#include "OAS/AttrBase.hpp"
#include "OAS/attributes/AttrPosition.hpp"
#include "OAS/attributes/AttrControllable.hpp"
#include "OAS/attributes/AttrGraphic.hpp"
#include "OAS/attributes/AttrAnimation.hpp"
#include "OAS/attributes/AttrMouseRegion.hpp"
#include "OAS/attributes/AttrMouseTrigger.hpp"
#include "OAS/SysBase.hpp"
#include "OAS/systems/SysTranslator.hpp"
#include "OAS/systems/SysRenderer.hpp"
#include "OAS/systems/SysController.hpp"
#include "OAS/systems/SysAnimator.hpp"
#include "OAS/systems/SysGUI.hpp"

// Graphics
#include "resource/graphics/SpriteSheet.hpp"
#include "resource/graphics/AnimBase.hpp"
#include "resource/graphics/animation/AnimIdle.hpp"
#include "resource/graphics/animation/AnimDefault.hpp"

// Sound
#include "resource/sound/SoundProperties.hpp"
#include "resource/sound/Music.hpp"

// GUI
#include "GUI/Window.hpp"
