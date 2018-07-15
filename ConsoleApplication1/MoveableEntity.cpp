#include "MoveableEntity.h"
#include "CustomMath.h"
#include <iostream>
#include "Game.h"

void MoveableEntity::moveInDirection() {
	//std::cout << "are you in here?" << "\n";
	sprite.move(movementvector.x * movementspeed, movementvector.y * movementspeed);
}
void MoveableEntity::changeDirectionToPoint(sf::Vector2f point) {
	angle = CustomMath::getAngleBetweenPointsInDegrees(sprite.getPosition(), point);
	destination = point;
	sprite.setRotation(angle);
}

void MoveableEntity::setPosition(sf::Vector2f point) {
	sprite.setPosition(point);
}

void MoveableEntity::startMoving(sf::Vector2f point) {
	movementvector = CustomMath::normalizeUnitVector(sprite.getPosition(), point);
}

sf::Sprite MoveableEntity::getSprite() {
	return sprite;
}
int MoveableEntity::getMovementSpeed() {
	return movementspeed;
}

void MoveableEntity::loadTexture(Textures::ID id, ResourceHolder <sf::Texture, Textures::ID> &rh)
{
	//rh.load(id, imageDestination);
	sprite.setTexture(rh.get(id));
}

sf::Vector2f MoveableEntity::getMovementVector() {
	return movementvector;
}
