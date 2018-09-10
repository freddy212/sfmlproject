#include "Projectile.h"

int Projectile::getCooldown() {
	return cooldown;
}

int Projectile::getDamage() {
	return damage;
}

int Projectile::getOwnerID() {
	return ownerID;
}