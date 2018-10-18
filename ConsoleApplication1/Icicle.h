#pragma once

#include "Projectile.h"
#include "ResourceHolder.h"
#include "Textures.h"
#include "SFML/Graphics.hpp"

class Icicle : public Projectile {
private:

	std::string icicleImageDestination = "C:/Users/frede/Desktop/Images/Icicle.png";
	sf::RectangleShape icrs;

public:

	void setBoundingShape();
	Icicle(ResourceHolder <sf::Texture, Textures::ID> &rh, int id);
};
