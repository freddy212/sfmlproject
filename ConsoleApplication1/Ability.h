#pragma once

#include "MoveableEntity.h"
#include "Player.h"
class Ability : public MoveableEntity{
public:
	int getDamage();
	int getCooldown();
	Player *getOwner();
	
protected:
	int damage;
	double cooldown;
	Player *owner;
};
