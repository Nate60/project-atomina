#include "MathUtil.h"

namespace ATMA {


	double perlin(Vec2<double> gradient[4], std::function<double (double, double, double)> interpolate, double x, double y) {

		int a0 = (int)x;
		int a1 = a0 + 1;
		int b0 = (int)y;
		int b1 = b0 + 1;

		double dx = x - a0;
		double dy = y - b0;

		double temp1, temp2, inter1, inter2;

		Vec2<double> distanceVector = Vec2<double>(dx, dy);
		temp1 = gradient[0] * distanceVector;

		distanceVector = Vec2<double>(x - a1, dy);
		temp2 = gradient[1] * distanceVector;
		inter1 = interpolate(temp1, temp2, dx);

		distanceVector = Vec2<double>(dx, y - b1);
		temp1 = gradient[2] * distanceVector;

		distanceVector = Vec2<double>(x - a1, y - b1);
		temp2 = gradient[3] * distanceVector;
		inter2 = interpolate(temp1, temp2, dx);

		return interpolate(inter1, inter2, dy);

	}


	float perlin(Vec2<float> gradient[4], std::function<float (float, float, float)> interpolate, float x, float y) {

		int a0 = (int)x;
		int a1 = a0 + 1;
		int b0 = (int)y;
		int b1 = b0 + 1;

		float dx = x - a0;
		float dy = y - b0;

		float temp1, temp2, inter1, inter2;

		Vec2<float> distanceVector = Vec2<float>(dx, dy);
		temp1 = gradient[0] * distanceVector;

		distanceVector = Vec2<float>(x - a1, dy);
		temp2 = gradient[1] * distanceVector;
		inter1 = interpolate(temp1, temp2, dx);

		distanceVector = Vec2<float>(dx, y - b1);
		temp1 = gradient[2] * distanceVector;

		distanceVector = Vec2<float>(x - a1, y - b1);
		temp2 = gradient[3] * distanceVector;
		inter2 = interpolate(temp1, temp2, dx);

		return interpolate(inter1, inter2, dy);

	}

}