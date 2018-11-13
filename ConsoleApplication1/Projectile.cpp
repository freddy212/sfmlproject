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

void Projectile::handleProjectileLaunch(sf::Vector2f pointClicked, sf::Vector2f characterPos)
{
	setPosition(characterPos);
	changeDirectionToPoint(pointClicked);
	startMoving(pointClicked);
	//Fix later
	for (auto i = 0; i < 2; i++) {
		moveInDirection();
	}
}

bool Projectile::getReadyToShoot()
{
	return isReadyToShoot;
}
