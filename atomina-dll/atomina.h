
#pragma once
#include "pch.h"
//Client facing header file that has all the includes needed,
//so that only this file needs to be included

#include "api.h"

//Util
#include "AtominaException.h"
#include "Log.h"
#include "ATConst.h"
#include "Worker.h"

//Math
#include "RandomGenerator.h"
#include "MathUtil.h"

//Core
#include "Game.h"
#include "Entry.h"
#include "ATMAContext.h"

//Messaging
#include "Communicator.h"
#include "MessageHandler.h"
#include "Observer.h"

//File
#include "FileHandler.h"
#include "FileUtil.h"

//Network

#include "NetworkClient.h"
#include "NetworkHost.h"

//Events
#include "Event.h"
#include "EventContext.h"
#include "EventManager.h"

//States

#include "State.h"
#include "BaseState.h"
#include "DummyState.h"
#include "StateManager.h"

//OAS
#include "Attribute.h"
#include "System.h"
#include "AttrBase.h"
#include "AttrTranslatable.h"
#include "SysTranslator.h"
#include "SysBase.h"
#include "ObjectMessage.h"
#include "ObjectManager.h"
#include "SystemManager.h"

//Graphic
#include "Window.h"
#include "SpriteSheet.h"
#include "AnimBase.h"
#include "AnimIdle.h"
