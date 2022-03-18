#include "CppUnitTest.h"
#include <atomina.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Random {

	TEST_CLASS(Random_Generator) {

		TEST_METHOD(Random_positive_int) {
			ATMA::RandomGenerator<int> rg;
			int value = rg(0, 10);

			Assert::IsTrue(value >= 0 && value <= 10);
		}

		TEST_METHOD(Random_negative_int) {
			ATMA::RandomGenerator<int> rg;
			int value = rg(-10, 0);

			Assert::IsTrue(value <= 0 && value >= -10);
		}


		TEST_METHOD(Random_mixed_int) {
			ATMA::RandomGenerator<int> rg;
			int value = rg(-10, 10);

			Assert::IsTrue(value >= -10 && value <= 10);
		}

		TEST_METHOD(Random_positive_float) {
			ATMA::RandomGenerator<float> rg;
			float value = rg(0.0f, 10.0f);

			Assert::IsTrue(value >= 0.0f && value <= 10.0f);
		}

		TEST_METHOD(Random_negative_float) {
			ATMA::RandomGenerator<float> rg;
			float value = rg(-10.0f, 0.0f);

			Assert::IsTrue(value <= 0.0f && value >= -10.0f);
		}


		TEST_METHOD(Random_mixed_float) {
			ATMA::RandomGenerator<float> rg;
			float value = rg(-10.0f, 10.0f);

			Assert::IsTrue(value >= -10.0f && value <= 10.0f);
		}


		TEST_METHOD(Random_positive_double) {
			ATMA::RandomGenerator<double> rg;
			double value = rg(0.0, 10.0);

			Assert::IsTrue(value >= 0.0 && value <= 10.0);
		}

		TEST_METHOD(Random_negative_double) {
			ATMA::RandomGenerator<double> rg;
			double value = rg(-10.0, 0.0);

			Assert::IsTrue(value <= 0.0 && value >= -10.0);
		}


		TEST_METHOD(Random_mixed_double) {
			ATMA::RandomGenerator<double> rg;
			double value = rg(-10.0, 10.0);

			Assert::IsTrue(value >= -10.0 && value <= 10.0);
		}

	};

}