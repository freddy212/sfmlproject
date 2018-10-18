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
	virtual void isHit(sf::Vector2f &direction);
	int getHealth();
	int getID();
	void shootProjectile(Projectile *p, sf::Vector2f pointClicked);
	void stopAtDestination();
	void outsideBounds();
	void handleHitStun();
	float getCircleRadius();
	void startMovingToPoint(sf::Vector2f pointClicked);
	
	
protected:
	float circleradius = 0;
	float numberOfTimesToRepeatSpeedInHitstun = 8;
	float defaultMovementSpeed;
	sf::Vector2f defaultMovementVector = sf::Vector2f(0, 0);
	int health;
	int ID;
	Character::HitState hitstate = Character::NOTHIT;
};
