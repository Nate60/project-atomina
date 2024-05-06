#pragma once
// conversion to template types causing warning
#include "AtominaTest.hpp"

/**
 * Fixture for testing properties of a Stadium
 * @tparam subtype of the Stadium
*/
template<class T>
class StadiumTestFixture: public ::testing::Test
{
protected:
};

/**
 * Fixture for testing collisions between two Stadiums
 * @tparam subtype of the Stadiums
*/
template<class T>
class StadiumCollisionTestFixture: public ::testing::Test
{
protected:
    void collideTest(
        const ATMA::Stadium<T> &a,
        const ATMA::Stadium<T> &b,
        bool exp,
        std::optional<ATMA::Vec2<T>> expVec = std::nullopt
    )
    {
        ATMA::Vec2<T> collideVec;
        bool result = ATMA::getCollideVector(a, b, collideVec);
        EXPECT_EQ(exp, result);
        if(expVec != std::nullopt)
        {
            
            EXPECT_EQ(expVec.value().x, collideVec.x);
            EXPECT_EQ(expVec.value().y, collideVec.y);
        }
    }
};