#pragma once
#include "api.h"

namespace ATMA {

	/*
	* data structure for a pair of numbers that represent the x and y 
	* of a vector
	*/
	template <class T> 
	class ATMA_API Vec2 {
	private:
		T x_;
		T y_;

	public:

		Vec2();
		Vec2(const Vec2<T>& other);
		Vec2(T x, T y);
		~Vec2() {
		}

		const T x() const;
		const T y() const;

		//addition
		Vec2<T> operator+(const Vec2& other);

		//subtraction
		Vec2<T> operator-(const Vec2& other);

		//dot product
		T operator*(const Vec2& other);

		//factor multipication
		Vec2<T> operator*(const T& other);

		//copy assignment
		Vec2<T>& operator=(const Vec2& other);

		//move assignment
		Vec2<T>& operator=(Vec2<T>&& other) noexcept;

		//friend functions need be exports since they are not actually part of the class
		friend ATMA_API bool operator==(const Vec2<T>& a, const Vec2<T>& b);

		friend ATMA_API bool operator!=(const Vec2<T>& a, const Vec2<T>& b);

	};



}