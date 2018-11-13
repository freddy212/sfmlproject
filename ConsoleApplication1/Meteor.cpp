#include "Meteor.h"

void manipulateMeteorImage(sf::Sprite &mcSprite) {
	mcSprite.setOrigin(mcSprite.getGlobalBounds().width / 2, mcSprite.getGlobalBounds().height / 2);
	mcSprite.scale(0.25, 0.25);
}

Meteor::Meteor(ResourceHolder<sf::Texture, Textures::ID>& rh, int id)
{
	ownerID = id;
	loadTexture(Textures::Meteor, rh);
	manipulateMeteorImage(sprite);
	mrs.setOrigin(25, 25);
	mrs.setSize(sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height));
	boundingshape = &mrs;
	damage = 10;
	cooldown = 0.1;
	movementspeed = 16;
	isReadyToShoot = false;
}
void Meteor::handleProjectileLaunch(sf::Vector2f pointClicked, sf::Vector2f characterPos)
{
	setPosition(pointClicked);
}
void Meteor::setBoundingShape() {
	auto gb = getSprite().getGlobalBounds();
	auto icrs = getBoundingShape();
	icrs->setPosition(gb.left + (gb.width / 2), gb.top + (gb.height / 2));
	icrs->setRotation(getAngle() - 90);
}