#include "MathTestSuite.hpp"

TYPED_TEST_SUITE(InterpolationTestFixture, InterpolationTestTypes);
TYPED_TEST_SUITE(PerlinTestFixture, PerlinTestTypes);

/**
 * Runs interpolation test function with linear interpolation function
 */
TYPED_TEST(InterpolationTestFixture, LinearInterpolation)
{

    auto f = ATMA::lerp<TypeParam, float>;
    this->interpolateTest(f);
};

/**
 * Runs interpolation helper test funciton with cubic interpolation function
 */
TYPED_TEST(InterpolationTestFixture, CubicInterpolation)
{

    auto f = ATMA::cubeTerp<TypeParam, float>;
    this->interpolateTest(f);
};

/**
 * Runs perlin noise helper test function with linear interpolation function
 */
TYPED_TEST(PerlinTestFixture, PerlinNoiseWithLerp)
{

    auto f = ATMA::lerp<TypeParam, float>;
    TypeParam exp = -0.5;
    this->perlinTest(f, exp);
};

/**
 * Runs perlin noise helper test funciton with cubic interpolation function
 */
TYPED_TEST(PerlinTestFixture, PerlinNoiseWithCubeTerp)
{

    auto f = ATMA::cubeTerp<TypeParam, float>;
    TypeParam exp = -0.5;
    this->perlinTest(f, exp);
};

using IntPerlinTestFixture = PerlinTestFixture<int>;

/**
 * Run perlin noise helper function with linear interpolation
 * Only on int data type because of data truncation
 */
TEST_F(IntPerlinTestFixture, PerlinNoiseWithLerpInt)
{
    auto f = ATMA::lerp<int, float>;
    int exp = 0;
    this->perlinTest(f, exp);
}

/**
 * Run perlin noise helper function with cubic interpolation
 * Only on int data type because of data truncation
 */
TEST_F(IntPerlinTestFixture, PerlinNoiseWithCubeTerpInt)
{
    auto f = ATMA::cubeTerp<int, float>;
    int exp = 0;
    this->perlinTest(f, exp);
}
