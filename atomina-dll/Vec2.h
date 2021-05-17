#pragma once
#include "api.h"
#include <functional>

namespace ATMA {
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
		const Vec2<T> operator+(const Vec2& other);

		//subtraction
		const Vec2<T> operator-(const Vec2& other);

		//dot product
		T operator*(const Vec2& other);

		//factor multipication
		const Vec2<T> operator*(const T& other);

		//copy assignment
		Vec2<T>& operator=(const Vec2& other);

		//move assignment
		Vec2<T>& operator=(Vec2<T>&& other) noexcept;

	};



}