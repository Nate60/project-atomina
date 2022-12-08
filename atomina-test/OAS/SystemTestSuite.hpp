#pragma once
#include "../AtominaTest.hpp"
#include "SystemFixtures.hpp"
#include "TestSystem.hpp"
#include "state/TestState.hpp"

//All data types for Systems
using SystemTypes = ::testing::Types<ATMA::SysTranslator, ATMA::SysRenderer, ATMA::SysController, ATMA::SysGUI>;

