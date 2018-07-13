#include "Player.h";
#include "CustomMath.h"
#include <iostream>

void Player::manipulateSpriteImage(sf::Sprite &playerSprite) {
	playerSprite.setOrigin(playerSprite.getGlobalBounds().width / 2, playerSprite.getGlobalBounds().height / 2);
	playerSprite.scale(0.2, 0.2);
}

void Player::setPosition(sf::Vector2f newpos)
{
	playerSprite.setPosition(newpos);
}

Player::Player(ResourceHolder<sf::Texture, Textures::ID>& rh)
{
	rh.load(Textures::Player, playerImageDestination);
	playerSprite.setTexture(rh.get(Textures::Player));
	manipulateSpriteImage(playerSprite);
}

void Player::move() {
	if (CustomMath::distance(playerSprite.getPosition(), pointTo) < 5.0) {
		movementvector = sf::Vector2f(0, 0);
		pointTo = playerSprite.getPosition();
	}
	playerSprite.move(movementvector.x * 3, movementvector.y * 3);
}

void Player::changeDirection(sf::Vector2f point) {
	std::cout << point.x << point.y;
	movementvector = CustomMath::normalizeUnitVector(playerSprite.getPosition(), point);
	pointTo = point;
	angle = CustomMath::getAngleBetweenPointsInDegrees(playerSprite.getPosition(), point);
	//std::cout << "rotation is : " << angleOfPlayer;
	playerSprite.setRotation(angle);
	//player.changeDirection((sf::Vector2f) sf::Mouse::getPosition(window));
}

sf::Sprite Player::getSprite() {
	return playerSprite;
}