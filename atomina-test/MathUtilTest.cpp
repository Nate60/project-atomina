#include "CppUnitTest.h"
#include <functional>
#include <atomina.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MathUtils
{

	void lerpExec() throw() {
		ATMA::lerp(0.0f, 0.0f, 2.0f);
	}

	TEST_CLASS(LinearInterpolation)
	{
	public:
		
		//--FLOAT--//

		TEST_METHOD(start_zero_point_float)
		{
			Assert::AreEqual(ATMA::lerp(0.0f, 0.0f, 0.0f), 0.0f);
		}

		TEST_METHOD(mid_zero_point_float)
		{
			Assert::AreEqual(ATMA::lerp(0.0f, 0.0f, 0.5f), 0.0f);
		}

		TEST_METHOD(end_zero_point_float)
		{
			Assert::AreEqual(ATMA::lerp(0.0f, 0.0f, 1.0f), 0.0f);
		}

		TEST_METHOD(end_point_float)
		{
			Assert::AreEqual(ATMA::lerp(0.0f, 2.0f, 1.0f), 2.0f);
		}

		TEST_METHOD(mid_point_float)
		{
			Assert::AreEqual(ATMA::lerp(0.0f, 2.0f, 0.5f), 1.0f);
		}

		TEST_METHOD(offset_start_point_float)
		{
			Assert::AreEqual(ATMA::lerp(1.0f, 1.0f, 0.0f), 1.0f);
		}

		TEST_METHOD(offset_end_point_float)
		{
			Assert::AreEqual(ATMA::lerp(1.0f, 2.0f, 1.0f), 2.0f);
		}

		TEST_METHOD(offset_mid_point_float)
		{
			Assert::AreEqual(ATMA::lerp(1.0f, 2.0f, 0.5f), 1.5f);
		}

		TEST_METHOD(neg_offset_start_point_float)
		{
			Assert::AreEqual(ATMA::lerp(-1.0f, 1.0f, 0.0f), -1.0f);
		}

		TEST_METHOD(neg_offset_end_point_float)
		{
			Assert::AreEqual(ATMA::lerp(-1.0f, 2.0f, 1.0f), 2.0f);
		}

		TEST_METHOD(neg_offset_mid_point_float)
		{
			Assert::AreEqual(ATMA::lerp(-1.0f, 2.0f, 0.5f), 0.5f);
		}

		TEST_METHOD(extra_point_float)
		{
			auto func = [] { ATMA::lerp(0.0f, 0.0f, 2.0f); };
			Assert::ExpectException<ATMA::InvalidParameterException>(func);
		}

		TEST_METHOD(neg_extra_point_float)
		{
			auto func = [] { ATMA::lerp(0.0f, 0.0f, -1.0f); };
			Assert::ExpectException<ATMA::InvalidParameterException>(func);
		}


		//--DOUBLE--//

		TEST_METHOD(start_zero_point_double)
		{
			Assert::AreEqual(ATMA::lerp(0.0, 0.0, 0.0), 0.0);
		}

		TEST_METHOD(mid_zero_point_double)
		{
			Assert::AreEqual(ATMA::lerp(0.0, 0.0, 0.5), 0.0);
		}

		TEST_METHOD(end_zero_point_double)
		{
			Assert::AreEqual(ATMA::lerp(0.0, 0.0, 1.0), 0.0);
		}

		TEST_METHOD(end_point_double)
		{
			Assert::AreEqual(ATMA::lerp(0.0, 2.0, 1.0), 2.0);
		}

		TEST_METHOD(mid_point_double)
		{
			Assert::AreEqual(ATMA::lerp(0.0, 2.0, 0.5), 1.0);
		}

		TEST_METHOD(offset_start_point_double)
		{
			Assert::AreEqual(ATMA::lerp(1.0, 1.0, 0.0), 1.0);
		}

		TEST_METHOD(offset_end_point_double)
		{
			Assert::AreEqual(ATMA::lerp(1.0f, 2.0f, 1.0f), 2.0f);
		}

		TEST_METHOD(offset_mid_point_double)
		{
			Assert::AreEqual(ATMA::lerp(1.0, 2.0, 0.5), 1.5);
		}

		TEST_METHOD(neg_offset_start_point_double)
		{
			Assert::AreEqual(ATMA::lerp(-1.0, 1.0, 0.0), -1.0);
		}

		TEST_METHOD(neg_offset_end_point_double)
		{
			Assert::AreEqual(ATMA::lerp(-1.0, 2.0, 1.0), 2.0);
		}

		TEST_METHOD(neg_offset_mid_point_double)
		{
			Assert::AreEqual(ATMA::lerp(-1.0, 2.0, 0.5), 0.5);
		}

		TEST_METHOD(extra_point_double)
		{
			auto func = [] { ATMA::lerp(0.0, 0.0, 2.0); };
			Assert::ExpectException<ATMA::InvalidParameterException>(func);
		}

		TEST_METHOD(neg_extra_point_double)
		{
			auto func = [] { ATMA::lerp(0.0, 0.0, -1.0); };
			Assert::ExpectException<ATMA::InvalidParameterException>(func);
		}

	};

	TEST_CLASS(CubicInterpolation){
	public:

		//--FLOAT--//

		TEST_METHOD(start_zero_point_float)
		{
			Assert::AreEqual(ATMA::cubeTerp(0.0f, 0.0f, 0.0f), 0.0f);
		}

		TEST_METHOD(mid_zero_point_float)
		{
			Assert::AreEqual(ATMA::cubeTerp(0.0f, 0.0f, 0.5f), 0.0f);
		}

		TEST_METHOD(end_zero_point_float)
		{
			Assert::AreEqual(ATMA::cubeTerp(0.0f, 0.0f, 1.0f), 0.0f);
		}

		TEST_METHOD(end_point_float)
		{
			Assert::AreEqual(ATMA::cubeTerp(0.0f, 2.0f, 1.0f), 2.0f);
		}

		TEST_METHOD(mid_point_float)
		{
			Assert::AreEqual(ATMA::cubeTerp(0.0f, 2.0f, 0.5f), 1.0f);
		}

		TEST_METHOD(offset_start_point_float)
		{
			Assert::AreEqual(ATMA::cubeTerp(1.0f, 1.0f, 0.0f), 1.0f);
		}

		TEST_METHOD(offset_end_point_float)
		{
			Assert::AreEqual(ATMA::cubeTerp(1.0f, 2.0f, 1.0f), 2.0f);
		}

		TEST_METHOD(offset_mid_point_float)
		{
			Assert::AreEqual(ATMA::cubeTerp(1.0f, 2.0f, 0.5f), 1.5f);
		}

		TEST_METHOD(neg_offset_start_point_float)
		{
			Assert::AreEqual(ATMA::cubeTerp(-1.0f, 1.0f, 0.0f), -1.0f);
		}

		TEST_METHOD(neg_offset_end_point_float)
		{
			Assert::AreEqual(ATMA::cubeTerp(-1.0f, 2.0f, 1.0f), 2.0f);
		}

		TEST_METHOD(neg_offset_mid_point_float)
		{
			Assert::AreEqual(ATMA::cubeTerp(-1.0f, 2.0f, 0.5f), 0.5f);
		}

		TEST_METHOD(extra_point_float)
		{
			auto func = [] { ATMA::cubeTerp(0.0f, 0.0f, 2.0f); };
			Assert::ExpectException<ATMA::InvalidParameterException>(func);
		}

		TEST_METHOD(neg_extra_point_float)
		{
			auto func = [] { ATMA::cubeTerp(0.0f, 0.0f, -1.0f); };
			Assert::ExpectException<ATMA::InvalidParameterException>(func);
		}


		//--DOUBLE--//

		TEST_METHOD(start_zero_point_double)
		{
			Assert::AreEqual(ATMA::cubeTerp(0.0, 0.0, 0.0), 0.0);
		}

		TEST_METHOD(mid_zero_point_double)
		{
			Assert::AreEqual(ATMA::cubeTerp(0.0, 0.0, 0.5), 0.0);
		}

		TEST_METHOD(end_zero_point_double)
		{
			Assert::AreEqual(ATMA::cubeTerp(0.0, 0.0, 1.0), 0.0);
		}

		TEST_METHOD(end_point_double)
		{
			Assert::AreEqual(ATMA::cubeTerp(0.0, 2.0, 1.0), 2.0);
		}

		TEST_METHOD(mid_point_double)
		{
			Assert::AreEqual(ATMA::cubeTerp(0.0, 2.0, 0.5), 1.0);
		}

		TEST_METHOD(offset_start_point_double)
		{
			Assert::AreEqual(ATMA::cubeTerp(1.0, 1.0, 0.0), 1.0);
		}

		TEST_METHOD(offset_end_point_double)
		{
			Assert::AreEqual(ATMA::cubeTerp(1.0f, 2.0f, 1.0f), 2.0f);
		}

		TEST_METHOD(offset_mid_point_double)
		{
			Assert::AreEqual(ATMA::cubeTerp(1.0, 2.0, 0.5), 1.5);
		}

		TEST_METHOD(neg_offset_start_point_double)
		{
			Assert::AreEqual(ATMA::cubeTerp(-1.0, 1.0, 0.0), -1.0);
		}

		TEST_METHOD(neg_offset_end_point_double)
		{
			Assert::AreEqual(ATMA::cubeTerp(-1.0, 2.0, 1.0), 2.0);
		}

		TEST_METHOD(neg_offset_mid_point_double)
		{
			Assert::AreEqual(ATMA::cubeTerp(-1.0, 2.0, 0.5), 0.5);
		}

		TEST_METHOD(extra_point_double)
		{
			auto func = [] { ATMA::cubeTerp(0.0, 0.0, 2.0); };
			Assert::ExpectException<ATMA::InvalidParameterException>(func);
		}

		TEST_METHOD(neg_extra_point_double)
		{
			auto func = [] { ATMA::cubeTerp(0.0, 0.0, -1.0); };
			Assert::ExpectException<ATMA::InvalidParameterException>(func);
		}

	};

	TEST_CLASS(PerlinNose) {
	public:

		TEST_METHOD(zero_magnitude_gradient_origin) {
			sf::Vector2<double> v[4] = { 
				sf::Vector2<double>(0, 0),
				sf::Vector2<double>(0, 0),
				sf::Vector2<double>(0, 0),
				sf::Vector2<double>(0, 0)
			};
			auto func = [](double a, double b, double c) { return ATMA::lerp(a, b, c); };
			Assert::AreEqual(ATMA::perlin(v, func , 0, 0), 0.0);

		}
		
		TEST_METHOD(parallel_equal_magnitude_gradient_origin) {
			sf::Vector2<double> v[4] = {
				sf::Vector2<double>(1, 1),
				sf::Vector2<double>(1, 1),
				sf::Vector2<double>(1, 1),
				sf::Vector2<double>(1, 1)
			};
			auto func = [](double a, double b, double c) { return ATMA::lerp(a, b, c); };
			Assert::AreEqual(ATMA::perlin(v, func, 0, 0), 0.0);

		}

		TEST_METHOD(spread_equal_magnitude_gradient_origin) {
			sf::Vector2<double> v[4] = {
				sf::Vector2<double>(-1, 1),
				sf::Vector2<double>(1, 1),
				sf::Vector2<double>(-1, -1),
				sf::Vector2<double>(1, -1)
			};
			auto func = [](double a, double b, double c) { return ATMA::lerp(a, b, c); };
			Assert::AreEqual(ATMA::perlin(v, func, 0, 0), 0.0);

		}

		TEST_METHOD(zero_magnitude_gradient_center) {
			sf::Vector2<double> v[4] = {
				sf::Vector2<double>(0, 0),
				sf::Vector2<double>(0, 0),
				sf::Vector2<double>(0, 0),
				sf::Vector2<double>(0, 0)
			};
			auto func = [](double a, double b, double c) { return ATMA::lerp(a, b, c); };
			Assert::AreEqual(ATMA::perlin(v, func, 0.5, 0.5), 0.0);

		}

		TEST_METHOD(parallel_equal_magnitude_gradient_center) {
			sf::Vector2<double> v[4] = {
				sf::Vector2<double>(1, 1),
				sf::Vector2<double>(1, 1),
				sf::Vector2<double>(1, 1),
				sf::Vector2<double>(1, 1)
			};
			auto func = [](double a, double b, double c) { return ATMA::lerp(a, b, c); };
			Assert::AreEqual(ATMA::perlin(v, func, 0.5, 0.5), 0.0);

		}

		TEST_METHOD(spread_equal_magnitude_gradient_center) {
			sf::Vector2<double> v[4] = {
				sf::Vector2<double>(-1, 1),
				sf::Vector2<double>(1, 1),
				sf::Vector2<double>(-1, -1),
				sf::Vector2<double>(1, -1)
			};
			auto func = [](double a, double b, double c) { return ATMA::lerp(a, b, c); };
			Assert::AreEqual(ATMA::perlin(v, func, 0.5, 0.5), 0.0);

		}

		TEST_METHOD(spread_unequal_magnitude_gradient_center) {
			sf::Vector2<double> v[4] = {
				sf::Vector2<double>(-2, 1),
				sf::Vector2<double>(10, 8),
				sf::Vector2<double>(-1, -3),
				sf::Vector2<double>(10, -1)
			};
			auto func = [](double a, double b, double c) { return ATMA::lerp(a, b, c); };
			Assert::AreEqual(ATMA::perlin(v, func, 0.5, 0.5), -1.25);

		}

	};
}
