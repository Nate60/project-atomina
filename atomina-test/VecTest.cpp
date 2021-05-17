#include "CppUnitTest.h"
#include <atomina.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Vector2 {

	TEST_CLASS(Vec2_int) {

		TEST_METHOD(add_positive_vectors) {

			ATMA::Vec2<int> v1 = ATMA::Vec2<int>(1, 3);
			ATMA::Vec2<int> v2 = ATMA::Vec2<int>(2, 4);

			bool isTrue = (v1 + v2 == ATMA::Vec2<int>(3, 7));

			Assert::IsTrue(isTrue);

		}

		TEST_METHOD(add_negative_vectors) {

			ATMA::Vec2<int> v1 = ATMA::Vec2<int>(-1, -3);
			ATMA::Vec2<int> v2 = ATMA::Vec2<int>(-2, -4);

			bool isTrue = (v1 + v2 == ATMA::Vec2<int>(-3, -7));

			Assert::IsTrue(isTrue);

		}
		
		TEST_METHOD(add_oposing_vectors) {

			ATMA::Vec2<int> v1 = ATMA::Vec2<int>(-1, -3);
			ATMA::Vec2<int> v2 = ATMA::Vec2<int>(2, 4);

			bool isTrue = (v1 + v2 == ATMA::Vec2<int>(1, 1));

			Assert::IsTrue(isTrue);

		}

		TEST_METHOD(add_mixed_vectors) {

			ATMA::Vec2<int> v1 = ATMA::Vec2<int>(-1, 3);
			ATMA::Vec2<int> v2 = ATMA::Vec2<int>(2, -4);

			bool isTrue = (v1 + v2 == ATMA::Vec2<int>(1, -1));

			Assert::IsTrue(isTrue);

		}

		TEST_METHOD(sub_positive_vectors) {

			ATMA::Vec2<int> v1 = ATMA::Vec2<int>(1, 3);
			ATMA::Vec2<int> v2 = ATMA::Vec2<int>(2, 4);

			bool isTrue = (v1 - v2 == ATMA::Vec2<int>(-1, -1));

			Assert::IsTrue(isTrue);

		}

		TEST_METHOD(sub_negative_vectors) {

			ATMA::Vec2<int> v1 = ATMA::Vec2<int>(-1, -3);
			ATMA::Vec2<int> v2 = ATMA::Vec2<int>(-2, -4);

			bool isTrue = (v1 - v2 == ATMA::Vec2<int>(1, 1));

			Assert::IsTrue(isTrue);

		}

		TEST_METHOD(sub_oposing_vectors) {

			ATMA::Vec2<int> v1 = ATMA::Vec2<int>(-1, -3);
			ATMA::Vec2<int> v2 = ATMA::Vec2<int>(2, 4);

			bool isTrue = (v1 - v2 == ATMA::Vec2<int>(-3, -7));

			Assert::IsTrue(isTrue);

		}

		TEST_METHOD(sub_mixed_vectors) {

			ATMA::Vec2<int> v1 = ATMA::Vec2<int>(-1, 3);
			ATMA::Vec2<int> v2 = ATMA::Vec2<int>(2, -4);

			bool isTrue = (v1 - v2 == ATMA::Vec2<int>(-3, 7));

			Assert::IsTrue(isTrue);

		}

		TEST_METHOD(dot_positive_vectors) {

			ATMA::Vec2<int> v1 = ATMA::Vec2<int>(1, 3);
			ATMA::Vec2<int> v2 = ATMA::Vec2<int>(2, 4);

			Assert::AreEqual(v1 * v2, 14);

		}

		TEST_METHOD(dot_negative_vectors) {

			ATMA::Vec2<int> v1 = ATMA::Vec2<int>(-1, -3);
			ATMA::Vec2<int> v2 = ATMA::Vec2<int>(-2, -4);

			Assert::AreEqual(v1 * v2, 14);

		}

		TEST_METHOD(dot_oposing_vectors) {

			ATMA::Vec2<int> v1 = ATMA::Vec2<int>(-1, -3);
			ATMA::Vec2<int> v2 = ATMA::Vec2<int>(2, 4);


			Assert::AreEqual(v1 * v2, -14);

		}

		TEST_METHOD(dot_mixed_vectors) {

			ATMA::Vec2<int> v1 = ATMA::Vec2<int>(-1, 3);
			ATMA::Vec2<int> v2 = ATMA::Vec2<int>(2, -4);

			Assert::AreEqual(v1 * v2, -14);

		}
		 
		TEST_METHOD(positive_scalar_positive_vector) {
			ATMA::Vec2<int> v1 = ATMA::Vec2<int>(1, 3);

			bool isTrue = (v1 * 2 == ATMA::Vec2<int>(2, 6));

			Assert::IsTrue(isTrue);

		}

		TEST_METHOD(positive_scalar_negative_vector) {
			ATMA::Vec2<int> v1 = ATMA::Vec2<int>(-1, -3);

			bool isTrue = (v1 * 2 == ATMA::Vec2<int>(-2, -6));

			Assert::IsTrue(isTrue);

		}

		TEST_METHOD(positive_scalar_mixed_vector) {
			ATMA::Vec2<int> v1 = ATMA::Vec2<int>(-1, 3);

			bool isTrue = (v1 * 2 == ATMA::Vec2<int>(-2, 6));

			Assert::IsTrue(isTrue);

		}

		TEST_METHOD(negative_scalar_positive_vector) {
			ATMA::Vec2<int> v1 = ATMA::Vec2<int>(1, 3);

			bool isTrue = (v1 * -2 == ATMA::Vec2<int>(-2, -6));

			Assert::IsTrue(isTrue);

		}

		TEST_METHOD(negative_scalar_negative_vector) {
			ATMA::Vec2<int> v1 = ATMA::Vec2<int>(-1, -3);

			bool isTrue = (v1 * -2 == ATMA::Vec2<int>(2, 6));

			Assert::IsTrue(isTrue);

		}

		TEST_METHOD(negative_scalar_mixed_vector) {
			ATMA::Vec2<int> v1 = ATMA::Vec2<int>(-1, 3);

			bool isTrue = (v1 * -2 == ATMA::Vec2<int>(2, -6));

			Assert::IsTrue(isTrue);

		}

	};


	TEST_CLASS(Vec2_float) {

		TEST_METHOD(add_positive_vectors) {

			ATMA::Vec2<float> v1 = ATMA::Vec2<float>(1, 3);
			ATMA::Vec2<float> v2 = ATMA::Vec2<float>(2, 4);

			bool isTrue = (v1 + v2 == ATMA::Vec2<float>(3, 7));

			Assert::IsTrue(isTrue);

		}

		TEST_METHOD(add_negative_vectors) {

			ATMA::Vec2<float> v1 = ATMA::Vec2<float>(-1, -3);
			ATMA::Vec2<float> v2 = ATMA::Vec2<float>(-2, -4);

			bool isTrue = (v1 + v2 == ATMA::Vec2<float>(-3, -7));

			Assert::IsTrue(isTrue);

		}

		TEST_METHOD(add_oposing_vectors) {

			ATMA::Vec2<float> v1 = ATMA::Vec2<float>(-1, -3);
			ATMA::Vec2<float> v2 = ATMA::Vec2<float>(2, 4);

			bool isTrue = (v1 + v2 == ATMA::Vec2<float>(1, 1));

			Assert::IsTrue(isTrue);

		}

		TEST_METHOD(add_mixed_vectors) {

			ATMA::Vec2<float> v1 = ATMA::Vec2<float>(-1, 3);
			ATMA::Vec2<float> v2 = ATMA::Vec2<float>(2, -4);

			bool isTrue = (v1 + v2 == ATMA::Vec2<float>(1, -1));

			Assert::IsTrue(isTrue);

		}

		TEST_METHOD(sub_positive_vectors) {

			ATMA::Vec2<float> v1 = ATMA::Vec2<float>(1, 3);
			ATMA::Vec2<float> v2 = ATMA::Vec2<float>(2, 4);

			bool isTrue = (v1 - v2 == ATMA::Vec2<float>(-1, -1));

			Assert::IsTrue(isTrue);

		}

		TEST_METHOD(sub_negative_vectors) {

			ATMA::Vec2<float> v1 = ATMA::Vec2<float>(-1, -3);
			ATMA::Vec2<float> v2 = ATMA::Vec2<float>(-2, -4);

			bool isTrue = (v1 - v2 == ATMA::Vec2<float>(1, 1));

			Assert::IsTrue(isTrue);

		}

		TEST_METHOD(sub_oposing_vectors) {

			ATMA::Vec2<float> v1 = ATMA::Vec2<float>(-1, -3);
			ATMA::Vec2<float> v2 = ATMA::Vec2<float>(2, 4);

			bool isTrue = (v1 - v2 == ATMA::Vec2<float>(-3, -7));

			Assert::IsTrue(isTrue);

		}

		TEST_METHOD(sub_mixed_vectors) {

			ATMA::Vec2<float> v1 = ATMA::Vec2<float>(-1, 3);
			ATMA::Vec2<float> v2 = ATMA::Vec2<float>(2, -4);

			bool isTrue = (v1 - v2 == ATMA::Vec2<float>(-3, 7));

			Assert::IsTrue(isTrue);

		}

		TEST_METHOD(dot_positive_vectors) {

			ATMA::Vec2<float> v1 = ATMA::Vec2<float>(1, 3);
			ATMA::Vec2<float> v2 = ATMA::Vec2<float>(2, 4);

			Assert::AreEqual(v1 * v2, 14.0f);

		}

		TEST_METHOD(dot_negative_vectors) {

			ATMA::Vec2<float> v1 = ATMA::Vec2<float>(-1, -3);
			ATMA::Vec2<float> v2 = ATMA::Vec2<float>(-2, -4);

			Assert::AreEqual(v1 * v2, 14.0f);

		}

		TEST_METHOD(dot_oposing_vectors) {

			ATMA::Vec2<float> v1 = ATMA::Vec2<float>(-1, -3);
			ATMA::Vec2<float> v2 = ATMA::Vec2<float>(2, 4);


			Assert::AreEqual(v1 * v2, -14.0f);

		}

		TEST_METHOD(dot_mixed_vectors) {

			ATMA::Vec2<float> v1 = ATMA::Vec2<float>(-1, 3);
			ATMA::Vec2<float> v2 = ATMA::Vec2<float>(2, -4);

			Assert::AreEqual(v1 * v2, -14.0f);

		}

		TEST_METHOD(positive_scalar_positive_vector) {
			ATMA::Vec2<float> v1 = ATMA::Vec2<float>(1, 3);

			bool isTrue = (v1 * 2) == ATMA::Vec2<float>(2, 6);

			Assert::IsTrue(isTrue);

		}

		TEST_METHOD(positive_scalar_negative_vector) {
			ATMA::Vec2<float> v1 = ATMA::Vec2<float>(-1, -3);

			bool isTrue = (v1 * 2) == ATMA::Vec2<float>(-2, -6);

			Assert::IsTrue(isTrue);

		}

		TEST_METHOD(positive_scalar_mixed_vector) {
			ATMA::Vec2<float> v1 = ATMA::Vec2<float>(-1, 3);

			bool isTrue = (v1 * 2) == ATMA::Vec2<float>(-2, 6);

			Assert::IsTrue(isTrue);

		}

		TEST_METHOD(negative_scalar_positive_vector) {
			ATMA::Vec2<float> v1 = ATMA::Vec2<float>(1, 3);

			bool isTrue = (v1 * -2) == ATMA::Vec2<float>(-2, -6);

			Assert::IsTrue(isTrue);

		}

		TEST_METHOD(negative_scalar_negative_vector) {
			ATMA::Vec2<float> v1 = ATMA::Vec2<float>(-1, -3);

			bool isTrue = (v1 * -2) == ATMA::Vec2<float>(2, 6);

			Assert::IsTrue(isTrue);

		}

		TEST_METHOD(negative_scalar_mixed_vector) {
			ATMA::Vec2<float> v1 = ATMA::Vec2<float>(-1, 3);

			bool isTrue = (v1 * -2) == ATMA::Vec2<float>(2, -6);

			Assert::IsTrue(isTrue);

		}

	};

	TEST_CLASS(Vec2_double) {

		TEST_METHOD(add_positive_vectors) {

			ATMA::Vec2<double> v1 = ATMA::Vec2<double>(1, 3);
			ATMA::Vec2<double> v2 = ATMA::Vec2<double>(2, 4);

			bool isTrue = (v1 + v2 == ATMA::Vec2<double>(3, 7));

			Assert::IsTrue(isTrue);

		}

		TEST_METHOD(add_negative_vectors) {

			ATMA::Vec2<double> v1 = ATMA::Vec2<double>(-1, -3);
			ATMA::Vec2<double> v2 = ATMA::Vec2<double>(-2, -4);

			bool isTrue = (v1 + v2 == ATMA::Vec2<double>(-3, -7));

			Assert::IsTrue(isTrue);

		}

		TEST_METHOD(add_oposing_vectors) {

			ATMA::Vec2<double> v1 = ATMA::Vec2<double>(-1, -3);
			ATMA::Vec2<double> v2 = ATMA::Vec2<double>(2, 4);

			bool isTrue = (v1 + v2 == ATMA::Vec2<double>(1, 1));

			Assert::IsTrue(isTrue);

		}

		TEST_METHOD(add_mixed_vectors) {

			ATMA::Vec2<double> v1 = ATMA::Vec2<double>(-1, 3);
			ATMA::Vec2<double> v2 = ATMA::Vec2<double>(2, -4);

			bool isTrue = (v1 + v2 == ATMA::Vec2<double>(1, -1));

			Assert::IsTrue(isTrue);

		}

		TEST_METHOD(sub_positive_vectors) {

			ATMA::Vec2<double> v1 = ATMA::Vec2<double>(1, 3);
			ATMA::Vec2<double> v2 = ATMA::Vec2<double>(2, 4);

			bool isTrue = (v1 - v2 == ATMA::Vec2<double>(-1, -1));

			Assert::IsTrue(isTrue);

		}

		TEST_METHOD(sub_negative_vectors) {

			ATMA::Vec2<double> v1 = ATMA::Vec2<double>(-1, -3);
			ATMA::Vec2<double> v2 = ATMA::Vec2<double>(-2, -4);

			bool isTrue = (v1 - v2 == ATMA::Vec2<double>(1, 1));

			Assert::IsTrue(isTrue);

		}

		TEST_METHOD(sub_oposing_vectors) {

			ATMA::Vec2<double> v1 = ATMA::Vec2<double>(-1, -3);
			ATMA::Vec2<double> v2 = ATMA::Vec2<double>(2, 4);

			bool isTrue = (v1 - v2 == ATMA::Vec2<double>(-3, -7));

			Assert::IsTrue(isTrue);

		}

		TEST_METHOD(sub_mixed_vectors) {

			ATMA::Vec2<double> v1 = ATMA::Vec2<double>(-1, 3);
			ATMA::Vec2<double> v2 = ATMA::Vec2<double>(2, -4);

			bool isTrue = (v1 - v2 == ATMA::Vec2<double>(-3, 7));

			Assert::IsTrue(isTrue);

		}

		TEST_METHOD(dot_positive_vectors) {

			ATMA::Vec2<double> v1 = ATMA::Vec2<double>(1, 3);
			ATMA::Vec2<double> v2 = ATMA::Vec2<double>(2, 4);

			Assert::AreEqual(v1 * v2, 14.0);

		}

		TEST_METHOD(dot_negative_vectors) {

			ATMA::Vec2<double> v1 = ATMA::Vec2<double>(-1, -3);
			ATMA::Vec2<double> v2 = ATMA::Vec2<double>(-2, -4);

			Assert::AreEqual(v1 * v2, 14.0);

		}

		TEST_METHOD(dot_oposing_vectors) {

			ATMA::Vec2<double> v1 = ATMA::Vec2<double>(-1, -3);
			ATMA::Vec2<double> v2 = ATMA::Vec2<double>(2, 4);


			Assert::AreEqual(v1 * v2, -14.0);

		}

		TEST_METHOD(dot_mixed_vectors) {

			ATMA::Vec2<double> v1 = ATMA::Vec2<double>(-1, 3);
			ATMA::Vec2<double> v2 = ATMA::Vec2<double>(2, -4);

			Assert::AreEqual(v1 * v2, -14.0);

		}

		TEST_METHOD(positive_scalar_positive_vector) {
			ATMA::Vec2<double> v1 = ATMA::Vec2<double>(1, 3);

			bool isTrue = (v1 * 2) == ATMA::Vec2<double>(2, 6);

			Assert::IsTrue(isTrue);

		}

		TEST_METHOD(positive_scalar_negative_vector) {
			ATMA::Vec2<double> v1 = ATMA::Vec2<double>(-1, -3);

			bool isTrue = (v1 * 2) == ATMA::Vec2<double>(-2, -6);

			Assert::IsTrue(isTrue);

		}

		TEST_METHOD(positive_scalar_mixed_vector) {
			ATMA::Vec2<double> v1 = ATMA::Vec2<double>(-1, 3);

			bool isTrue = (v1 * 2) == ATMA::Vec2<double>(-2, 6);

			Assert::IsTrue(isTrue);

		}

		TEST_METHOD(negative_scalar_positive_vector) {
			ATMA::Vec2<double> v1 = ATMA::Vec2<double>(1, 3);

			bool isTrue = (v1 * -2) == ATMA::Vec2<double>(-2, -6);

			Assert::IsTrue(isTrue);

		}

		TEST_METHOD(negative_scalar_negative_vector) {
			ATMA::Vec2<double> v1 = ATMA::Vec2<double>(-1, -3);

			bool isTrue = (v1 * -2) == ATMA::Vec2<double>(2, 6);

			Assert::IsTrue(isTrue);

		}

		TEST_METHOD(negative_scalar_mixed_vector) {
			ATMA::Vec2<double> v1 = ATMA::Vec2<double>(-1, 3);

			bool isTrue = (v1 * -2) == ATMA::Vec2<double>(2, -6);

			Assert::IsTrue(isTrue);

		}

	};

}