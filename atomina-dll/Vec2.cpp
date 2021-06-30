#include "pch.h"
#include "Vec2.h"

namespace ATMA {

	//template instances for the accceptable types. Needed to be exported for visability
	template ATMA_API class Vec2<int>;
	template ATMA_API class Vec2<float>;
	template ATMA_API class Vec2<double>;

	Vec2<int>::Vec2() : x_(0), y_(0) {}

	Vec2<float>::Vec2() : x_(0.0f), y_(0.0f) {}

	Vec2<double>::Vec2() : x_(0.0), y_(0.0) {}
	
	Vec2<int>::Vec2(const Vec2<int>& other) : x_(other.x_), y_(other.y_) {}

	Vec2<float>::Vec2(const Vec2<float>& other) : x_(other.x_), y_(other.y_) {}

	Vec2<double>::Vec2(const Vec2<double>& other) : x_(other.x_), y_(other.y_) {}

	Vec2<int>::Vec2(int x, int y) : x_(x), y_(y) {}

	Vec2<float>::Vec2(float x, float y) : x_(x), y_(y) {}

	Vec2<double>::Vec2(double x, double y) : x_(x), y_(y) {}

	const int Vec2<int>::x() const {
		return x_;
	}

	const float Vec2<float>::x() const {
		return x_;
	}

	const double Vec2<double>::x() const {
		return x_;
	}

	const int Vec2<int>::y() const{
		return y_;
	}

	const float Vec2<float>::y() const {
		return y_;
	}

	const double Vec2<double>::y() const {
		return y_;
	}

	Vec2<int> Vec2<int>::operator+(const Vec2<int>& other) {
		return Vec2<int>(this->x_ + other.x_, this->y_ + other.y_);
	}

	Vec2<float> Vec2<float>::operator+(const Vec2<float>& other) {
		return Vec2<float>(this->x_ + other.x(), this->y_ + other.y());
	}

	Vec2<double> Vec2<double>::operator+(const Vec2<double>& other) {
		return Vec2<double>(this->x_ + other.x(), this->y_ + other.y());
	}

	Vec2<int> Vec2<int>::operator-(const Vec2<int>& other) {
		return Vec2<int>(this->x_ - other.x(), this->y_ - other.y());
	}

	Vec2<float> Vec2<float>::operator-(const Vec2<float>& other) {
		return Vec2<float>(this->x_ - other.x(), this->y_ - other.y());
	}
	Vec2<double> Vec2<double>::operator-(const Vec2<double>& other) {
		return Vec2<double>(this->x_ - other.x(), this->y_ - other.y());
	}

	int Vec2<int>::operator*(const Vec2<int>& other) {
		return (int)(this->x_ * other.x_  + this->y_ * other.y_);
	}

	float Vec2<float>::operator*(const Vec2<float>& other) {
		return (float)(this->x_ * other.x_ + this->y_ * other.y_);
	}
	
	double Vec2<double>::operator*(const Vec2<double>& other) {
		return (double)(this->x_ * other.x_ + this->y_ * other.y_);
	}

	Vec2<int> Vec2<int>::operator*(const int& other) {
		return Vec2<int>(this->x_ * other, this->y_ * other);
	}

	Vec2<float> Vec2<float>::operator*(const float& other) {
		return Vec2<float>(this->x_ * other, this->y_ * other);
	}

	Vec2<double> Vec2<double>::operator*(const double& other) {
		return Vec2<double>(this->x_ * other, this->y_ * other);
	}

	Vec2<int>& Vec2<int>::operator=(const Vec2<int>& other){
		this->x_ = other.x_;
		this->y_ = other.y_;
		return *this;
	}

	Vec2<float>& Vec2<float>::operator=(const Vec2<float>& other) {
		this->x_ = other.x_;
		this->y_ = other.y_;
		return *this;
	}

	Vec2<double>& Vec2<double>::operator=(const Vec2<double>& other) {
		this->x_ = other.x_;
		this->y_ = other.y_;
		return *this;
	}

	Vec2<int>& Vec2<int>::operator=(Vec2<int>&& other) noexcept
	{
		this->x_ = other.x_;
		this->y_ = other.y_;
		return *this;
	}

	Vec2<float>& Vec2<float>::operator=(Vec2<float>&& other) noexcept
	{
		this->x_ = other.x_;
		this->y_ = other.y_;
		return *this;
	}

	Vec2<double>& Vec2<double>::operator=(Vec2<double>&& other) noexcept
	{
		this->x_ = other.x_;
		this->y_ = other.y_;
		return *this;
	}

	bool operator==(const Vec2<int>& a, const Vec2<int>& b) {
		return(a.x() == b.x() && a.y() == b.y());
	}

	bool operator==(const Vec2<float>& a, const Vec2<float>& b) {
		return(a.x() == b.x() && a.y() == b.y());
	}

	bool operator==(const Vec2<double>& a, const Vec2<double>& b) {
		return(a.x() == b.x() && a.y() == b.y());
	}

	bool operator!=(const Vec2<int>& a, const Vec2<int>& b) {
		return !(a == b);
	}

	bool operator!=(const Vec2<float>& a, const Vec2<float>& b) {
		return !(a == b);
	}

	bool operator!=(const Vec2<double>& a, const Vec2<double>& b) {
		return !(a == b);
	}



}