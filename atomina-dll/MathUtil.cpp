#include "pch.h"
#include "MathUtil.h"

namespace ATMA {


	double perlin(sf::Vector2<double> gradient[4], std::function<double (double, double, double)> interpolate, double l_x, double l_y) {

		int a0 = (int)l_x;
		int a1 = a0 + 1;
		int b0 = (int)l_y;
		int b1 = b0 + 1;

		double dx = l_x - a0;
		double dy = l_y - b0;

		double temp1, temp2, inter1, inter2;

		sf::Vector2<double> distanceVector = sf::Vector2<double>(dx, dy);
		temp1 = gradient[0] * distanceVector;

		distanceVector = sf::Vector2<double>(l_x - a1, dy);
		temp2 = gradient[1] * distanceVector;
		inter1 = interpolate(temp1, temp2, dx);

		distanceVector = sf::Vector2<double>(dx, l_y - b1);
		temp1 = gradient[2] * distanceVector;

		distanceVector = sf::Vector2<double>(l_x - a1, l_y - b1);
		temp2 = gradient[3] * distanceVector;
		inter2 = interpolate(temp1, temp2, dx);

		return interpolate(inter1, inter2, dy);

	}


	float perlin(sf::Vector2f gradient[4], std::function<float (float, float, float)> interpolate, float l_x, float l_y) {

		int a0 = (int)l_x;
		int a1 = a0 + 1;
		int b0 = (int)l_y;
		int b1 = b0 + 1;

		float dx = l_x - a0;
		float dy = l_y - b0;

		float temp1, temp2, inter1, inter2;

		sf::Vector2f distanceVector = sf::Vector2f(dx, dy);
		temp1 = gradient[0] * distanceVector;

		distanceVector = sf::Vector2f(l_x - a1, dy);
		temp2 = gradient[1] * distanceVector;
		inter1 = interpolate(temp1, temp2, dx);

		distanceVector = sf::Vector2f(dx, l_y - b1);
		temp1 = gradient[2] * distanceVector;

		distanceVector = sf::Vector2f(l_x - a1, l_y - b1);
		temp2 = gradient[3] * distanceVector;
		inter2 = interpolate(temp1, temp2, dx);

		return interpolate(inter1, inter2, dy);

	}

}