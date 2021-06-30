#pragma once
#include "AtominaException.h"

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
	inline float cubeTerp(float a0, float a1, float w) {
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
	inline double cubeTerp(double a0, double a1, double w) {
		if (w > 1.0 || w < 0.0)
			throw InvalidParameterException("delta must be between 0.0 and 1.0");
		return (a1 - a0) * (3.0 - w * 2.0) * w * w + a0;
	}



	//function headers need to be exported

	/*
	* Used to generate perlin noise at a specific location on a gradient
	* @param gradient: Array of 4 directional vectors that define the gradient around the point
	* @param interpolate: interpolation function to interpolate values in the gradient
	* @param l_x: x coordinate point to get the noise at
	* @param l_y: y coordinate point to get the noise at
	*/
	ATMA_API double perlin(sf::Vector2<double> gradient[4], std::function<double (double, double, double) > interpolate, double l_x, double l_y);

	/*
	* Used to generate perlin noise at a specific location on a gradient using floats
	* @param gradient: Array of 4 directional vectors that define the gradient around the point
	* @param interpolate: interpolation function to interpolate values in the gradient
	* @param l_x: x coordinate point to get the noise at
	* @param l_y: y coordinate point to get the noise at
	*/
	ATMA_API float perlin(sf::Vector2f gradient[4], std::function<float (float, float, float)> interpolate, float l_x, float l_y);

	//inline dot product for vectors

#define VEC_DOT(vec_size,vec_type) operator * (sf::Vector##vec_size##vec_type a, sf::Vector##vec_size##vec_type b) { return a.x * b.x + a.y * b.y;}

	inline double VEC_DOT(2, <double>)

	inline float VEC_DOT(2, f)
		
	inline int VEC_DOT(2, i)

}
