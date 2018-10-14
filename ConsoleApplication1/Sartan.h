#pragma once
#include "Character.h"

class Sartan : public Character {
public: 
	void act(bool dodge, std::vector<Projectile*>& activeAbilities);
	void setBoundingShape();
	Sartan(ResourceHolder <sf::Texture, Textures::ID> &rh, int id);
	void dodgeProjectile();
	void fireBarrage(std::vector<Projectile*>& activeAbilities);
	void setDodged(bool idodged);
private:
	void manipulateSpriteImage(sf::Sprite &sprite);
	float sartanCircleRadius = 20; 
	bool dodged = false;
	ResourceHolder <sf::Texture, Textures::ID> *refrh;
};