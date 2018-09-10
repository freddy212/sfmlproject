#pragma once

#include "MoveableEntity.h"
class Projectile : public MoveableEntity{
public:
	int getDamage();
	int getCooldown();
	int getOwnerID();
	
protected:
	int damage;
	double cooldown;
	int ownerID;
};
