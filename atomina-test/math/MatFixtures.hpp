#pragma once
// conversion to template types causing warning
#include "AtominaTest.hpp"

/**
 * @brief Fixture for testing Matrix 3 of varying subtypes
 * @tparam T subtype of the Matrix
 */
template<class T>
class Matrix3TestFixture: public ::testing::Test
{
protected:
    /**
     * @brief helper function to test addition of Matrix
     * @param a first matrix
     * @param b second matrix
     * @param exp expected resulting matrix
     */
    void addTest(ATMA::Mat3<T> a, ATMA::Mat3<T> b, ATMA::Mat3<T> exp)
    {
        ATMA::Mat3<T> res = a + b;
        EXPECT_TRUE(res == exp);
    }

    /**
     * @brief helper function to test subtraction of matrices
     * @param a first matrix
     * @param b second matrix
     * @param exp expected resulting matrix
     */
    void subTest(ATMA::Mat3<T> a, ATMA::Mat3<T> b, ATMA::Mat3<T> exp)
    {
        ATMA::Mat3<T> res = a - b;
        EXPECT_TRUE(res == exp);
    }

    /**
     * @brief helper function to test scalar multiplication
     * @param a matrix
     * @param b scalar
     * @param exp expected resulting matrix
     */
    void scalarTest(ATMA::Mat3<T> a, T b, ATMA::Mat3<T> exp)
    {
        ATMA::Mat3<T> res = a * b;
        EXPECT_TRUE(res == exp);
    }

    /**
     * @brief helper function to test multiplication of matrices
     * @param a first matrix
     * @param b second matrix
     * @param exp expected resulting matrix
     */
    void multTest(ATMA::Mat3<T> a, ATMA::Mat3<T> b, ATMA::Mat3<T> exp)
    {
        ATMA::Mat3<T> res = a * b;
        EXPECT_TRUE(res == exp);
    }

    /**
     * @brief helper function to test transformation of vectors
     * @param a matrix
     * @param b vector
     * @param exp expected resulting vector
     */
    void transformTest(ATMA::Mat3<T> a, ATMA::Vec3<T> b, ATMA::Vec3<T> exp)
    {
        ATMA::Vec3<T> res = a * b;
        EXPECT_TRUE(res == exp);
    }
};