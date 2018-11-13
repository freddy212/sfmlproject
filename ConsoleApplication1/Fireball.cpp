#include "Fireball.h"

void manipulateFireballImage(sf::Sprite &fbSprite) {
	fbSprite.setOrigin(fbSprite.getGlobalBounds().width / 2, fbSprite.getGlobalBounds().height / 2);
	fbSprite.scale(0.1, 0.1);
}

Fireball::Fireball(ResourceHolder<sf::Texture, Textures::ID>& rh, int id)
{
	ownerID = id;
	fbrs.setOrigin(10, 10);
	fbrs.setSize(sf::Vector2f(20, 40));
	boundingshape = &fbrs;
	loadTexture(Textures::Fireball, rh);
	manipulateFireballImage(sprite);
	damage = 10;
	cooldown = 0.6;
	movementspeed = 10;
}
void Fireball::handleProjectileLaunch(sf::Vector2f pointClicked, sf::Vector2f characterPos)
{
	Projectile::handleProjectileLaunch(pointClicked, characterPos);
}
void Fireball::setBoundingShape(){
	auto gb = getSprite().getGlobalBounds();
	auto fbrs = getBoundingShape();
	//fbrs->setPosition(gb.left + (gb.width / 2.0) - 10, gb.top + (gb.height / 2.0));
	fbrs->setPosition(sprite.getPosition().x , sprite.getPosition().y);
	//printf(to_string(getAngle());
	fbrs->setRotation(getAngle() - 90);

}