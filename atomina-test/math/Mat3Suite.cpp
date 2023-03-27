#include "Mat3Suite.hpp"

TYPED_TEST_SUITE(Matrix3TestFixture, Mat3TestTypes);

/**
 * Tests that addition of matrix 3 gives the correct result
 */
TYPED_TEST(Matrix3TestFixture, AddTest)
{
    this->addTest(
        {
            {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}
    },
        {{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}},
        {{{2, 4, 6}, {8, 10, 12}, {14, 16, 18}}}
    );
}

/**
 * Tests that subtraction of matrix 3 gives the correct result
 */
TYPED_TEST(Matrix3TestFixture, SubTest)
{
    this->subTest(
        {
            {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}
    },
        {{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}},
        {{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}}
    );
}

/**
 * Tests that scalar multiplication of matrix 3 gives the correct result
 */
TYPED_TEST(Matrix3TestFixture, ScalarTest)
{

    this->scalarTest(
        {
            {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}
    },
        3,
        {{{3, 6, 9}, {12, 15, 18}, {21, 24, 27}}}
    );
}

/**
 * Tests that product of matrix 3 gives the correct result
 */
TYPED_TEST(Matrix3TestFixture, ProductTest)
{

    this->multTest(
        {
            {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}
    },
        {{{9, 8, 7}, {6, 5, 4}, {3, 2, 1}}},
        {{{30, 24, 18}, {84, 69, 54}, {138, 114, 90}}}
    );
}

/**
 * Tests that scaling of vector 3 gives the correct result
 */
TYPED_TEST(Matrix3TestFixture, ScalingTest)
{
    this->transformTest(ATMA::scalingMatrix<TypeParam>(2, 2), {1, 1, 1}, {2, 2, 1});
}

/**
 * Tests that translating of vector 3 gives the correct result
 */
TYPED_TEST(Matrix3TestFixture, TranslatingTest)
{
    this->transformTest(ATMA::translationMatrix<TypeParam>(2, 2), {1, 1, 1}, {3, 3, 1});
}

/**
 * Tests that rotation of vector 3 gives the correct result
 */
TYPED_TEST(Matrix3TestFixture, RotationTest)
{
    this->transformTest(ATMA::rotationMatrix<TypeParam>(90), {0, 1, 0}, {-1, 0, 0});
}