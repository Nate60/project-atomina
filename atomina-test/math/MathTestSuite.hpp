#pragma once
#include "AtominaTest.hpp"
#include "MathTestFixtures.hpp"

//All data type implementations of interpolation function
using InterpolationTestTypes = ::testing::Types<int, float, double>;
//All data type implementations of perlin noise function
using PerlinTestTypes = ::testing::Types<float, double>;
