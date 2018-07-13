#pragma once

#include <math.h>
#include <SFML/Graphics.hpp>
#define M_PI 3.1415926535897
class CustomMath{
public:

	float static distance(const sf::Vector2f &left, const sf::Vector2f &right) {
		float csq = pow((left.x - right.x), 2) + pow((left.y - right.y), 2);
		return sqrt(csq);
	}
	sf::Vector2f static normalizeUnitVector(const sf::Vector2f &left, const sf::Vector2f &right) {
		float unitdirection = sqrt(pow(right.x - left.x, 2) + pow(right.y - left.y, 2));
		return sf::Vector2f((right.x - left.x) / unitdirection, (right.y - left.y) / unitdirection);
	}

	float static getAngleBetweenPointsInDegrees(const sf::Vector2f &left, const sf::Vector2f &right) {
		float angle = atan2(right.y - left.y, right.x - left.x);
		return angle * 180 / M_PI;
	}

private: CustomMath() {};

};