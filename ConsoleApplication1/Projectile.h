#pragma once

#include "MoveableEntity.h"
class Projectile : public MoveableEntity{
public:
	int getDamage();
	float getCooldown();
	int getOwnerID();
	
protected:
	int damage;
	float cooldown;
	int ownerID;
};
