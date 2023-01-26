#include "Vec2Suite.hpp"

TYPED_TEST_SUITE(Vector2TestFixture, Vec2TestTypes);

/**
 * Tests that addition of vector 2 gives the correct result
 */
TYPED_TEST(Vector2TestFixture, AddTest)
{
    this->addTest({1, 2}, {3, 4}, {4, 6});
}

/**
 * Tests that subtraction of vector 2 gives the correct result
 */
TYPED_TEST(Vector2TestFixture, SubTest)
{
    this->subTest({4, 4}, {2, 2}, {2, 2});
}

/**
 * Tests that dot product of vector 2 gives the correct result
 */
TYPED_TEST(Vector2TestFixture, DotTest)
{
    this->dotTest({1, 2}, {3, 4}, 11);
}

/**
 * Tests that scalar multiplication of vector 2 gives the correct result
 */
TYPED_TEST(Vector2TestFixture, ScalarTest)
{
    this->scalarTest({2, 3}, 2, {4, 6});
}
