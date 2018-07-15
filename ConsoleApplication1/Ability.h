#pragma once

#include "MoveableEntity.h"

class Ability : public MoveableEntity{
public:
	int getDamage();
	int getCooldown();
protected:
	int damage;
	double cooldown;
};
