
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
#include "util/RetryExecutor.hpp"

// Math
#include "math/Vec2.hpp"
#include "math/Vec3.hpp"
#include "math/Mat3.hpp"
#include "math/RandomGenerator.hpp"
#include "math/MathFuncs.hpp"

// Core
#include "core/Game.hpp"
#include "core/Entry.hpp"
#include "core/ATMAContext.hpp"
#include "core/ATMAFormats.hpp"

// File
#include "file/FileHandler.hpp"
#include "file/FileFuncs.hpp"

// Events
#include "event/ObjectEventContext.hpp"
#include "event/ObjectEvent.hpp"

// States

#include "state/State.hpp"
#include "state/BaseState.hpp"
#include "state/states/DummyState.hpp"

// OAS
#include "OAS/Attribute.hpp"
#include "OAS/System.hpp"
#include "OAS/AttrBase.hpp"
#include "OAS/attributes/AttrShape.hpp"
#include "OAS/attributes/AttrControllable.hpp"
#include "OAS/SysBase.hpp"
#include "OAS/systems/SysTranslator.hpp"
#include "OAS/systems/SysController.hpp"

// Resource
#include "resource/Resource.hpp"
#include "resource/DummyResource.hpp"
#include "resource/graphics/AnimBase.hpp"
#include "resource/graphics/animation/AnimDefault.hpp"
#include "resource/graphics/animation/AnimIdle.hpp"

// Network
#include "network/URL.hpp"
#include "network/Socket.hpp"
#include "network/SocketListener.hpp"
#ifdef _WINDOWS
#    include "network/socket/SocketWinImpl.hpp"
#    include "network/socket/SocketListenerWinImpl.hpp"
#elif __linux__
#    include "network/socket/SocketUnixImpl.hpp"
#    include "network/socket/SocketListenerUnixImpl.hpp"
#endif
#include "network/NetworkClient.hpp"
#include "network/NetworkHost.hpp"