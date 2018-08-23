#pragma once

#include "MoveableEntity.h"
#include "Player.h"
class Ability : public MoveableEntity{
public:
	int getDamage();
	int getCooldown();
	int getOwnerId();
	
protected:
	int damage;
	double cooldown;
	int ownerID;
};
