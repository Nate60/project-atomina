#pragma once
#include "AtominaException.h"


namespace ATMA {


	/*
	* Linear Interpolation between two values, with a given delta
	* @param v0 Starting Boundary of interpolation
	* @param v1 Ending Boundary of interpolation'
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
	* @param v1 Ending Boundary of interpolation'
	* @param t The delta as a ratio of (v-v0)/v1-v0, must be between 0 and 1
	*/
	inline double lerp(double v0, double v1, double t) {
		if (t > 1.0 || t < 0.0)
			throw InvalidParameterException("delta must be between 0.0 and 1.0");
		return (1 - t) * v0 + t * v1;
	}

}