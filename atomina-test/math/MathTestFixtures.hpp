#pragma once
// conversion to template types causing warning
#include "AtominaTest.hpp"

/**
 * Test fixture for running interpolation tests
 * against Atomina's interpolation function
 */
template<class T>
class InterpolationTestFixture: public ::testing::Test
{
protected:
    /**
     * function to run tests against a given interpolation
     * function
     * @param f Interpolation function that returns a float value
     */
    void interpolateTest(std::function<T(T, T, float)> f)
    {
        // middle
        T x1 = 0;
        T x2 = 10;
        float w = 0.5;
        T result = f(x1, x2, w);
        EXPECT_EQ(result, 5.0f);
        // end
        w = 1;
        result = f(x1, x2, w);
        EXPECT_EQ(result, 10.0f);
        // start
        w = 0;
        result = f(x1, x2, w);
        EXPECT_EQ(result, 0.0f);
        // empty
        x2 = 0;
        result = f(x1, x2, w);
        EXPECT_EQ(result, 0.0f);
        // negative
        x1 = 5;
        x2 = -10;
        w = 0.5;
        T exp = static_cast<T>(-2.5f); // int will truncate
        result = f(x1, x2, w);
        EXPECT_EQ(result, exp);
    }
};

/**
 * Test fixture for running perlin noise function tests
 * against Atomina's perlin noise function
 */
template<class T>
class PerlinTestFixture: public ::testing::Test
{
protected:
    /**
     * function to run tests against a given implementation of
     * perlin noise
     * @param f function that implements perlin noise and returns a float
     * @param l_exp expected value of the given function
     */
    void perlinTest(std::function<T(T, T, float)> f, T l_exp)
    {
        ATMA::Vec2<T> gradient[4] = {
            {0, 0},
            {1, 0},
            {0, 1},
            {1, 1}
        };
        T x = static_cast<T>(0.5);
        T y = static_cast<T>(0.5);
        T result = ATMA::perlin(gradient, f, x, y);
        EXPECT_EQ(result, l_exp);
    }
};
