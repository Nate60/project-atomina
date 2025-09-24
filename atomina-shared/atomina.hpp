
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
#include "util/Path.hpp"

// Math
#include "math/Vec2.hpp"
#include "math/Vec3.hpp"
#include "math/Mat3.hpp"
#include "math/Stadium.hpp"
#include "math/RandomGenerator.hpp"
#include "math/MathFuncs.hpp"

// Core
#include "core/Game.hpp"
#include "core/Server.hpp"
#include "core/Engine.hpp"
#include "core/ATMAContext.hpp"

// File
#include "file/FileHandler.hpp"
#include "file/FileFuncs.hpp"
#include "file/FileSystem.hpp"

// Events
#include "event/ObjectEventContext.hpp"
#include "event/ObjectEvent.hpp"
#include "event/ObjectEventManager.hpp"

// States
#include "state/State.hpp"
#include "state/BaseState.hpp"
#include "state/states/DummyState.hpp"
#include "state/StateManager.hpp"

// OAS
#include "OAS/Attribute.hpp"
#include "OAS/System.hpp"
#include "OAS/AttrBase.hpp"
#include "OAS/attributes/AttrShape.hpp"
#include "OAS/attributes/AttrControllable.hpp"
#include "OAS/attributes/AttrVelocity.hpp"
#include "OAS/attributes/AttrCollidable.hpp"
#include "OAS/AttributeManager.hpp"
#include "OAS/SysBase.hpp"
#include "OAS/systems/SysTranslator.hpp"
#include "OAS/systems/SysController.hpp"
#include "OAS/systems/SysRenderer.hpp"
#include "OAS/systems/SysAnimator.hpp"
#include "OAS/systems/SysCollider.hpp"
#include "OAS/SystemManager.hpp"

// Resource
#include "resource/Resource.hpp"
#include "resource/ResourceLoader.hpp"
#include "resource/ResourceEnum.hpp"
#include "resource/DummyResource.hpp"
#include "resource/ResourceManager.hpp"
#include "resource/loaders/MapdataLoader.hpp"
#include "resource/loaders/TilesetLoader.hpp"
#include "resource/loaders/AnimationLoader.hpp"
#include "resource/loaders/AudioWaveLoader.hpp"
#include "resource/loaders/GLTextureLoader.hpp"
#include "resource/loaders/GLShaderLoader.hpp"
#include "resource/loaders/DummyResourceLoader.hpp"
#include "resource/writers/MapdataWriter.hpp"
#include "resource/writers/TilesetWriter.hpp"
#include "resource/writers/AnimationWriter.hpp"
#include "resource/writers/AudioWaveWriter.hpp"
#include "resource/writers/GLShaderWriter.hpp"
#include "resource/writers/DummyResourceWriter.hpp"

#include "resource/graphics/Animation.hpp"
#include "resource/graphics/Tileset.hpp"
#include "resource/map/Mapdata.hpp"

// Network
#include "network/URL.hpp"
#include "network/Socket.hpp"
#include "network/SocketListener.hpp"
#include "network/NetworkManager.hpp"
#include "network/NetworkMessageTypes.hpp"
#include "network/NetworkMessage.hpp"
#include "network/NetworkSerde.hpp"

// GUI
#include "GUI/AppWindow.hpp"
#include "GUI/KeyCode.hpp"
#include "GUI/WindowManager.hpp"

// Time
#include "time/Clock.hpp"
#include "time/StopWatch.hpp"

// Render
#include "render/GLBuffer.hpp"
#include "render/GLProgram.hpp"
#include "render/Renderer.hpp"
#include "render/GLShader.hpp"
#include "render/GLTexture.hpp"
#include "render/GLRenderContext.hpp"
#include "render/GLContext.hpp"
#include "render/Camera.hpp"
#include "render/Text.hpp"
#include "render/renderImpl/Dummy/GLBufferDummyImpl.hpp"
#include "render/renderImpl/Dummy/GLProgramDummyImpl.hpp"
#include "render/renderImpl/Dummy/GLShaderDummyImpl.hpp"
#include "render/renderImpl/Dummy/GLTextureDummyImpl.hpp"
#include "render/renderImpl/Dummy/GLRenderContextDummyImpl.hpp"
#include "render/renderImpl/OpenGL/GLBufferOpenGLImpl.hpp"
#include "render/renderImpl/OpenGL/GLProgramOpenGLImpl.hpp"
#include "render/renderImpl/OpenGL/GLShaderOpenGLImpl.hpp"
#include "render/renderImpl/OpenGL/GLTextureOpenGLImpl.hpp"
#include "render/renderImpl/OpenGL/GLRenderContextOpenGLImpl.hpp"

// Sound
#include "sound/AudioManager.hpp"
#include "sound/AudioWave.hpp"
#include "sound/AudioChannel.hpp"

#ifdef _WIN32
// Network
#    include "platform/Win/network/SocketWinImpl.hpp"
#    include "platform/Win/network/SocketListenerWinImpl.hpp"
#    include "platform/Win/sound/AudioChannelWinImpl.hpp"
#    include "platform/Win/file/FileSystem.hpp"
#elif __linux__
// Network
#    include "platform/Linux/network/SocketUnixImpl.hpp"
#    include "platform/Linux/network/SocketListenerUnixImpl.hpp"
#    include "platform/Linux/sound/AudioChannelUnixImpl.hpp"
#    include "platform/Linux/file/FileSystem.hpp"
#endif
