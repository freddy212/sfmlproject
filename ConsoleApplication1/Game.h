#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "CustomMath.h"
#include <iostream>
#include "Player.h"
#include "ResourceHolder.h"
#include "Textures.h"

#include <iostream>
class Game {

private: 
	sf::CircleShape innercirclecreation();
	void loadTextures();
	ResourceHolder <sf::Texture, Textures::ID> rh;
	int windowWidth = 800;
	int windowHeight = 640;
	sf::FloatRect windowRect;
	sf::Vector2f viewPos;

public:
	Game();
};
