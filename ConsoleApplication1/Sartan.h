#pragma once
#include "Character.h"

class Sartan : public Character {
public: 
	void act(std::vector<Projectile*>& activeAbilities);
	void setBoundingShape();
	Sartan(ResourceHolder <sf::Texture, Textures::ID> &rh, int id);
	void dodgeProjectile();
	void fireBarrage(std::vector<Projectile*>& activeAbilities);
	void setDodged(bool idodged);
	bool getDodged();
	void isHit(sf::Vector2f &direction) override;
private:
	void manipulateSpriteImage(sf::Sprite &sprite);
	void moveToCenter();
	float sartanCircleRadius = 20; 
	bool dodged = false;
	ResourceHolder <sf::Texture, Textures::ID> *refrh;
};