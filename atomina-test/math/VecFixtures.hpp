#pragma once
//conversion to template types causing warning
#include "AtominaTest.hpp"

template <class T>
class Vector2TestFixture: public ::testing::Test
{
protected:

	void addTest(ATMA::Vec2<T> a, ATMA::Vec2<T> b, ATMA::Vec2<T> exp) 
	{
        ATMA::Vec2<T> res = a + b;
        EXPECT_TRUE(res.x == exp.x);
        EXPECT_TRUE(res.y == exp.y);
	}

	void subTest(ATMA::Vec2<T> a, ATMA::Vec2<T> b, ATMA::Vec2<T> exp)
    {
        ATMA::Vec2<T> res = a - b;
        EXPECT_TRUE(res.x == exp.x);
        EXPECT_TRUE(res.y == exp.y);
    }

    void dotTest(ATMA::Vec2<T> a, ATMA::Vec2<T> b, T exp)
    {
        T res = a * b;
        EXPECT_TRUE(res == exp);
    }

    void scalarTest(ATMA::Vec2<T> a, T b, ATMA::Vec2<T> exp) 
    {
        ATMA::Vec2<T> res = a * b;
        EXPECT_TRUE(res.x == exp.x);
        EXPECT_TRUE(res.y == exp.y);
    }

};