#pragma once
#include "AtominaTest.hpp"
#include "AttributeFixtures.hpp"

// All Attribute data types
using AttributeTypes =
    ::testing::Types<ATMA::AttrShape, ATMA::AttrControllable, ATMA::AttrVelocity, ATMA::AttrRenderable, ATMA::AttrCollidable>;