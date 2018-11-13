#pragma once 

#include "Projectile.h"
#include "ResourceHolder.h"
#include "Textures.h"
#include "SFML/Graphics.hpp"

class Meteor : public Projectile {
private:

	sf::RectangleShape mrs;

public:

	void setBoundingShape();
	Meteor(ResourceHolder <sf::Texture, Textures::ID> &rh, int id);
    void handleProjectileLaunch(sf::Vector2f pointClicked, sf::Vector2f characterPos) override;
};
