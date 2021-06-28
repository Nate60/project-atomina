
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

//Core
#include "Game.h"
#include "Entry.h"

//Events
#include "Event.h"
#include "EventType.h"
#include "KeyEvent.h"
#include "MouseEvent.h"

//Math
#include "RandomGenerator.h"
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
