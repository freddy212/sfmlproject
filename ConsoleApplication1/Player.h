#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Textures.h"
#include "ResourceHolder.h"
#include "MoveableEntity.h"

class Player : public MoveableEntity{

public:
	enum HitState {
		HITSTUN,
		NOTHIT
	};
	HitState getHitState();
	void handleHitStun(int currentSpeed);
	void setBoundingShape();
	float getPlayerCircleRadius();
	Player(ResourceHolder <sf::Texture,Textures::ID> &rh);
	void stopAtDestination();
	void isHit(sf::Vector2f &direction);
private:
	std::string playerImageDestination = "C:/Users/frede/Desktop/Images/topdownzombie.png";
	void manipulateSpriteImage(sf::Sprite &sprite);
	float playerCircleRadius = 20;
	float numberOfTimesToRepeatSpeedInHitstun = 3;
	float playerDefaultMovementSpeed = 3;
	Player::HitState hitstate;
};
