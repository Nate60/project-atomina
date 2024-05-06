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
 * Tests that scalar multiplication of vector 2 gives the correct result
 */
TYPED_TEST(Vector3TestFixture, DivideTest)
{
    this->divideTest({4, 6, 2}, 2, {2, 3, 1});
}

/**
 * Tests that cross product of vector 3 gives the correct result
 */
TYPED_TEST(Vector3TestFixture, CrossProductTest)
{
    this->crossTest({1, 0, 0}, {0, 1, 0}, {0, 0, 1});
}

/**
 * Tests that normalization of a vector gives correct result
*/
TYPED_TEST(Vector3TestFixture, NormalizeTest)
{
    this->normTest(
        {1, 1, 1},
        {1 / static_cast<TypeParam>(std::sqrt(3)),
         1 / static_cast<TypeParam>(std::sqrt(3)),
         1 / static_cast<TypeParam>(std::sqrt(3))}
    );
}

/**
 * Normalizing a vector with a zero component does not break normalization
*/
TYPED_TEST(Vector3TestFixture, NormalizeTestAxis)
{
    this->normTest({1, 0, 0}, {1, 0, 0});
}

/**
 * Normalizing a zero vector will return the zero vector
*/
TYPED_TEST(Vector3TestFixture, NormalizeTestZero)
{
    this->normTest({0, 0, 0}, {0, 0, 0});
}