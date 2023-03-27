#include "Vec3Suite.hpp"

TYPED_TEST_SUITE(Vector3TestFixture, Vec3TestTypes);

/**
 * Tests that addition of vector 3 gives the correct result
 */
TYPED_TEST(Vector3TestFixture, AddTest)
{
    this->addTest({1, 2, 3}, {4, 5, 6}, {5, 7, 9});
}

/**
 * Tests that subtraction of vector 3 gives the correct result
 */
TYPED_TEST(Vector3TestFixture, SubTest)
{
    this->subTest({4, 4, 4}, {2, 2, 2}, {2, 2, 2});
}

/**
 * Tests that dot product of vector 3 gives the correct result
 */
TYPED_TEST(Vector3TestFixture, DotTest)
{
    this->dotTest({1, 2, 3}, {4, 5, 6}, 32);
}

/**
 * Tests that scalar multiplication of vector 3 gives the correct result
 */
TYPED_TEST(Vector3TestFixture, ScalarTest)
{
    this->scalarTest({2, 3, 1}, 2, {4, 6, 2});
}

/**
 * Tests that cross product of vector 3 gives the correct result
 */
TYPED_TEST(Vector3TestFixture, CrossProductTest)
{
    this->crossTest({1, 0, 0}, {0, 1, 0}, {0, 0, 1});
}