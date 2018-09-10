#include "Player.h"
#include "CustomMath.h"
#include <iostream>

void Player::manipulateSpriteImage(sf::Sprite &playerSprite) {
	playerSprite.scale(0.2, 0.2);
	playerSprite.setOrigin(playerSprite.getLocalBounds().width / 2.0, playerSprite.getLocalBounds().height / 2.0);
	playerSprite.rotate(270);
}

Player::Player(ResourceHolder<sf::Texture, Textures::ID>&rh, int id)
{
	ID = id;
	health = 100;
	sf::Vector2f circlepos = sf::Vector2f(getSprite().getPosition().x - (getSprite().getTextureRect().width / 5 / 3.5), getSprite().getPosition().y - (getSprite().getTextureRect().height / 5 / 2.9));
	float circleradius = 20;
	loadTexture(Textures::Player, rh);
	manipulateSpriteImage(sprite);
	circleshape.setPosition(circlepos);
	circleshape.setRadius(circleradius);
	circleshape.setOrigin(circleradius, circleradius);
	boundingshape = &circleshape;

}
void Player::setBoundingShape() {
	auto mrs = getBoundingShape();
	auto newcirclepos =  sprite.getPosition();
	mrs->setPosition(newcirclepos);
}

float Player::getPlayerCircleRadius() {
	return playerCircleRadius;
}
