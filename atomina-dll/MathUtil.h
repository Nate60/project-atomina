#pragma once
#include "AtominaException.h"
#include "Vec2.h"
#include <functional>

namespace ATMA {


	/*
	* Linear Interpolation between two values, with a given delta
	* @param v0 Starting Boundary of interpolation
	* @param v1 Ending Boundary of interpolation
	* @param t The delta as a ratio of (v-v0)/v1-v0, must be between 0 and 1
	*/
	inline float lerp(float v0, float v1, float t) {
		if (t > 1.0f || t < 0.0f)
			throw InvalidParameterException("delta must be between 0.0f and 1.0f");
		return (1 - t) * v0 + t * v1;
	}


	/*
	* Overloaded Linear Interpolation between two values, with a given delta
	* @param v0 Starting Boundary of interpolation
	* @param v1 Ending Boundary of interpolation
	* @param t The delta as a ratio of (v-v0)/v1-v0, must be between 0 and 1
	*/
	inline double lerp(double v0, double v1, double t) {
		if (t > 1.0 || t < 0.0)
			throw InvalidParameterException("delta must be between 0.0 and 1.0");
		return (1 - t) * v0 + t * v1;
	}


	/*
	* Cubic interpolation between two values with a given delta, used for smoother stepping
	* @param v0 Starting Boundary of interpolation
	* @param v1 Ending Boundary of interpolation
	* @param t The delta as a ratio of (v-v0)/v1-v0, must be between 0 and 1
	*/
	float cubeTerp(float a0, float a1, float w) {
		if (w > 1.0 || w < 0.0)
			throw InvalidParameterException("delta must be between 0.0 and 1.0");
		return (a1 - a0) * (3.0f - w * 2.0f) * w * w + a0;
	}

	/*
	* Overloaded Cubic interpolation between two floats with a given delta, used for smoother stepping
	* @param v0 Starting Boundary of interpolation
	* @param v1 Ending Boundary of interpolation
	* @param t The delta as a ratio of (v-v0)/v1-v0, must be between 0 and 1
	*/
	double cubeTerp(double a0, double a1, double w) {
		if (w > 1.0 || w < 0.0)
			throw InvalidParameterException("delta must be between 0.0 and 1.0");
		return (a1 - a0) * (3.0 - w * 2.0) * w * w + a0;
	}



	//function headers need to be exported
	ATMA_API double perlin(Vec2<double> gradient[4], std::function<double (double, double, double) > interpolate, double x, double y);


	ATMA_API float perlin(Vec2<float> gradient[4], std::function<float (float, float, float)> interpolate, float x, float y);

}