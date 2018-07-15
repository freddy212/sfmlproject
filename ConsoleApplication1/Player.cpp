#include "Player.h";
#include "CustomMath.h"
#include <iostream>

void Player::manipulateSpriteImage(sf::Sprite &playerSprite) {
	playerSprite.setOrigin(playerSprite.getGlobalBounds().width / 2, playerSprite.getGlobalBounds().height / 2);
	playerSprite.scale(0.2, 0.2);
}

Player::Player(ResourceHolder<sf::Texture, Textures::ID>&rh)
{
	loadTexture(Textures::Player, rh);
	manipulateSpriteImage(sprite);
}
void Player::stopAtDestination() {
	if (CustomMath::distance(sprite.getPosition(), destination) < 5.0) {
		movementvector = sf::Vector2f(0, 0);
		destination = sprite.getPosition();
	}
}
