#include "Ability.h"

int Ability::getCooldown() {
	return cooldown;
}

int Ability::getDamage() {
	return damage;
}

Player* Ability::getOwner() {
	return owner;
}