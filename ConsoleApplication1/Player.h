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
	void isHit(sf::Vector2f &direction) override;
	int getAvailableIcicle();
	void incrementAvailableIcicle();
	void decrementAvailableIcicle();
	
private:
	void manipulateSpriteImage(sf::Sprite &sprite);
	float playerCircleRadius = 20;
	int availableIcicle = 0;
};
