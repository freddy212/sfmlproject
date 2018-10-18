#include "Projectile.h"

float Projectile::getCooldown() {
	return cooldown;
}

int Projectile::getDamage() {
	return damage;
}

int Projectile::getOwnerID() {
	return ownerID;
}