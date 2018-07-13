#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Textures.h"
#include "ResourceHolder.h"

class Player {

private:
	std::string playerImageDestination = "C:/Users/frede/Desktop/Images/topdownzombie.png";
	//sf::Texture playerTexture;
	sf::Sprite playerSprite;
	void manipulateSpriteImage(sf::Sprite &sprite);
	float angle = 0;
	sf::Vector2f pointTo;
	sf::Vector2f movementvector; 

public:
	Player(ResourceHolder <sf::Texture,Textures::ID> &rh);
	sf::Sprite getSprite();
	void move();
	void changeDirection(sf::Vector2f point);
	void setPosition(sf::Vector2f newpos);
};
