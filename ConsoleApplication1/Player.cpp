#include "Player.h";
#include "CustomMath.h"
#include <iostream>

void Player::manipulateSpriteImage(sf::Sprite &playerSprite) {
	playerSprite.setOrigin(playerSprite.getGlobalBounds().width / 2.0, playerSprite.getGlobalBounds().height / 2.0);
	playerSprite.scale(0.2, 0.2);
	playerSprite.rotate(270);
}

Player::Player(ResourceHolder<sf::Texture, Textures::ID>&rh)
{
	sf::Vector2f circlepos = sf::Vector2f(getSprite().getPosition().x - (getSprite().getTextureRect().width / 5 / 3.5), getSprite().getPosition().y - (getSprite().getTextureRect().height / 5 / 2.9));
	float circleradius = 20;
	circleshape.setPosition(circlepos);
	circleshape.setRadius(circleradius);
	boundingshape = &circleshape;
	loadTexture(Textures::Player, rh);
	manipulateSpriteImage(sprite);
}
void Player::stopAtDestination() {
	if (CustomMath::distance(sprite.getPosition(), destination) < 5.0) {
		movementvector = sf::Vector2f(0, 0);
		destination = sprite.getPosition();
	}
}

void Player::isHit(sf::Vector2f direction) {
	movementvector = direction;
}
void Player::setBoundingShape() {
	auto mrs = getBoundingShape();
	auto newcirclepos =  sf::Vector2f(getSprite().getPosition().x - (getSprite().getTextureRect().width / 5 / 3.5), getSprite().getPosition().y - (getSprite().getTextureRect().height / 5 / 2.9));
	mrs->setPosition(newcirclepos);
}

float Player::getPlayerCircleRadius() {
	return playerCircleRadius;
}
