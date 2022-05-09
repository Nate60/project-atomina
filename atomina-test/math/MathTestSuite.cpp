#include "MathTestSuite.hpp"

TYPED_TEST_SUITE(InterpolationTestFixture, InterpolationTestTypes);
TYPED_TEST_SUITE(PerlinTestFixture, PerlinTestTypes);
TYPED_TEST(InterpolationTestFixture, LinearInterpolation){

    std::array<std::array<int,10>,15> array;

    auto f = ATMA::lerp<TypeParam,float>;
    this->interpolateTest(f);
};

TYPED_TEST(InterpolationTestFixture, CubicInterpolation){


    auto f = ATMA::cubeTerp<TypeParam,float>;
    this->interpolateTest(f);
};

TYPED_TEST(PerlinTestFixture, PerlinNoiseWithLerp){

    auto f = ATMA::lerp<TypeParam,float>;
    TypeParam exp = -0.5;
    this-> perlinTest(f, exp);

};

TYPED_TEST(PerlinTestFixture, PerlinNoiseWithCubeTerp){

    auto f = ATMA::cubeTerp<TypeParam,float>;
    TypeParam exp = -0.5;
    this-> perlinTest(f, exp);

};

using IntPerlinTestFixture = PerlinTestFixture<int>;

TEST_F(IntPerlinTestFixture, PerlinNoiseWithLerpInt){
    auto f = ATMA::lerp<int,float>;
    int exp = 0;
    this-> perlinTest(f, exp);
}

TEST_F(IntPerlinTestFixture, PerlinNoiseWithCubeTerpInt){
    auto f = ATMA::cubeTerp<int,float>;
    int exp = 0;
    this-> perlinTest(f, exp);
}

