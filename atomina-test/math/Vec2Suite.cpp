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

/**
 * Tests that scalar multiplication of vector 2 gives the correct result
 */
TYPED_TEST(Vector2TestFixture, DivideTest)
{
    this->divideTest({4, 6}, 2, {2, 3});
}

/**
 * Tests that normalization of a vector gives correct result
*/
TYPED_TEST(Vector2TestFixture, NormalizeTest)
{
    this->normTest(
        {1, 1}, {1 / static_cast<TypeParam>(std::sqrt(2)), 1 / static_cast<TypeParam>(std::sqrt(2))}
    );
}

/**
 * Normalizing a vector with a zero component does not break normalization
*/
TYPED_TEST(Vector2TestFixture, NormalizeTestAxis)
{
    this->normTest({1, 0}, {1, 0});
}

/**
 * Normalizing a zero vector will return the zero vector
*/
TYPED_TEST(Vector2TestFixture, NormalizeTestZero)
{
    this->normTest({0, 0}, {0, 0});
}
