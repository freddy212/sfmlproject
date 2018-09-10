#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Textures.h"
#include "ResourceHolder.h"
#include "Character.h"

class Player : public Character{

public:

	void setBoundingShape();
	float getPlayerCircleRadius();
	Player(ResourceHolder <sf::Texture,Textures::ID> &rh, int id);


	
private:
	void manipulateSpriteImage(sf::Sprite &sprite);
	float playerCircleRadius = 20;
};
