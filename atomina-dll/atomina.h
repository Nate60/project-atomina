
#pragma once
#include "pch.h"
//Client facing header file that has all the includes needed,
//so that only this file needs to be included

#include "api.h"

//Util
#include "AtominaException.h"
#include "MathUtil.h"
#include "SysUtil.h"
#include "Log.h"

//Math
#include "RandomGenerator.h"

//Core
#include "Game.h"
#include "Entry.h"

//Network

#include "NetworkClient.h"
#include "NetworkHost.h"

//Events
#include "Event.h"
#include "EventType.h"

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
