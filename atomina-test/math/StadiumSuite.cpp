#include "StadiumSuite.hpp"

TYPED_TEST_SUITE(StadiumTestFixture, StadiumTestTypes);
TYPED_TEST_SUITE(StadiumCollisionTestFixture, StadiumCollideTestTypes);

/**
 * Stadiums should be considered equal when all their parameters are equal
 * in value
*/
TYPED_TEST(StadiumTestFixture, StadiumEqualTest)
{
    ATMA::Stadium<TypeParam> a{
        {0, 0},
        {1, 1},
        1
    };
    ATMA::Stadium<TypeParam> b{
        {0, 0},
        {1, 1},
        1
    };
    EXPECT_TRUE(a == b);
};

/**
 * Stadiums should be considered not equal if even on of their parameters are not
 * equal in value
*/
TYPED_TEST(StadiumTestFixture, StadiumNotEqualTest)
{
    ATMA::Stadium<TypeParam> a{
        {0, 0},
        {1, 1},
        2
    };
    ATMA::Stadium<TypeParam> b{
        {0, 0},
        {1, 1},
        1
    };
    EXPECT_FALSE(a == b);
    a = {
        {1, 0},
        {1, 1},
        2
    };
    b = {
        {0, 0},
        {1, 1},
        2
    };
    EXPECT_FALSE(a == b);
};

/**
 * When a Stadiums base is moved, only the coordinates of its
 * two defining points should be move. Additionally the rotation
 * and distance between its two defining points should be preserved
*/
TYPED_TEST(StadiumTestFixture, StadiumMoveTest)
{
    ATMA::Stadium<TypeParam> a{
        {0, 1},
        {0, 2},
        1
    };
    ATMA::Stadium<TypeParam> b{
        {2, 1},
        {2, 2},
        1
    };
    a.setBase({2, 0});
    EXPECT_TRUE(a == b);
}

/**
 * The base of a stadium should be defined as the point along its prinicipal axis (
 * the line the goes through the center of both of its semicircle caps) that touches the outer point of
 * the semi-circle defined by the Stadium's point A and its radius R
*/
TYPED_TEST(StadiumTestFixture, StadiumGetBaseTest)
{
    ATMA::Stadium<TypeParam> a{
        {0, 1},
        {0, 2},
        1
    };
    ATMA::Vec2<TypeParam> exp{0, 0};
    ATMA::Vec2<TypeParam> result = a.getBase();
    EXPECT_TRUE(exp == result);
}

/**
 * The rotation of a stadium be about its base, and preserve its 
 * dimensions
*/
TYPED_TEST(StadiumTestFixture, StadiumRotateTest)
{
    ATMA::Stadium<TypeParam> a{
        {2, 2},
        {2, 3},
        1
    };
    ATMA::Stadium<TypeParam> b{
        {3, 1},
        {4, 1},
        1
    };
    a.setRotation(-90);
    EXPECT_TRUE(a == b);
}

/**
 * The rotation of a stadium is defined by the angle of its principal axis and the 
 * x-axis
*/
TYPED_TEST(StadiumTestFixture, StadiumGetRotationTest)
{
    ATMA::Stadium<TypeParam> a{
        {3, 3},
        {3, 2},
        1
    };
    TypeParam exp = -90;
    TypeParam result = a.getRotation();
    EXPECT_EQ(exp, result);
}

/**
 * Stadiums that do not intersect should not be considered as collided
*/
TYPED_TEST(StadiumCollisionTestFixture, CollideTestNoCollide)
{
    ATMA::Stadium<TypeParam> a{
        {0, 0},
        {1, 1},
        1
    };
    ATMA::Stadium<TypeParam> b{
        {3, 0},
        {3, 1},
        1
    };
    this->collideTest(a, b, false);
};

/**
 * Stadiums that intersect each other should be considered as collided
 * and the collision function should return the penetration vector
*/
TYPED_TEST(StadiumCollisionTestFixture, CollideTestCollide)
{
    ATMA::Stadium<TypeParam> a{
        {0, 0},
        {0, 1},
        2
    };
    ATMA::Stadium<TypeParam> b{
        {1, 0},
        {1, 1},
        2
    };
    this->collideTest(a, b, true);
}

/**
 * If a stadium is fully enclosed in another it is still considered to
 * be colliding
*/
TYPED_TEST(StadiumCollisionTestFixture, CollidTestFullEnclosure)
{
    ATMA::Stadium<TypeParam> a{
        {0, 0},
        {1, 1},
        1
    };
    ATMA::Stadium<TypeParam> b{
        {0, 0},
        {1, 1},
        1
    };
    this->collideTest(a, b, true, std::make_optional<ATMA::Vec2<TypeParam>>(0, 0));
};

/**
 * If a stadium is fully enclosed in another it is still considered to
 * be colliding, even if the stadium is larger
*/
TYPED_TEST(StadiumCollisionTestFixture, CollidTestFullOverlap)
{
    ATMA::Stadium<TypeParam> a{
        {0, 0},
        {1, 1},
        1
    };
    ATMA::Stadium<TypeParam> b{
        {-1, -1},
        { 1,  1},
        2
    };
    this->collideTest(a, b, true, std::make_optional<ATMA::Vec2<TypeParam>>(0,0));
};

/**
 * Collision with a stadium should still work even if the stadium is also a circle
*/
TYPED_TEST(StadiumCollisionTestFixture, CollideTestWithCircle)
{

    ATMA::Stadium<TypeParam> a{
        {1, 2},
        {1, 2},
        1
    };
    ATMA::Stadium<TypeParam> b{
        {-1, -1},
        { 1,  1},
        2
    };
    this->collideTest(a, b, true);
}
