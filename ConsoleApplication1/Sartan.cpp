#include "Sartan.h"

void Sartan::manipulateSpriteImage(sf::Sprite &sartanSprite) {
	sartanSprite.setOrigin(sartanSprite.getGlobalBounds().width / 2.0, sartanSprite.getGlobalBounds().height / 2.0);
	sartanSprite.scale(0.3, 0.3);
	//sartanSprite.rotate(270);
}

Sartan::Sartan(ResourceHolder <sf::Texture, Textures::ID> &rh, int id) {
	ID = id;
	health = 300;
	sf::Vector2f circlepos = sf::Vector2f(getSprite().getPosition().x - (getSprite().getTextureRect().width / 5 / 3.5), getSprite().getPosition().y - (getSprite().getTextureRect().height / 5 / 2.9));
	float circleradius = 20;
	circleshape.setPosition(circlepos);
	circleshape.setRadius(circleradius);
	boundingshape = &circleshape;
	loadTexture(Textures::Sartan, rh);
	manipulateSpriteImage(sprite);
	sprite.setPosition(400, 180);
}

void Sartan::setBoundingShape() {
	auto mrs = getBoundingShape();
	auto newcirclepos = sf::Vector2f(getSprite().getPosition().x - (getSprite().getTextureRect().width / 5 / 3.5), getSprite().getPosition().y - (getSprite().getTextureRect().height / 5 / 2.9));
	mrs->setPosition(newcirclepos);
}

