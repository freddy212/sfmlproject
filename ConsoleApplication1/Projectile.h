#pragma once

#include "MoveableEntity.h"
class Projectile : public MoveableEntity{
public:
	int getDamage();
	float getCooldown();
	int getOwnerID();
    virtual void handleProjectileLaunch(sf::Vector2f pointClicked, sf::Vector2f characterPos);
	bool getReadyToShoot();
	
protected:
	int damage;
	bool isReadyToShoot = true;
	float cooldown;
	int ownerID;
};
