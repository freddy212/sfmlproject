#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "CustomMath.h"
#include <iostream>
#include "Player.h"
#include "ResourceHolder.h"
#include "Textures.h"
#include "SFfont.h"
#include "Sartan.h"

#include <iostream>
class Game {

private: 
	sf::CircleShape innercirclecreation();
	void loadTextures();
	void loadFonts();
	ResourceHolder <sf::Texture, Textures::ID> rh;
	ResourceHolder <sf::Font, Fonts::ID> fh;
	float windowWidth = 800;
	float windowHeight = 640;
	sf::FloatRect windowRect;
	sf::Vector2f viewPos;
	Projectile* createProjectile(bool q, bool w, Player &c);

public:
	Game();
};
