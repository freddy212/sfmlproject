#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Textures.h"
#include "ResourceHolder.h"
#include "MoveableEntity.h"

class Player : public MoveableEntity{

private:
	std::string playerImageDestination = "C:/Users/frede/Desktop/Images/topdownzombie.png";
	void manipulateSpriteImage(sf::Sprite &sprite);

public:
	Player(ResourceHolder <sf::Texture,Textures::ID> &rh);
	void stopAtDestination();
};
