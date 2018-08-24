#pragma once

#include <math.h>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
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

	bool static intersects(sf::Sprite first, sf::Sprite second) {
		sf::FloatRect abilityrect = second.getGlobalBounds();
		sf::FloatRect manrect = first.getGlobalBounds();
		return sf::FloatRect(manrect.left,manrect.top,manrect.width / 2, manrect.height / 2).intersects(sf::FloatRect(abilityrect.left,abilityrect.top,abilityrect.width / 2, abilityrect.height / 2));
	}

	
	bool static circleIntersectionWithRectangle(sf::Vector2f circlepos, float circleradius, sf::FloatRect rect){

		float circleDistancex = abs(circlepos.x - rect.left);
		float circleDistancey = abs(circlepos.y - rect.top);

		if (circleDistancex > (rect.width / 2 + circleradius)) { return false; }
		if (circleDistancey > (rect.height / 2 + circleradius)) { return false; }

		if (circleDistancex <= (rect.width / 2)) { return true; }
		if (circleDistancey <= (rect.height / 2)) { return true; }

		auto cornerDistance_sq = pow(circleDistancex - rect.width / 2,2) +
			pow(circleDistancey - rect.height / 2,2);

		return (cornerDistance_sq <= pow(circleradius,2));
	}

	bool static circleIntersectionWithRotatedRectangle(sf::Vector2f circlepos, float circleradius, sf::FloatRect rect, float rotation) {
		int circlexoffset = 10;
		float rectCenterX = rect.left;
		 float rectCenterY = rect.top;

		float rectX = rectCenterX - rect.width / 2;
		float rectY = rectCenterY - rect.height / 2;

		float rectReferenceX = rectX;
		float rectReferenceY = rectY;

		// Rotate circle's center point back
		float unrotatedCircleX = cos(rotation) * (circlepos.x - rectCenterX) - sin(rotation) * (circlepos.y - rectCenterY) + rectCenterX;
		float unrotatedCircleY = sin(rotation) * (circlepos.x - rectCenterX) + cos(rotation) * (circlepos.y - rectCenterY) + rectCenterY;

		// Closest point in the rectangle to the center of circle rotated backwards(unrotated)
		float closestX, closestY;

		// Find the unrotated closest x point from center of unrotated circle
		if (unrotatedCircleX < rectReferenceX) {
			closestX = rectReferenceX;
		}
		else if (unrotatedCircleX > rectReferenceX + rect.width) {
			closestX = rectReferenceX + rect.width;
		}
		else {
			closestX = unrotatedCircleX;
		}

		// Find the unrotated closest y point from center of unrotated circle
		if (unrotatedCircleY < rectReferenceY) {
			closestY = rectReferenceY;
		}
		else if (unrotatedCircleY > rectReferenceY + rect.height) {
			closestY = rectReferenceY + rect.height;
		}
		else {
			closestY = unrotatedCircleY;
		}

		// Determine collision
		bool collision = false;
		float distanceBetweenObjects = distance(sf::Vector2f(unrotatedCircleX + circlexoffset, unrotatedCircleY), 
			sf::Vector2f(closestX, closestY));

		if (distanceBetweenObjects < circleradius) {
			collision = true;
		}
		else {
			collision = false;
		}

		return collision;
	}

private: CustomMath() {};

};