#include "Character.h"
#include "CustomMath.h"

Character::HitState Character::getHitState() {
	return hitstate;
}

int Character::getHealth() {
	return health;
}

int Character::getID()
{
	return ID;
}


void Character::shootProjectile(Projectile * p, sf::Vector2f &pointClicked)
{
	p->setPosition(getSprite().getPosition());
	p->changeDirectionToPoint(pointClicked);
	p->startMoving(pointClicked);
	//Fix later
	for (auto i = 0; i < 2; i++) {
		p->moveInDirection();
	}
}
void Character::stopAtDestination() {
	if (CustomMath::distance(sprite.getPosition(), destination) < 5.0) {
		movementvector = sf::Vector2f(0, 0);
		destination = sprite.getPosition();
	}
}

void Character::isHit(sf::Vector2f &direction) {
	health = health - 10;
	hitstate = HITSTUN;
	movementspeed = 20;
	movementvector = direction;
}
void Character::outsideBounds() {
	health--;
}
void Character::handleHitStun() {
	if (hitstate == HITSTUN) {
		if (numberOfTimesToRepeatSpeedInHitstun > 1) {
			numberOfTimesToRepeatSpeedInHitstun--;
		}
		else {
			movementspeed = movementspeed / 2;
			numberOfTimesToRepeatSpeedInHitstun = 5;
		}
		if (movementspeed <= 5) {
			numberOfTimesToRepeatSpeedInHitstun = 5;
			hitstate = NOTHIT;
			movementspeed = defaultMovementSpeed;
			movementvector = sf::Vector2f(0, 0);
		}
	}
}
