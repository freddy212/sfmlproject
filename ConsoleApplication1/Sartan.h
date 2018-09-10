#pragma once
#include "Character.h"

class Sartan : public Character {
public: 
	void manipulateSpriteImage(sf::Sprite &sprite);
	void setBoundingShape();
	Sartan(ResourceHolder <sf::Texture, Textures::ID> &rh, int id);
private:
	float sartanCircleRadius = 20; 
};