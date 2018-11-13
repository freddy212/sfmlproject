#include "Icicle.h"

void manipulateIcicleImage(sf::Sprite &icSprite) {
	icSprite.setOrigin(icSprite.getGlobalBounds().width / 2, icSprite.getGlobalBounds().height / 2);
	icSprite.scale(0.25, 0.25);
}

Icicle::Icicle(ResourceHolder<sf::Texture, Textures::ID>& rh, int id)
{
	ownerID = id;
	icrs.setOrigin(30, 6);
	icrs.setSize(sf::Vector2f(40, 12));
	boundingshape = &icrs;
	loadTexture(Textures::Icicle, rh);
	manipulateIcicleImage(sprite);
	damage = 10;
	cooldown = 0.1;
	movementspeed = 16;
}
void Icicle::handleProjectileLaunch(sf::Vector2f pointClicked, sf::Vector2f characterPos)
{
	Projectile::handleProjectileLaunch(pointClicked, characterPos);
}
void Icicle::setBoundingShape() {
	auto gb = getSprite().getGlobalBounds();
	auto icrs = getBoundingShape();
	icrs->setPosition(gb.left + (gb.width / 2), gb.top + (gb.height / 2));
	icrs->setRotation(getAngle() - 180);
}