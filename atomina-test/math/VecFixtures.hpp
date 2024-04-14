#pragma once
// conversion to template types causing warning
#include "AtominaTest.hpp"

/**
 * @brief Fixture for testing Vector 2 of varying subtypes
 * @tparam T subtype of the vector
 */
template<class T>
class Vector2TestFixture: public ::testing::Test
{
protected:
    /**
     * @brief helper function to test addition of vectors
     * @param a first vector
     * @param b second vector
     * @param exp expected resulting vector
     */
    void addTest(ATMA::Vec2<T> a, ATMA::Vec2<T> b, ATMA::Vec2<T> exp)
    {
        ATMA::Vec2<T> res = a + b;
        EXPECT_TRUE(res == exp);
    }

    /**
     * @brief helper function to test subtraction of vectors
     * @param a first vector
     * @param b second vector
     * @param exp expected resulting vector
     */
    void subTest(ATMA::Vec2<T> a, ATMA::Vec2<T> b, ATMA::Vec2<T> exp)
    {
        ATMA::Vec2<T> res = a - b;
        EXPECT_TRUE(res == exp);
    }

    /**
     * @brief helper function to test dot product of vectors
     * @param a first vector
     * @param b second vector
     * @param exp expected resulting value
     */
    void dotTest(ATMA::Vec2<T> a, ATMA::Vec2<T> b, T exp)
    {
        T res = a * b;
        EXPECT_TRUE(res == exp);
    }

    /**
     * @brief helper function to test scalar multiplication
     * @param a vector
     * @param b scalar
     * @param exp expected resulting vector
     */
    void scalarTest(ATMA::Vec2<T> a, T b, ATMA::Vec2<T> exp)
    {
        ATMA::Vec2<T> res = a * b;
        EXPECT_TRUE(res == exp);
    }
};

/**
 * @brief Fixture for testing Vector 2 of varying subtypes
 * @tparam T subtype of the vector
 */
template<class T>
class Vector3TestFixture: public ::testing::Test
{
protected:
    /**
     * @brief helper function to test addition of vectors
     * @param a first vector
     * @param b second vector
     * @param exp expected resulting vector
     */
    void addTest(ATMA::Vec3<T> a, ATMA::Vec3<T> b, ATMA::Vec3<T> exp)
    {
        ATMA::Vec3<T> res = a + b;
        EXPECT_TRUE(res == exp);
    }

    /**
     * @brief helper function to test subtraction of vectors
     * @param a first vector
     * @param b second vector
     * @param exp expected resulting vector
     */
    void subTest(ATMA::Vec3<T> a, ATMA::Vec3<T> b, ATMA::Vec3<T> exp)
    {
        ATMA::Vec3<T> res = a - b;
        EXPECT_TRUE(res == exp);
    }

    /**
     * @brief helper function to test dot product of vectors
     * @param a first vector
     * @param b second vector
     * @param exp expected resulting value
     */
    void dotTest(ATMA::Vec3<T> a, ATMA::Vec3<T> b, T exp)
    {
        T res = a * b;
        EXPECT_TRUE(res == exp);
    }

    /**
     * @brief helper function to test scalar multiplication
     * @param a vector
     * @param b scalar
     * @param exp expected resulting vector
     */
    void scalarTest(ATMA::Vec3<T> a, T b, ATMA::Vec3<T> exp)
    {
        ATMA::Vec3<T> res = a * b;
        EXPECT_TRUE(res == exp);
    }

    void crossTest(ATMA::Vec3<T> a, ATMA::Vec3<T> b, ATMA::Vec3<T> exp)
    {
        ATMA::Vec3<T> res = ATMA::cross(a, b);
        EXPECT_TRUE(res == exp);
    }
};