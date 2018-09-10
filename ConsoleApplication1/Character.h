#pragma once
#include "MoveableEntity.h"
#include "Projectile.h"
class Character : public MoveableEntity {
public:
	enum HitState {
		HITSTUN,
		NOTHIT
	};
	HitState getHitState();
	void isHit(sf::Vector2f &direction);
	int getHealth();
	int getID();
	void shootProjectile(Projectile *p, sf::Vector2f &pointClicked);
	void stopAtDestination();
	void outsideBounds();
	void handleHitStun();
	
	
protected:
	float numberOfTimesToRepeatSpeedInHitstun = 8;
	float defaultMovementSpeed = 3;
	int health;
	int ID;
	Character::HitState hitstate = Character::NOTHIT;
};
