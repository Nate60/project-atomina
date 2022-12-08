#pragma once
#include "AtominaTest.hpp"
#include "AttributeFixtures.hpp"
#include "OAS/attributes/AttrAnimation.hpp"
#include "OAS/attributes/AttrGraphic.hpp"
#include "OAS/attributes/AttrMouseRegion.hpp"
#include "OAS/attributes/AttrMouseTrigger.hpp"
#include "OAS/attributes/AttrVelocity.hpp"

// All Attribute data types
using AttributeTypes = ::testing::Types<
    ATMA::AttrPosition,
    ATMA::AttrGraphic,
    ATMA::AttrControllable,
    ATMA::AttrMouseTrigger,
    ATMA::AttrMouseRegion,
    ATMA::AttrVelocity,
    ATMA::AttrAnimation>;